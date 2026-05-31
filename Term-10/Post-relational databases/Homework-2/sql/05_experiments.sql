-- =====================================================================
-- ДЗ-2 ПБД, вариант 5 (GIN + BRIN), Пермяков Д.К.
-- Скрипт 05: сценарии экспериментов
--
-- Каждый эксперимент = серия из 4-х шагов:
--   1) пересоздать данные (gen_dataset)
--   2) выполнить EXPLAIN (план + cost)
--   3) выполнить EXPLAIN (ANALYZE, BUFFERS) ≥ 5 раз — для расчёта
--      среднего времени Execution time и СКО
--   4) перенести значения в Excel-таблицу
--
-- Запускать ОДНИ И ТЕ ЖЕ команды в обеих БД:
--   * sport_school_idx   — для строк "с индексами"
--   * sport_school_noidx — для строк "без индексов"
--
-- Для статистической чистоты — перед каждым ANALYZE-запуском желательно:
--     DISCARD ALL;
--     SELECT pg_stat_reset();
-- =====================================================================

------------------------------------------------------------------------
-- 0. БАЗОВЫЙ ИССЛЕДУЕМЫЙ ЗАПРОС
------------------------------------------------------------------------
-- Семантика:
--   "Найти учеников, которые занимаются хотя бы одной из тех секций,
--    по которой в указанном временном окне проводилась тренировка".
--
-- Соответствие шаблону задания
--    "SELECT * FROM tab1 WHERE [индекс1] IN (SELECT [индекс2] FROM tab2 WHERE ...)":
--    оператор IN заменён на && (пересечение массивов) — потому что
--    индексное поле tab1 имеет тип TEXT[], а GIN индексирует именно его.
--    Семантически && — это IN-проверка, обобщённая на массив.

-- :sel1 — селективность tab1 (доля учеников с 'Футбол'), %
-- :sel2 — селективность tab2 (длина окна в % от 5 лет)
-- :nstu — число строк в students
-- :ntra — число строк в trainings

------------------------------------------------------------------------
-- 1. ЭКСПЕРИМЕНТ 3.1 — фикс. кол-во строк, варьирование sel ПОДЗАПРОСА (tab2)
-- (по варианту: «1) с варьированием селективности поля в таблице подзапроса»)
------------------------------------------------------------------------
-- Зафиксировано: n_students = 1000, n_trainings = 1000, sel1 = 10%
-- Варьируется:   sel2 ∈ {1, 2, 3, 5, 10, 15, 20, 30} %

-- Пример одного шага для sel2 = 10 %:
CALL gen_dataset(1000, 1000, 10, 10);

-- Реальные селективности (проверка):
SELECT sel_tab1_actual_pct() AS actual_sel1_pct,
       sel_tab2_actual_pct(10) AS actual_sel2_pct;

-- Просмотр стоимости плана (без выполнения):
EXPLAIN
SELECT *
FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline
    FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

-- Реальное измерение времени (повторить N≥5 раз, усреднить):
EXPLAIN (ANALYZE, BUFFERS, TIMING ON, VERBOSE OFF)
SELECT *
FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline
    FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

-- Все шаги серии 3.1 (повторить для каждого значения sel2):
--   CALL gen_dataset(1000, 1000, 10, <sel2>);
--   EXPLAIN ... <тот же запрос с подстановкой sel2 в make_interval>
--   EXPLAIN (ANALYZE, BUFFERS) ... <то же>

------------------------------------------------------------------------
-- 2. ЭКСПЕРИМЕНТ 3.2 — фикс. кол-во строк, варьирование sel ВНЕШНЕЙ (tab1)
-- (по варианту: «2) с варьированием селективности поля внешней таблицы»)
------------------------------------------------------------------------
-- Зафиксировано: n_students = 1000, n_trainings = 1000, sel2 = 10%
-- Варьируется:   sel1 ∈ {1, 2, 3, 5, 10, 15, 20, 30} %

CALL gen_dataset(1000, 1000, 10, 10);  -- пример

EXPLAIN
SELECT *
FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline
    FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

EXPLAIN (ANALYZE, BUFFERS)
SELECT *
FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline
    FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

------------------------------------------------------------------------
-- 3. ЭКСПЕРИМЕНТ 3.3 — фикс. селективность (10%), варьирование числа строк
-- (по таблице 1, по варианту — внешняя таблица tab1)
------------------------------------------------------------------------
-- Зафиксировано:  sel1 = 10%, sel2 = 10%
-- Варьируется:    n_students = n_trainings ∈ {100, 1k, 10k, 100k, 1M}
--                 (для базового объёма достаточно {1k, 1M})

-- Шаблон шага:
--   CALL gen_dataset(<N>, <N>, 10, 10);
--   EXPLAIN ...           -- зафиксировать total cost
--   EXPLAIN (ANALYZE) ... -- повторить 5 раз, усреднить time

-- Пример 1k:
CALL gen_dataset(1000, 1000, 10, 10);
EXPLAIN
SELECT *
FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

EXPLAIN (ANALYZE, BUFFERS)
SELECT *
FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

-- Пример 1M (тяжёлый — выполнять последним):
--   CALL gen_dataset(1000000, 1000000, 10, 10);
--   EXPLAIN ...
--   EXPLAIN (ANALYZE, BUFFERS) ...

------------------------------------------------------------------------
-- 4. ЭКСПЕРИМЕНТ 3.4 — то же, что 3.3, но в БД sport_school_noidx
--    (без индексов). Скрипты идентичны.
------------------------------------------------------------------------

------------------------------------------------------------------------
-- 5. ОБСЛУЖИВАЮЩИЕ ЗАПРОСЫ
------------------------------------------------------------------------

-- Принудительная очистка кеша Linux/ОС невозможна из самой СУБД
-- (нужен sudo sysctl). В рамках одного сеанса psql можно сделать:
--   DISCARD ALL;
-- и/или перезапустить службу postgres, если хочется честно мерить
-- «холодные» обращения.

-- Текущие индексы в БД:
SELECT schemaname, tablename, indexname, indexdef
FROM pg_indexes
WHERE tablename IN ('students','trainings')
ORDER BY tablename, indexname;

-- Размер таблиц и индексов:
SELECT relname, pg_size_pretty(pg_relation_size(relid))      AS size,
                pg_size_pretty(pg_total_relation_size(relid)) AS total_size
FROM pg_catalog.pg_statio_user_tables
WHERE relname IN ('students','trainings');

-- Параметры планировщика (для записи в отчёт):
SHOW random_page_cost;
SHOW seq_page_cost;
SHOW cpu_tuple_cost;
SHOW cpu_index_tuple_cost;
SHOW cpu_operator_cost;
SHOW effective_cache_size;
SHOW shared_buffers;
SHOW work_mem;

-- Если индекс не выбирается планировщиком на маленьких объёмах:
--   SET enable_seqscan = off;
-- (для исследовательских целей; для отчёта лучше оставить настройки
--  по умолчанию и зафиксировать факт выбора Seq Scan).
