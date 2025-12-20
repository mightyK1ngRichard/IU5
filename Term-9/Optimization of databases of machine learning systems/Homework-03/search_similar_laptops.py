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


# ============ ПРОВЕРКА НАЛИЧИЯ ДАННЫХ ============
def check_table_exists_and_has_data(conn):
    """Проверка существования таблицы и наличия данных"""
    with conn.cursor() as cur:
        # Проверяем существование таблицы
        cur.execute("""
                    SELECT EXISTS (SELECT
                                   FROM information_schema.tables
                                   WHERE table_name = 'laptops');
                    """)
        table_exists = cur.fetchone()[0]

        if not table_exists:
            print("❌ ТАБЛИЦА 'laptops' НЕ СУЩЕСТВУЕТ!")
            print("   Сначала запустите generate_laptops.py")
            return False

        # Проверяем количество данных
        cur.execute("SELECT COUNT(*) FROM laptops;")
        count = cur.fetchone()[0]

        print(f"📊 Найдено записей в таблице 'laptops': {count}")

        if count == 0:
            print("❌ ТАБЛИЦА ПУСТА!")
            print("   Сначала запустите generate_laptops.py")
            return False

        if count < 3:
            print(f"⚠️  В таблице всего {count} записей, нужно минимум 3 для поиска")
            return False

        return True


# ============ ФУНКЦИЯ ДЛЯ СОЗДАНИЯ ИНДЕКСА HNSW ============
def create_hnsw_index(conn):
    """Создание HNSW индекса для ускорения поиска"""
    with conn.cursor() as cur:
        print("Создание HNSW индекса...")
        start_time = time.time()

        # Проверяем, не существует ли уже индекс
        cur.execute("""
                    SELECT indexname
                    FROM pg_indexes
                    WHERE tablename = 'laptops'
                      AND indexname LIKE '%embedding%';
                    """)
        existing_index = cur.fetchone()

        if existing_index:
            print(f"⚠️  Индекс уже существует: {existing_index[0]}")
            print("   Пропускаем создание индекса...")
            return

        # Увеличиваем память для ускорения создания индекса
        cur.execute("SET maintenance_work_mem = '2GB';")

        # Создаем индекс
        cur.execute("""
                    CREATE INDEX laptops_embedding_hnsw_idx
                        ON laptops USING hnsw (embedding vector_cosine_ops)
                        WITH (m = 16, ef_construction = 64);
                    """)

        conn.commit()
        end_time = time.time()

        print(f"✅ HNSW индекс создан успешно!")
        print(f"⏱️  Время создания индекса: {end_time - start_time:.2f} секунд")


# ============ ПОИСК ПОХОЖИХ НОУТБУКОВ ============
def search_similar_laptops(conn, embedding_list, use_index=False, limit=3):
    """Поиск похожих ноутбуков по косинусному расстоянию"""
    with conn.cursor() as cur:
        # Настраиваем параметры поиска в зависимости от использования индекса
        if use_index:
            # Для HNSW индекса настраиваем точность поиска
            cur.execute("SET hnsw.ef_search = 100;")

        # SQL запрос для поиска похожих ноутбуков
        query = """
                SELECT id, \
                       manufacturer, \
                       cpu, \
                       harddrive_type, \
                       harddrive_space, \
                       ram_type, \
                       ram, \
                       wifi, \
                       bluetooth, \
                       ethernet, \
                       webcam, \
                       cardreader, \
                       graphics, \
                       display, \
                       usb, \
                       battery, \
                       description, \
                       1 - (embedding <=> %s::vector) AS similarity
                FROM laptops
                ORDER BY embedding <=> %s::vector
                    LIMIT %s; \
                """

        # Выполняем запрос и замеряем время
        start_time = time.time()
        cur.execute(query, (embedding_list, embedding_list, limit))
        results = cur.fetchall()
        end_time = time.time()

        return results, end_time - start_time


# ============ ФОРМИРОВАНИЕ КОНФИГУРАЦИИ ИЗ ВАШЕГО ВАРИАНТА ============
def create_target_configuration():
    """Создание целевой конфигурации ноутбука по вашему варианту"""

    properties1 = {
        'manufacturers': 'LG',
        'cpus': 'x64',
        'harddrive_types': 'SSD',
        'harddrive_spaces': '<= 128 GB',
        'ram_types': 'DDR4',
        'rams': '2-4GB',
        'wifis': 'Wifi 2.4',
        'bluetooths': 'Has Bluetooth',
        'ethernets': 'Has Ethernet',
        'webcams': 'No Webcam',
        'cardreaders': 'No Cardreader',
        'graphics': 'External GPU',
        'displays': '15.6 inch',
        'usbs': 'USB 2.0',
        'batteries': '4-6 hours',
    }

    # Формируем описание
    description_parts = []
    for key, value in properties1.items():
        description_parts.append(f"{key}:{value}")

    description = ','.join(description_parts)

    # Выводим информацию о целевой конфигурации
    print("=" * 70)
    print("ЦЕЛЕВАЯ КОНФИГУРАЦИЯ НОУТБУКА (по 1 варианту):")
    print("=" * 70)
    for key, value in properties1.items():
        print(f"  {key.replace('_', ' ').title()}: {value}")
    print(f"\n  Текстовое описание: {description}")
    print("=" * 70)

    return properties1, description


# ============ ОТОБРАЖЕНИЕ РЕЗУЛЬТАТОВ ============
def display_results(results, search_time, use_index=False):
    """Красивое отображение результатов поиска"""

    index_status = "С ИНДЕКСОМ HNSW" if use_index else "БЕЗ ИНДЕКСА"

    print(f"\n{'=' * 70}")
    print(f"РЕЗУЛЬТАТЫ ПОИСКА ({index_status}):")
    print(f"{'=' * 70}")
    print(f"⏱️  Время выполнения запроса: {search_time:.4f} секунд")
    print(f"📊 Найдено похожих ноутбуков: {len(results)}\n")

    for idx, row in enumerate(results, 1):
        print(f"{'─' * 70}")
        print(f"НОУТБУК #{idx} (ID: {row[0]}, Сходство: {row[-1]:.4f})")
        print(f"{'─' * 70}")

        # Извлекаем характеристики
        characteristics = [
            "Производитель", "Процессор", "Тип HDD", "Объем HDD",
            "Тип RAM", "Объем RAM", "Wi-Fi", "Bluetooth", "Ethernet",
            "Webcam", "Cardreader", "Графика", "Дисплей", "USB", "Батарея"
        ]

        for i, (char_name, char_value) in enumerate(zip(characteristics, row[1:16])):
            print(f"  {char_name}: {char_value}")

        print(f"  Описание: {row[16][:100]}..." if len(row[16]) > 100 else f"  Описание: {row[16]}")
        print()


# ============ ОСНОВНАЯ ФУНКЦИЯ ============
def main():
    try:
        # Подключение к базе данных
        print("Подключение к PostgreSQL...")
        conn = psycopg2.connect(**DB_CONFIG)
        print("✅ Успешное подключение к PostgreSQL!\n")

        # Проверяем наличие данных
        if not check_table_exists_and_has_data(conn):
            conn.close()
            return

        # 1. Формируем целевую конфигурацию и получаем embedding
        properties1, description = create_target_configuration()
        embedding = get_embedding(description)
        embedding_list = embedding.tolist()

        print(f"\n📐 Размерность эмбеддинга: {len(embedding_list)}")
        print(f"📏 Вектор эмбеддинга (первые 5 значений): {embedding_list[:5]}\n")

        # 2. Поиск БЕЗ индекса
        print("\n" + "#" * 70)
        print("ПОИСК ПОХОЖИХ НОУТБУКОВ БЕЗ ИНДЕКСА:")
        print("#" * 70)

        results_without_index, time_without_index = search_similar_laptops(
            conn, embedding_list, use_index=False, limit=3
        )
        display_results(results_without_index, time_without_index, use_index=False)

        # 3. Создаем HNSW индекс
        create_hnsw_index(conn)

        # 4. Поиск С индексом
        print("\n" + "#" * 70)
        print("ПОИСК ПОХОЖИХ НОУТБУКОВ С ИНДЕКСОМ HNSW:")
        print("#" * 70)

        results_with_index, time_with_index = search_similar_laptops(
            conn, embedding_list, use_index=True, limit=3
        )
        display_results(results_with_index, time_with_index, use_index=True)

        # 5. Сравнение производительности
        print("\n" + "=" * 70)
        print("СРАВНЕНИЕ ПРОИЗВОДИТЕЛЬНОСТИ:")
        print("=" * 70)
        print(f"⏱️  Время БЕЗ индекса: {time_without_index:.4f} секунд")
        print(f"⏱️  Время С индексом:   {time_with_index:.4f} секунд")

        if time_without_index > 0 and time_with_index > 0:
            speedup = time_without_index / time_with_index
            print(f"🚀 Ускорение: в {speedup:.2f} раз!")

        print("=" * 70)

    except Exception as e:
        print(f"❌ Ошибка: {e}")
        import traceback
        traceback.print_exc()
    finally:
        if 'conn' in locals():
            conn.close()
            print("\n🔌 Соединение с PostgreSQL закрыто")


if __name__ == "__main__":
    main()