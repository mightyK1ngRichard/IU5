from django.shortcuts import render
from django.core.files.storage import FileSystemStorage
import onnxruntime
import numpy as np
from PIL import Image
from django.conf import settings

imageClassList = {
    '0': {
        'name': 'Ежевика',
        'emoji': '🫐',
        'features': [
            {'icon': '🌿', 'text': 'Тёмно-фиолетовые или чёрные плоды, состоящие из мелких костянок'},
            {'icon': '🌱', 'text': 'Растёт на колючих кустарниках, листья зубчатые, тёмно-зелёные'},
            {'icon': '🍬', 'text': 'Вкус кисло-сладкий, богата антиоксидантами и витамином C'},
            {'icon': '📅', 'text': 'Созревает в конце лета — начале осени (июль–сентябрь)'},
        ]
    },
    '2': {
        'name': 'Клубника',
        'emoji': '🍓',
        'features': [
            {'icon': '❤️', 'text': 'Ярко-красные плоды сердцевидной формы с мелкими семенами на поверхности'},
            {'icon': '🌿', 'text': 'Низкорослое растение с тройчатыми листьями и белыми цветками'},
            {'icon': '🍬', 'text': 'Сладкий насыщенный вкус, высокое содержание витамина C и фолиевой кислоты'},
            {'icon': '📅', 'text': 'Основной сезон — конец весны и начало лета (май–июнь)'},
        ]
    },
    '1': {
        'name': 'Малина',
        'emoji': '🫐',
        'features': [
            {'icon': '🔴', 'text': 'Мягкие красные (реже жёлтые) плоды, легко отделяются от цветоложа'},
            {'icon': '🌱', 'text': 'Кустарник с тонкими побегами, покрытыми мелкими шипами'},
            {'icon': '🍬', 'text': 'Нежный сладко-кислый вкус, богата клетчаткой, марганцем и витамином K'},
            {'icon': '📅', 'text': 'Созревает летом: июнь–август в зависимости от сорта'},
        ]
    },
}

MODEL_NAME = 'homework_cifar100_CNN_RESNET20'


def scoreImagePage(request):
    context = {
        'classExamples': imageClassList,
        'classNames': {key: value['name'] for key, value in imageClassList.items()},
    }
    return render(request, 'scorepage.html', context)


def predictImage(request):
    fileObj = request.FILES['filePath']
    fs = FileSystemStorage()
    filePathName = fs.save('images/' + fileObj.name, fileObj)
    uploaded_image_url = fs.url(filePathName)
    scorePrediction = predictImageData('.' + uploaded_image_url)

    predicted_class_info = imageClassList.get(scorePrediction['class_id'], {})

    context = {
        'scorePrediction': scorePrediction,
        'predictedClassInfo': predicted_class_info,
        'uploaded_image_url': uploaded_image_url,
        'classExamples': imageClassList,
        'classNames': {key: value['name'] for key, value in imageClassList.items()},
    }
    return render(request, 'scorepage.html', context)


def predictImageData(filePath):
    img = Image.open(filePath).convert("RGB")
    img_resized = np.asarray(img.resize((32, 32), Image.LANCZOS))
    sess = onnxruntime.InferenceSession(
        rf'{settings.MEDIA_ROOT}/models/{MODEL_NAME}.onnx'
    )
    input_tensor = np.asarray([img_resized]).astype(np.float32)
    logits = sess.run(None, {'input': input_tensor})[0]
    class_id = str(int(np.argmax(logits)))
    confidence = float(np.max(logits))

    return {
        'class_id': class_id,
        'class_name': imageClassList.get(class_id, {}).get('name', 'Неизвестно'),
        'confidence': confidence,
    }
