import { Tensor } from "onnxruntime-web";
import { renderBoxes, Colors } from "./renderBox";
import labels from "./labels.json";

const colors   = new Colors();
const numClass = labels.length; // 4: None, raspberry, strawberry, blackberry

// ---------- preprocessing ----------

const preprocessImage = (image, modelWidth, modelHeight) => {
  const canvas = document.createElement("canvas");
  canvas.width  = modelWidth;
  canvas.height = modelHeight;
  const ctx = canvas.getContext("2d");

  const scale = Math.min(modelWidth / image.naturalWidth, modelHeight / image.naturalHeight);
  const newW  = Math.round(image.naturalWidth  * scale);
  const newH  = Math.round(image.naturalHeight * scale);
  const padX  = (modelWidth  - newW) / 2;
  const padY  = (modelHeight - newH) / 2;

  ctx.fillStyle = "#808080";
  ctx.fillRect(0, 0, modelWidth, modelHeight);
  ctx.drawImage(image, padX, padY, newW, newH);

  const pixels = ctx.getImageData(0, 0, modelWidth, modelHeight).data;
  const input  = new Float32Array(3 * modelWidth * modelHeight);
  for (let i = 0; i < modelWidth * modelHeight; i++) {
    input[i]                                = pixels[i * 4]     / 255;
    input[i +     modelWidth * modelHeight] = pixels[i * 4 + 1] / 255;
    input[i + 2 * modelWidth * modelHeight] = pixels[i * 4 + 2] / 255;
  }
  return { input, padX, padY, scale };
};

// ---------- mask postprocessing (pure JS, no mask ONNX model) ----------

/**
 * Вычисляет маску для одного объекта и рисует её полупрозрачным цветом на canvas.
 *
 * @param {CanvasRenderingContext2D} ctx
 * @param {Float32Array} proto  - output1.data, shape [1, 32, 160, 160]
 * @param {Float32Array} coefs  - 32 mask coefficients
 * @param {number[]} bounding   - [bx1, by1, bw, bh] в координатах canvas
 * @param {number[]} crop       - [x1, y1, w, h]  в координатах оригинала
 * @param {string}  color       - hex цвет детекции
 * @param {HTMLImageElement} image
 * @param {number} modelWidth
 * @param {number} modelHeight
 * @param {number} padX
 * @param {number} padY
 * @param {number} scale
 */
const drawMask = (ctx, proto, coefs, bounding, crop, color, image, modelWidth, modelHeight, padX, padY, scale) => {
  const nm = 32, mH = 160, mW = 160;
  const [bx1, by1, bw, bh] = bounding;

  // 1. mask[i] = sum_c( coefs[c] * proto[c, y, x] )  (linear combination of prototypes)
  const flat = new Float32Array(mH * mW);
  for (let c = 0; c < nm; c++) {
    const k   = coefs[c];
    const off = c * mH * mW;
    for (let i = 0; i < mH * mW; i++) flat[i] += k * proto[off + i];
  }

  // 2. sigmoid + threshold → binary mask [160, 160]
  const maskBin = new Uint8Array(mH * mW);
  for (let i = 0; i < flat.length; i++) {
    maskBin[i] = (1 / (1 + Math.exp(-flat[i]))) > 0.5 ? 1 : 0;
  }

  // 3. Наложить маску на область bounding box в canvas
  const safeW = Math.min(bw, ctx.canvas.width  - bx1);
  const safeH = Math.min(bh, ctx.canvas.height - by1);
  if (safeW <= 0 || safeH <= 0) return;

  const imgData = ctx.getImageData(bx1, by1, safeW, safeH);
  const d       = imgData.data;
  const [r, g, b] = Colors.hexToRgba(color, 255);

  const canvasScaleX = image.naturalWidth  / ctx.canvas.width;
  const canvasScaleY = image.naturalHeight / ctx.canvas.height;

  for (let py = 0; py < safeH; py++) {
    for (let px = 0; px < safeW; px++) {
      // canvas px → original image coords → model (letterbox) coords → proto coords
      const imgX   = (bx1 + px) * canvasScaleX;
      const imgY   = (by1 + py) * canvasScaleY;
      const modelX = imgX * scale + padX;
      const modelY = imgY * scale + padY;
      const protoX = Math.round(modelX * mW / modelWidth);
      const protoY = Math.round(modelY * mH / modelHeight);

      if (protoX < 0 || protoX >= mW || protoY < 0 || protoY >= mH) continue;
      if (!maskBin[protoY * mW + protoX]) continue;

      const idx = (py * safeW + px) * 4;
      d[idx]     = r;
      d[idx + 1] = g;
      d[idx + 2] = b;
      d[idx + 3] = 120; // полупрозрачность
    }
  }
  ctx.putImageData(imgData, bx1, by1);
};

// ---------- main export ----------

/**
 * Detect + Segment:
 *   1. best.onnx         → output0 [1, 4+numClass+32, 8400], output1 [1, 32, 160, 160]
 *   2. nms-yolov8.onnx   → selected detections
 *   3. JS mask drawing   → полупрозрачные маски на canvas
 *   4. renderBoxes       → рамки и подписи поверх
 */
export const detectImage = async (
  image, canvas, session,
  topk, iouThreshold, scoreThreshold, inputShape
) => {
  const ctx = canvas.getContext("2d");
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  const [, , modelWidth, modelHeight] = inputShape;
  const { input, padX, padY, scale } = preprocessImage(image, modelWidth, modelHeight);

  // 1. Инференс модели сегментации
  const tensor = new Tensor("float32", input, inputShape);
  const config = new Tensor("float32", new Float32Array([numClass, topk, iouThreshold, scoreThreshold]));

  const { output0, output1 } = await session.net.run({ images: tensor });

  // 2. NMS
  const { selected } = await session.nms.run({ detection: output0, config });

  const numSelected = selected.dims[1];
  const rowSize     = selected.dims[2]; // 4 bbox + 4 scores + 32 mask coefs = 40
  const proto       = output1.data;     // Float32Array, [1, 32, 160, 160]

  const boxes = [];

  for (let idx = 0; idx < numSelected; idx++) {
    const data   = selected.data.slice(idx * rowSize, (idx + 1) * rowSize);
    const scores = data.slice(4, 4 + numClass);
    const score  = Math.max(...scores);
    const label  = scores.indexOf(score); // 0=None,1=raspberry,2=strawberry,3=blackberry

    // Пропускаем класс "None"
    if (labels[label] === "None") continue;

    const color = colors.get(label);

    // Bbox cx,cy,w,h → image coords
    const cx = data[0], cy = data[1], bw = data[2], bh = data[3];
    const x1 = Math.max(0, Math.round(((cx - bw / 2) - padX) / scale));
    const y1 = Math.max(0, Math.round(((cy - bh / 2) - padY) / scale));
    const w  = Math.round(bw / scale);
    const h  = Math.round(bh / scale);

    const sx = canvas.width  / image.naturalWidth;
    const sy = canvas.height / image.naturalHeight;

    const bx1 = Math.round(x1 * sx);
    const by1 = Math.round(y1 * sy);
    const bw2 = Math.round(w  * sx);
    const bh2 = Math.round(h  * sy);

    // Mask coefficients: индексы 8..39
    const maskCoefs = new Float32Array(data.slice(8));

    // 3. Рисуем маску через JS
    drawMask(ctx, proto, maskCoefs, [bx1, by1, bw2, bh2], [x1, y1, w, h],
             color, image, modelWidth, modelHeight, padX, padY, scale);

    boxes.push({
      label:       labels[label], // labels.json: 0=None,1=raspberry,2=strawberry,3=blackberry
      labelIdx:    label,
      probability: score,
      color,
      bounding:    [bx1, by1, bw2, bh2],
      crop:        [x1, y1, w, h],
    });
  }

  // 4. Рамки и подписи поверх масок
  renderBoxes(ctx, boxes);
  return boxes;
};
