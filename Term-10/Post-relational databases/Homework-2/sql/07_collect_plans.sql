-- =====================================================================
-- ДЗ-2 ПБД, вариант 5 (GIN + BRIN), Пермяков Д.К.
-- Скрипт 07: сбор полных текстов EXPLAIN для Приложения Б отчёта
--
-- ВЫПОЛНИТЬ ДВАЖДЫ:
--   1) \c sport_school_idx    \i 07_collect_plans.sql  > plans_idx.txt
--   2) \c sport_school_noidx  \i 07_collect_plans.sql  > plans_noidx.txt
-- =====================================================================

\pset format aligned
\pset border 0
\pset null '∅'
\set ECHO all

------------------------------------------------------------------------
-- ПЛАН 1.  Серия 3.1, sel2 = 3 %, N = 1000, sel1 = 10 %
------------------------------------------------------------------------
CALL gen_dataset(1000, 1000, 10, 3);

EXPLAIN (VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*3/100.0)::INT)
);

EXPLAIN (ANALYZE, BUFFERS, VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*3/100.0)::INT)
);

------------------------------------------------------------------------
-- ПЛАН 2.  Серия 3.1, sel2 = 20 %, N = 1000
------------------------------------------------------------------------
CALL gen_dataset(1000, 1000, 10, 20);

EXPLAIN (VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*20/100.0)::INT)
);

EXPLAIN (ANALYZE, BUFFERS, VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*20/100.0)::INT)
);

------------------------------------------------------------------------
-- ПЛАН 3.  Серия 3.2, sel1 = 1 %, N = 1000
------------------------------------------------------------------------
CALL gen_dataset(1000, 1000, 1, 10);

EXPLAIN (VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

EXPLAIN (ANALYZE, BUFFERS, VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

------------------------------------------------------------------------
-- ПЛАН 4.  Серия 3.2, sel1 = 30 %, N = 1000
------------------------------------------------------------------------
CALL gen_dataset(1000, 1000, 30, 10);

EXPLAIN (VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

EXPLAIN (ANALYZE, BUFFERS, VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

------------------------------------------------------------------------
-- ПЛАН 5.  Серия 3.3, N = 1 000, sel = 10 %
------------------------------------------------------------------------
CALL gen_dataset(1000, 1000, 10, 10);

EXPLAIN (VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

EXPLAIN (ANALYZE, BUFFERS, VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

------------------------------------------------------------------------
-- ПЛАН 6.  Серия 3.3, N = 1 000 000, sel = 10 %    *** САМЫЙ ВАЖНЫЙ ***
------------------------------------------------------------------------
CALL gen_dataset(1000000, 1000000, 10, 10);

EXPLAIN (VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

EXPLAIN (ANALYZE, BUFFERS, VERBOSE)
SELECT * FROM students s
WHERE s.disciplines && ARRAY(
    SELECT DISTINCT t.discipline FROM trainings t
    WHERE t.training_date >= cfg_start_date()::TIMESTAMP
      AND t.training_date <  cfg_start_date()::TIMESTAMP
                            + make_interval(days => FLOOR(cfg_total_days()*10/100.0)::INT)
);

------------------------------------------------------------------------
-- ПАРАМЕТРЫ СРЕДЫ — пригодятся для Главы 6.1 отчёта
------------------------------------------------------------------------
SELECT version();
SHOW shared_buffers;
SHOW work_mem;
SHOW effective_cache_size;
SHOW random_page_cost;
SHOW seq_page_cost;
SHOW cpu_tuple_cost;
SHOW cpu_index_tuple_cost;
SHOW max_parallel_workers_per_gather;

------------------------------------------------------------------------
-- РАЗМЕРЫ ТАБЛИЦ И ИНДЕКСОВ (после последнего CALL — 1 млн строк)
------------------------------------------------------------------------
SELECT relname,
       pg_size_pretty(pg_relation_size(relid))      AS heap_size,
       pg_size_pretty(pg_total_relation_size(relid))AS total_size
FROM pg_catalog.pg_statio_user_tables
WHERE relname IN ('students','trainings')
ORDER BY relname;

SELECT indexrelname,
       pg_size_pretty(pg_relation_size(indexrelid)) AS index_size
FROM pg_catalog.pg_stat_user_indexes
WHERE relname IN ('students','trainings')
ORDER BY relname, indexrelname;
