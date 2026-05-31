import React, { useState, useRef, useEffect } from "react";
import { Tensor, InferenceSession } from "onnxruntime-web";
import { detectImage } from "./utils/detect";
import "./style/App.css";

const LEGEND = [
  { label: "blackberry", color: "#FF3838" },
  { label: "raspberry",  color: "#FF9D97" },
  { label: "strawberry", color: "#FF701F" },
];

const App = () => {
  const [session, setSession] = useState(null);
  const [loading, setLoading] = useState("Загрузка YOLOv8-seg...");
  const [image, setImage]     = useState(null);

  const inputImage = useRef(null);
  const imageRef   = useRef(null);
  const canvasRef  = useRef(null);

  const modelInputShape = [1, 3, 640, 640];
  const topk            = 100;
  const iouThreshold    = 0.45;
  const scoreThreshold  = 0.25;

  useEffect(() => {
    const init = async () => {
      try {
        const yolov8 = await InferenceSession.create("./best.onnx");
        const nms    = await InferenceSession.create("./nms-yolov8.onnx");

        setLoading("Прогрев модели...");
        const dummy = new Tensor("float32",
          new Float32Array(modelInputShape.reduce((a, b) => a * b)),
          modelInputShape
        );
        await yolov8.run({ images: dummy });

        setSession({ net: yolov8, nms });
        setLoading(null);
      } catch (e) {
        setLoading("Ошибка: " + e.message);
        console.error(e);
      }
    };
    init();
  }, []);

  const handleImageLoad = async () => {
    if (!session || !imageRef.current || !canvasRef.current) return;
    const img = imageRef.current;
    canvasRef.current.width  = img.clientWidth;
    canvasRef.current.height = img.clientHeight;

    await detectImage(
      img, canvasRef.current, session,
      topk, iouThreshold, scoreThreshold, modelInputShape
    );
  };

  const handleFile = (e) => {
    const file = e.target.files?.[0];
    if (!file) return;
    if (image) URL.revokeObjectURL(image);
    const url = URL.createObjectURL(file);
    imageRef.current.src = url;
    setImage(url);
  };

  const handleClose = () => {
    inputImage.current.value = "";
    imageRef.current.src = "#";
    URL.revokeObjectURL(image);
    setImage(null);
    const ctx = canvasRef.current?.getContext("2d");
    if (ctx) ctx.clearRect(0, 0, canvasRef.current.width, canvasRef.current.height);
  };

  return (
    <div className="App">
      <div className="header">
        <h1>🍓 Berry Detector</h1>
        <p>YOLOv8-seg · ONNX Runtime · React</p>
      </div>

      {loading && (
        <div className="loader">
          <div className="spinner" />
          {loading}
        </div>
      )}

      {!image ? (
        <div className="drop-zone" onClick={() => !loading && inputImage.current.click()}>
          <div className="icon">🖼️</div>
          <p><span>Нажмите</span> чтобы загрузить фото</p>
          <p>raspberry · strawberry · blackberry</p>
        </div>
      ) : (
        <div className="content">
          <img ref={imageRef} src="#" alt="detection" onLoad={handleImageLoad} />
          <canvas ref={canvasRef} />
        </div>
      )}

      {!image && (
        <>
          <img ref={imageRef} src="#" alt="" style={{ display: "none" }} onLoad={handleImageLoad} />
          <canvas ref={canvasRef} style={{ display: "none" }} />
        </>
      )}

      <div className="btn-container">
        {!image ? (
          <button className="primary" onClick={() => !loading && inputImage.current.click()}>
            📂 Открыть изображение
          </button>
        ) : (
          <>
            <button className="primary" onClick={() => inputImage.current.click()}>
              📂 Другое фото
            </button>
            <button className="secondary" onClick={handleClose}>
              ✕ Закрыть
            </button>
          </>
        )}
      </div>

      <div className="legend">
        {LEGEND.map((item) => (
          <div className="legend-item" key={item.label}>
            <div className="legend-dot" style={{ background: item.color }} />
            {item.label}
          </div>
        ))}
      </div>

      <input
        type="file"
        ref={inputImage}
        accept="image/*"
        style={{ display: "none" }}
        onChange={handleFile}
      />
    </div>
  );
};

export default App;
