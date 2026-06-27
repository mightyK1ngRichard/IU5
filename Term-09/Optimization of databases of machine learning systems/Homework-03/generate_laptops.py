import random
import numpy as np
import psycopg2
from psycopg2 import sql
from transformers import AutoTokenizer, AutoModel
import torch
import time

# ============ НАСТРОЙКА ПОДКЛЮЧЕНИЯ К БАЗЕ ДАННЫХ ============
DB_CONFIG = {
    "host": "localhost",
    "database": "iu5",
    "user": "postgres",
    "password": "iu5-magisters"
}

# ============ ОПРЕДЕЛЕНИЕ СВОЙСТВ НОУТБУКОВ ============
properties = {
    'manufacturers': ['LG', 'HP', 'Lenovo', 'Samsung', 'Asus', 'Acer', 'Apple'],
    'cpus': ['x64', 'ARM', 'RISC-V'],
    'harddrive_types': ['SSD', 'HDD', 'SSD+HDD'],
    'harddrive_spaces': ['<= 128 GB', '128-256GB', '256-512GB', '512-1024GB', '1024+GB'],
    'ram_types': ['DDR3', 'DDR4'],
    'rams': ['1-2GB', '2-4GB', '4-8GB', '8-16GB', '16+GB'],
    'wifis': ['No Wifi', 'Wifi 2.4', 'Wifi 5.8'],
    'bluetooths': ['No Bluetooth', 'Has Bluetooth'],
    'ethernets': ['No Ethernet', 'Has Ethernet'],
    'webcams': ['No Webcam', 'Has Webcam'],
    'cardreaders': ['No Cardreader', 'Has Cardreader'],
    'graphics': ['Integrated GPU', 'External GPU', 'Integrated+External GPU'],
    'displays': ['13.3 inch', '15.6 inch', '16 inch'],
    'usbs': ['No USB', 'USB 2.0', 'USB 3.0'],
    'batteries': ['<= 4 Hours', '4-6 hours', '6-8 hours', '8-10 hours', '10+ hours']
}

# ============ ЗАГРУЗКА МОДЕЛИ ДЛЯ ЭМБЕДДИНГОВ ============
print("Загрузка модели для генерации эмбеддингов...")
tokenizer = AutoTokenizer.from_pretrained('sentence-transformers/all-MiniLM-L6-v2')
model = AutoModel.from_pretrained('sentence-transformers/all-MiniLM-L6-v2')
print("Модель загружена успешно!")


# ============ ФУНКЦИЯ ДЛЯ ПОЛУЧЕНИЯ ЭМБЕДДИНГА ============
def get_embedding(text):
    """Генерация эмбеддинга для текста"""
    inputs = tokenizer(
        text,
        return_tensors='pt',
        truncation=True,
        padding=True,
        max_length=512
    )

    with torch.no_grad():
        outputs = model(**inputs)

    return outputs.last_hidden_state[:, 0, :].numpy()[0]


# ============ ФУНКЦИЯ СОЗДАНИЯ ТАБЛИЦЫ ============
def create_table(conn):
    """Создание таблицы laptops в базе данных"""
    with conn.cursor() as cur:
        cur.execute("""
                    CREATE TABLE IF NOT EXISTS laptops
            (
                id              SERIAL PRIMARY KEY,
                manufacturer    TEXT        NOT NULL,
                cpu             TEXT        NOT NULL,
                harddrive_type  TEXT        NOT NULL,
                harddrive_space TEXT        NOT NULL,
                ram_type        TEXT        NOT NULL,
                ram             TEXT        NOT NULL,
                wifi            TEXT        NOT NULL,
                bluetooth       TEXT        NOT NULL,
                ethernet        TEXT        NOT NULL,
                webcam          TEXT        NOT NULL,
                cardreader      TEXT        NOT NULL,
                graphics        TEXT        NOT NULL,
                display         TEXT        NOT NULL,
                usb             TEXT        NOT NULL,
                battery         TEXT        NOT NULL,
                description     TEXT        NOT NULL,
                embedding       VECTOR(384) NOT NULL,
                created_at      TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );
        """)
    conn.commit()
    print("✅ Таблица 'laptops' создана или уже существует")


# ============ ФУНКЦИЯ ДЛЯ ВСТАВКИ ДАННЫХ ============
def insert_single_laptop(conn, laptop_data):
    """Вставка одной записи о ноутбуке в таблицу"""
    with conn.cursor() as cur:
        cur.execute("""
                    INSERT INTO laptops (manufacturer, cpu, harddrive_type, harddrive_space,
                                         ram_type, ram, wifi, bluetooth, ethernet, webcam,
                                         cardreader, graphics, display, usb, battery,
                                         description, embedding)
                    VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s,
                            %s, %s, %s, %s, %s, %s, %s)
                    """, laptop_data)
    conn.commit()


# ============ ОСНОВНАЯ ФУНКЦИЯ ============
def main():
    # Параметры по вашему варианту
    total_laptops = 5000  # По вашему варианту: 5000 ноутбуков

    try:
        # Подключение к базе данных
        print("Подключение к PostgreSQL...")
        conn = psycopg2.connect(**DB_CONFIG)
        print("✅ Успешное подключение к PostgreSQL!")

        # Создание таблицы
        create_table(conn)

        # Проверяем, сколько уже есть записей
        with conn.cursor() as cur:
            cur.execute("SELECT COUNT(*) FROM laptops;")
            existing_count = cur.fetchone()[0]
            print(f"📊 В таблице уже есть {existing_count} ноутбуков")

        # Если уже есть достаточно данных, пропускаем генерацию
        if existing_count >= total_laptops:
            print(f"✅ Уже достаточно данных ({existing_count} из {total_laptops})")
            print("   Пропускаем генерацию...")
            conn.close()
            return

        # Генерация и вставка записей
        print(f"\n🚀 Начинаем генерацию {total_laptops - existing_count} новых ноутбуков...")
        start_time = time.time()

        for id in range(existing_count + 1, total_laptops + 1):
            # Формируем случайную конфигурацию ноутбука
            laptop_chars = {}
            description_parts = []

            for key, values in properties.items():
                # 1. Определяем случайное значение для ключа
                i = random.randint(0, len(values) - 1)

                # 2. Сохраняем в словарь
                laptop_chars[key] = values[i]

                # 3. Добавляем в список для описания
                description_parts.append(f"{key}:{values[i]}")

            # 4. Объединяем описание в одну строку
            description = ','.join(description_parts)

            # 5. Генерируем embedding
            embedding = get_embedding(description)

            # 6. Подготавливаем данные для вставки
            laptop_data = (
                laptop_chars['manufacturers'],
                laptop_chars['cpus'],
                laptop_chars['harddrive_types'],
                laptop_chars['harddrive_spaces'],
                laptop_chars['ram_types'],
                laptop_chars['rams'],
                laptop_chars['wifis'],
                laptop_chars['bluetooths'],
                laptop_chars['ethernets'],
                laptop_chars['webcams'],
                laptop_chars['cardreaders'],
                laptop_chars['graphics'],
                laptop_chars['displays'],
                laptop_chars['usbs'],
                laptop_chars['batteries'],
                description,
                embedding.tolist()  # Преобразуем numpy array в список
            )

            # 7. Вставляем запись в таблицу
            insert_single_laptop(conn, laptop_data)

            # Прогресс-бар каждые 500 ноутбуков
            if id % 500 == 0:
                print(f"  ✅ Сгенерировано {id}/{total_laptops} ноутбуков...")

        end_time = time.time()
        total_time = end_time - start_time

        print(f"\n🎉 ГЕНЕРАЦИЯ ЗАВЕРШЕНА!")
        print(f"📊 Всего ноутбуков в базе: {total_laptops}")
        print(f"⏱️  Общее время выполнения: {total_time:.2f} секунд")
        print(f"⏱️  Среднее время на ноутбук: {total_time / (total_laptops - existing_count):.3f} секунд")

    except Exception as e:
        print(f"❌ Ошибка: {e}")
    finally:
        if 'conn' in locals():
            conn.close()
            print("🔌 Соединение с PostgreSQL закрыто")


if __name__ == "__main__":
    main()