import random
import numpy as np
import simpy
import statistics
import matplotlib.pyplot as plt

# Константы модели
NUM_OF_DOCKS = 10
TRIANGLE_MODE = 8
TRIANGLE_MIN = 4
TRIANGLE_MAX = 10
MEAN_TRUCKS = 14
STD_TRUCKS = 3
MEAN_ARRIVAL = 540
MEAN_UNLOADING = [0, 22, 21, 27, 24, 17, 19, 22, 31, 28, 29]
DOCKS_LOADING = [0] * NUM_OF_DOCKS
TRUCK_CAPACITY = [1, 2, 3]
TOTAL_UNLOADING_TIME = 0
TRUCK_COUNT = 0
CRANE_COUNT = 0
FORKLIFT_COUNT = 0
DAILY_STORAGE_FILLED = 0
TOTAL_STORAGE_CAPACITY = 300
MONTHLY_LOADING_RATIO = []
DAILY_FORKLIFT_COUNT = {}
DAILY_CRANE_COUNT = {}
DAILY_STORAGE_FILLED_GRAPH = {}
DAILY_UNLOADING_TIME = {}
QUEUE_TIMES = {}
COUNTER = 0
DAILY_UNLOADING_TIME_COUNTER = 0
DAY_COUNT = 1
MULTIPLEXOR = 1

# SimPy environment
env = simpy.Environment()

# Генерация количеств грузовиков разной грузоподъемности в колонне
def generate_truck_counts():
    num_types = int(np.random.triangular(TRIANGLE_MIN, TRIANGLE_MODE, TRIANGLE_MAX))
    truck_counts = [0] * (TRIANGLE_MAX + 1)

    available_types = list(range(1, TRIANGLE_MAX + 1))
    for _ in range(num_types):
        truck_type = random.choice(available_types)
        available_types.remove(truck_type)
        num_trucks = int(np.random.normal(MEAN_TRUCKS, STD_TRUCKS))
        truck_counts[truck_type] = num_trucks

    return truck_counts


# Генерация времени прибытия колонны
def generate_arrival_time():
    return np.random.exponential(MEAN_ARRIVAL)


# Разгрузка грузовика
def unload_truck(env, dock_id, truck_type):
    global TOTAL_UNLOADING_TIME, TRUCK_COUNT, CRANE_COUNT, FORKLIFT_COUNT, DAILY_STORAGE_FILLED, DAILY_UNLOADING_TIME_COUNTER

    unload_time = np.random.exponential(scale=MEAN_UNLOADING[truck_type])
    yield env.timeout(unload_time)
    DOCKS_LOADING[dock_id] -= 1
    DAILY_UNLOADING_TIME[COUNTER] = unload_time
    DAILY_UNLOADING_TIME_COUNTER += 1
    TRUCK_COUNT += 1
    if truck_type in [5, 6, 7]:
        yield env.timeout(TRUCK_CAPACITY[0] * MULTIPLEXOR)
        DAILY_STORAGE_FILLED += TRUCK_CAPACITY[0]
        TOTAL_UNLOADING_TIME += unload_time + TRUCK_CAPACITY[0] * MULTIPLEXOR
    if truck_type in [1, 2, 3, 4]:
        yield env.timeout(TRUCK_CAPACITY[1] * MULTIPLEXOR)
        DAILY_STORAGE_FILLED += TRUCK_CAPACITY[1]
        TOTAL_UNLOADING_TIME += unload_time + TRUCK_CAPACITY[1] * MULTIPLEXOR
    if truck_type in [8, 9, 10]:
        yield env.timeout(TRUCK_CAPACITY[2] * MULTIPLEXOR)
        DAILY_STORAGE_FILLED += TRUCK_CAPACITY[2]
        TOTAL_UNLOADING_TIME += unload_time + TRUCK_CAPACITY[2] * MULTIPLEXOR


# Разгрузка грузовиков на колоннах
def unload_trucks(env, truck_counts):
    global FORKLIFT_COUNT, CRANE_COUNT, COUNTER
    for i in range(len(truck_counts)):
        num_trucks = truck_counts[i]
        for _ in range(num_trucks):
            if i in [1, 2, 3, 4] and truck_counts[i] != 0:
                FORKLIFT_COUNT += 1
                if DAY_COUNT not in DAILY_FORKLIFT_COUNT:
                    DAILY_FORKLIFT_COUNT[DAY_COUNT] = 1
                else:
                    DAILY_FORKLIFT_COUNT[DAY_COUNT] += 1
            elif i in [8, 9, 10] and truck_counts[i] != 0:
                CRANE_COUNT += 1
                if DAY_COUNT not in DAILY_CRANE_COUNT:
                    DAILY_CRANE_COUNT[DAY_COUNT] = 1
                else:
                    DAILY_CRANE_COUNT[DAY_COUNT] += 1
            yield env.timeout(0)
            free_docks = [j for j in range(NUM_OF_DOCKS) if DOCKS_LOADING[j] == 0]
            while not free_docks:  # Ждем, пока не освободится док
                yield env.timeout(1)
                if COUNTER not in QUEUE_TIMES:
                    QUEUE_TIMES[COUNTER] = 1
                else:
                    QUEUE_TIMES[COUNTER] += 1
                free_docks = [j for j in range(NUM_OF_DOCKS) if DOCKS_LOADING[j] == 0]
            COUNTER += 1
            free_dock = random.choice(free_docks)
            DOCKS_LOADING[free_dock] += 1
            env.process(unload_truck(env, free_dock, i))


# Основная функция моделирования склада
def simulate_warehouse(env):
    global DAILY_STORAGE_FILLED, DAY_COUNT
    while DAY_COUNT < 31:
        truck_counts = generate_truck_counts()
        arrival_time = generate_arrival_time()

        yield env.timeout(arrival_time)
        yield env.process(unload_trucks(env, truck_counts))

        DAILY_STORAGE_FILLED_GRAPH[DAY_COUNT] = DAILY_STORAGE_FILLED / TOTAL_STORAGE_CAPACITY
        loading_ratio = DAILY_STORAGE_FILLED / TOTAL_STORAGE_CAPACITY
        MONTHLY_LOADING_RATIO.append(loading_ratio)
        print(f"Загруженность склада за день {DAY_COUNT}: {loading_ratio:.2f}")
        DAILY_STORAGE_FILLED = 0
        DAY_COUNT += 1

    avg_unloading_time = TOTAL_UNLOADING_TIME / TRUCK_COUNT
    avg_monthly_loading_ratio = sum(MONTHLY_LOADING_RATIO) / len(MONTHLY_LOADING_RATIO)

    print(f"Среднее время разгрузки грузовиков: {avg_unloading_time:.2f} минут")
    print(f"Средний коэффициент загрузки за месяц: {avg_monthly_loading_ratio:.2f}")
    print(f"Вилочные погрузчики были использованы {FORKLIFT_COUNT} раз")
    print(f"Краны были использованы {CRANE_COUNT} раз")

    print(f"Максимальная продолжительность ожидания в очереди: {max(QUEUE_TIMES.values())} мин")
    minutes, seconds = divmod(statistics.mean(QUEUE_TIMES.values()) * 60, 60)
    seconds = int(seconds)
    print(f"Среднее время ожидания в очереди: {int(minutes)} мин {seconds} сек")

    x1 = list(QUEUE_TIMES.keys())
    y1 = list(QUEUE_TIMES.values())

    # Создание графика
    plt.bar(x1, y1)

    # Добавление подписей осей и заголовка
    plt.grid(True)
    plt.xlabel('Номер грузовика')
    plt.ylabel('Время ожидания в очереди (мин)')
    plt.title('Статистика ожидания грузовиков в очереди')

    # Показать график
    plt.show()

    x2 = list(DAILY_UNLOADING_TIME.keys())
    y2 = list(DAILY_UNLOADING_TIME.values())

    # Создание графика
    plt.bar(x2, y2)

    # Добавление подписей осей и заголовка
    plt.grid(True)
    plt.xlabel('Номер грузовика')
    plt.ylabel('Время время разгрузки (мин)')
    plt.title('Статистика времени разгрузки грузовиков')

    # Показать график
    plt.show()

    x3 = list(DAILY_STORAGE_FILLED_GRAPH.keys())
    y3 = list(DAILY_STORAGE_FILLED_GRAPH.values())

    # Создание графика
    plt.plot(x3, y3)

    # Добавление подписей осей и заголовка
    plt.grid(True)
    plt.xlabel('День')
    plt.ylabel('Загруженность склада (коэффициент)')
    plt.title('Статистика загруженности склада по дням')

    # Показать график
    plt.show()

    x4 = list(DAILY_FORKLIFT_COUNT.keys())
    y4 = list(DAILY_FORKLIFT_COUNT.values())

    # Создание графика
    plt.plot(x4, y4)

    # Добавление подписей осей и заголовка
    plt.grid(True)
    plt.xlabel('День')
    plt.ylabel('Кол-во использований вилочных погрузчиков')
    plt.title('Статистика использований вилочных погрузчиков по дням')

    # Показать график
    plt.show()

    x5 = list(DAILY_CRANE_COUNT.keys())
    y5 = list(DAILY_CRANE_COUNT.values())

    # Создание графика
    plt.plot(x5, y5)

    # Добавление подписей осей и заголовка
    plt.grid(True)
    plt.xlabel('День')
    plt.ylabel('Кол-во использований кранов')
    plt.title('Статистика использований кранов по дням')

    # Показать график
    plt.show()

    return avg_unloading_time, avg_monthly_loading_ratio, FORKLIFT_COUNT, CRANE_COUNT


env.process(simulate_warehouse(env))
env.run()
