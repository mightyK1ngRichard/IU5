-- =====================================================================
-- ДЗ-2 ПБД, вариант 5 (GIN + BRIN), Пермяков Д.К.
-- Скрипт 06: пакетный прогон серий экспериментов
--
-- Для каждой пары (sel1, sel2, n_students, n_trainings) выполняется:
--   * пересоздание данных
--   * 1 раз EXPLAIN — получение плана и cost
--   * REPEATS раз EXPLAIN (ANALYZE) — получение времени
--
-- Результаты СВОДНОГО прогона пишутся в таблицу bench_results, откуда
-- их удобно выгрузить в CSV (\copy ... TO 'bench.csv' CSV HEADER)
-- и подцепить в Excel.
-- =====================================================================

CREATE TABLE IF NOT EXISTS bench_results (
    series        TEXT,         -- '3.1' / '3.2' / '3.3'
    db_kind       TEXT,         -- 'idx' / 'noidx'
    n_students    INTEGER,
    n_trainings   INTEGER,
    sel1_pct      NUMERIC,
    sel2_pct      NUMERIC,
    total_cost    NUMERIC,      -- из EXPLAIN (FORMAT JSON)
    exec_time_ms  NUMERIC,      -- из EXPLAIN (ANALYZE, FORMAT JSON)
    plan_node     TEXT,         -- название корневого узла плана
    measured_at   TIMESTAMPTZ DEFAULT now()
);

-- =====================================================================
-- Универсальная функция: один шаг измерения.
--   p_db_kind = 'idx' | 'noidx' — пишется в результат, физически
--   определяется текущей БД (psql \c).
-- =====================================================================
CREATE OR REPLACE PROCEDURE run_one_step(
    p_series       TEXT,
    p_db_kind      TEXT,
    p_n_students   INTEGER,
    p_n_trainings  INTEGER,
    p_sel1_pct     NUMERIC,
    p_sel2_pct     NUMERIC,
    p_repeats      INTEGER DEFAULT 5
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_sql      TEXT;
    v_explain  JSONB;
    v_cost     NUMERIC;
    v_time     NUMERIC;
    v_node     TEXT;
    v_avg_time NUMERIC := 0;
    v_window_days INTEGER;
    r INTEGER;
BEGIN
    -- 1) Пересоздаём данные.
    CALL gen_dataset(p_n_students, p_n_trainings, p_sel1_pct, p_sel2_pct);

    v_window_days := GREATEST(1, FLOOR(cfg_total_days() * p_sel2_pct / 100.0)::INT);

    -- 2) Базовый запрос как текст (подстановка окна).
    v_sql := format(
        $f$
        SELECT *
        FROM students s
        WHERE s.disciplines && ARRAY(
            SELECT DISTINCT t.discipline
            FROM trainings t
            WHERE t.training_date >= %L::TIMESTAMP
              AND t.training_date <  %L::TIMESTAMP + make_interval(days => %s)
        )
        $f$,
        cfg_start_date(), cfg_start_date(), v_window_days
    );

    -- 3) EXPLAIN (FORMAT JSON) — забираем cost и имя узла.
    EXECUTE 'EXPLAIN (FORMAT JSON) ' || v_sql INTO v_explain;
    v_cost := (v_explain -> 0 -> 'Plan' ->> 'Total Cost')::NUMERIC;
    v_node :=  v_explain -> 0 -> 'Plan' ->> 'Node Type';

    -- 4) EXPLAIN (ANALYZE, FORMAT JSON) — повторяем p_repeats раз
    --    и усредняем поле "Execution Time".
    FOR r IN 1 .. p_repeats LOOP
        EXECUTE 'EXPLAIN (ANALYZE, BUFFERS, FORMAT JSON) ' || v_sql INTO v_explain;
        v_time := (v_explain -> 0 ->> 'Execution Time')::NUMERIC;
        v_avg_time := v_avg_time + v_time;
        INSERT INTO bench_results(series, db_kind, n_students, n_trainings,
                                  sel1_pct, sel2_pct, total_cost,
                                  exec_time_ms, plan_node)
        VALUES (p_series, p_db_kind, p_n_students, p_n_trainings,
                p_sel1_pct, p_sel2_pct, v_cost, v_time, v_node);
    END LOOP;

    RAISE NOTICE 'series=% db=% n=(%/%) sel=(%/%) cost=% avg_time=% мс  node=%',
                 p_series, p_db_kind, p_n_students, p_n_trainings,
                 p_sel1_pct, p_sel2_pct, v_cost,
                 ROUND(v_avg_time / p_repeats, 3), v_node;
END;
$$;

-- =====================================================================
-- Готовый прогон БАЗОВОГО варианта (по п. 6.1 задания).
-- Подразумевается, что вы:
--   1) подключились к нужной БД (sport_school_idx или sport_school_noidx)
--   2) поставили нужное значение p_db_kind = 'idx' или 'noidx'.
-- =====================================================================
-- ПРИМЕР: запустить все 3 серии в БД С индексами
--
--   \c sport_school_idx
--   TRUNCATE bench_results;
--   DO $$
--   DECLARE s NUMERIC;
--   BEGIN
--     -- серия 3.1 — варьирование sel2 (подзапрос)
--     FOREACH s IN ARRAY ARRAY[1,2,3,5,10,15,20,30]::NUMERIC[] LOOP
--       CALL run_one_step('3.1','idx',1000,1000,10,s,5);
--     END LOOP;
--     -- серия 3.2 — варьирование sel1 (внешняя)
--     FOREACH s IN ARRAY ARRAY[1,2,3,5,10,15,20,30]::NUMERIC[] LOOP
--       CALL run_one_step('3.2','idx',1000,1000,s,10,5);
--     END LOOP;
--     -- серия 3.3 — варьирование числа строк, sel = 10%
--     CALL run_one_step('3.3','idx',     100,     100, 10, 10, 5);
--     CALL run_one_step('3.3','idx',    1000,    1000, 10, 10, 5);
--     CALL run_one_step('3.3','idx',   10000,   10000, 10, 10, 5);
--     CALL run_one_step('3.3','idx',  100000,  100000, 10, 10, 5);
--     CALL run_one_step('3.3','idx', 1000000, 1000000, 10, 10, 5);
--   END $$;
--
--   \copy (SELECT * FROM bench_results ORDER BY series, n_students, sel1_pct, sel2_pct, measured_at)
--         TO 'bench_idx.csv' WITH (FORMAT csv, HEADER true);
--
-- Затем то же самое в БД БЕЗ индексов:
--
--   \c sport_school_noidx
--   TRUNCATE bench_results;
--   DO $$ ... CALL run_one_step('3.1','noidx', ...);  ...  END $$;
--   \copy (SELECT * FROM bench_results ...) TO 'bench_noidx.csv' ...
