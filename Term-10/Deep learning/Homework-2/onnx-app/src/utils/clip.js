// CLIP via HuggingFace Inference API
// Бесплатный tier: ~30 000 запросов/месяц
// Токен: https://huggingface.co/settings/tokens

const HF_TOKEN = ""; // вставь свой токен сюда (read-only)
const HF_MODEL = "openai/clip-vit-base-patch32";
const HF_URL   = `https://api-inference.huggingface.co/models/${HF_MODEL}`;

let hfAvailable = null; // null = не проверено, true/false

/**
 * Проверить доступность HF API
 */
export const loadCLIP = async (onProgress) => {
  onProgress?.("Проверка CLIP API...");
  // Просто помечаем как готово — реальный запрос при первом вызове
  hfAvailable = true;
  return true;
};

export const isCLIPReady = () => hfAvailable === true;

/**
 * Crop bbox из img → base64 string
 */
export const cropImage = (imgElement, box) => {
  const [x, y, w, h] = box;
  const scaleX = imgElement.naturalWidth  / imgElement.clientWidth;
  const scaleY = imgElement.naturalHeight / imgElement.clientHeight;
  const canvas = document.createElement("canvas");
  canvas.width  = Math.max(32, Math.round(w * scaleX));
  canvas.height = Math.max(32, Math.round(h * scaleY));
  const ctx = canvas.getContext("2d");
  ctx.drawImage(
    imgElement,
    Math.round(x * scaleX), Math.round(y * scaleY),
    canvas.width, canvas.height,
    0, 0, canvas.width, canvas.height
  );
  // Возвращаем base64 без префикса
  return canvas.toDataURL("image/jpeg").split(",")[1];
};

/**
 * Rank cards by CLIP similarity (HF API).
 * Fallback to class-based matching if API unavailable.
 */
export const rankCards = async (imageBase64, cards, detectedClassName) => {
  // Fallback: если нет токена — матчим по классу
  if (!HF_TOKEN) {
    return fallback(cards, detectedClassName);
  }

  try {
    const labels = cards.map((c) => c.name);

    const response = await fetch(HF_URL, {
      method: "POST",
      headers: {
        "Authorization": `Bearer ${HF_TOKEN}`,
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        inputs: {
          image: imageBase64,
          candidate_labels: labels,
        },
      }),
    });

    if (!response.ok) throw new Error(`HF API: ${response.status}`);

    const results = await response.json();

    // results = [{ label, score }, ...]
    return results
      .map((r) => ({ ...cards[labels.indexOf(r.label)], score: r.score }))
      .sort((a, b) => b.score - a.score);

  } catch (e) {
    console.warn("CLIP API недоступен, fallback:", e.message);
    hfAvailable = false;
    return fallback(cards, detectedClassName);
  }
};

/**
 * Fallback: вернуть карточки того же класса + случайные из других
 */
const fallback = (cards, detectedClassName) => {
  const sameClass  = cards.filter((c) => c.className === detectedClassName);
  const otherClass = cards.filter((c) => c.className !== detectedClassName)
    .sort(() => Math.random() - 0.5)
    .slice(0, 2);
  return [...sameClass, ...otherClass];
};
