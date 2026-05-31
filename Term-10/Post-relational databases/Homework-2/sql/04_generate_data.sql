-- =====================================================================
-- ДЗ-2 ПБД, вариант 5 (GIN + BRIN), Пермяков Д.К.
-- Скрипт 04: процедуры генерации данных с заданной селективностью
--
-- ГЛАВНАЯ ИДЕЯ
--   * целевое значение GIN-поля        — секция 'Футбол'
--   * целевое значение BRIN-поля       — временной интервал
--                                        от START_DATE длительностью
--                                        sel2 * TOTAL_RANGE
--
--   sel1 (селективность tab1, %)  — доля учеников, у которых в массиве
--                                   disciplines есть 'Футбол'
--   sel2 (селективность tab2, %)  — доля тренировок, попадающих
--                                   во временной интервал
--
--   n_students  — число строк в tab1
--   n_trainings — число строк в tab2
--
-- ВЫПОЛНЯТЬ ОДИНАКОВО в обеих БД: sport_school_noidx и sport_school_idx
-- =====================================================================

-- ---------------------------------------------------------------------
-- Константы периода. START_DATE — начало шкалы дат, TOTAL_DAYS — длина.
-- Берём ровно 5 лет (1827 дней включает високосный год).
-- Эти же константы используются и в скриптах экспериментов.
-- ---------------------------------------------------------------------
CREATE OR REPLACE FUNCTION cfg_start_date()  RETURNS DATE     AS $$ SELECT DATE '2021-01-01' $$ LANGUAGE SQL IMMUTABLE;
CREATE OR REPLACE FUNCTION cfg_total_days()  RETURNS INTEGER  AS $$ SELECT 1827              $$ LANGUAGE SQL IMMUTABLE;

-- =====================================================================
-- Процедура генерации tab1 (students)
-- =====================================================================
CREATE OR REPLACE PROCEDURE gen_students(
    p_n_rows  INTEGER,
    p_sel_pct NUMERIC      -- 0..100 — желаемая селективность 'Футбол'
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_other_disciplines TEXT[] := ARRAY[
        'Баскетбол','Волейбол','Плавание','Лёгкая атлетика','Хоккей',
        'Гимнастика','Самбо','Бокс','Шахматы','Лыжи','Теннис',
        'Дзюдо','Каратэ','Настольный теннис','Художественная гимнастика'
    ];
    v_arr TEXT[];
    i     INTEGER;
    -- Сначала считаем, сколько строк должны содержать "Футбол". Например: gen_students(1000, 10) → v_n_with_target = 100.
    v_n_with_target INTEGER := FLOOR(p_n_rows * p_sel_pct / 100.0);
BEGIN
    -- Очищаем таблицу и сбрасываем последовательность.
    TRUNCATE TABLE students RESTART IDENTITY CASCADE;

    -- Сначала пишем строки С целевым значением 'Футбол',
    -- потом — без него. Так точная селективность гарантирована.
    FOR i IN 1 .. p_n_rows LOOP
        -- Базовый массив — 1..3 случайных дисциплины из "других".
        v_arr := ARRAY(
            SELECT v_other_disciplines[1 + FLOOR(random() * array_length(v_other_disciplines,1))::INT]
            FROM generate_series(1, 1 + FLOOR(random() * 3)::INT)
        );

        -- Для каждой строки сначала собирается «фон» — массив из 1–3 случайных дисциплин (исключая «Футбол»)
        IF i <= v_n_with_target THEN
            -- Добавляем целевую секцию, исключаем дубль.
            v_arr := ARRAY(SELECT DISTINCT unnest(v_arr || ARRAY['Футбол']));
        ELSE
            -- Гарантируем отсутствие 'Футбол' в массиве "не-целевых" строк.
            v_arr := ARRAY(SELECT DISTINCT unnest(v_arr) EXCEPT SELECT 'Футбол');
            IF array_length(v_arr,1) IS NULL THEN
                v_arr := ARRAY['Шахматы'];
            END IF;
        END IF;

        INSERT INTO students(full_name, birth_date, disciplines)
        VALUES (
            'Ученик_' || i,
            DATE '2008-01-01' + (FLOOR(random()*4000))::INT,
            v_arr
        );
    END LOOP;

    RAISE NOTICE 'students: вставлено % строк, из них с "Футбол" — % (≈ % %%)',
                 p_n_rows, v_n_with_target,
                 ROUND(100.0 * v_n_with_target / NULLIF(p_n_rows,0), 2);
END;
$$;

-- =====================================================================
-- Процедура генерации tab2 (trainings)
--   Записи вставляются в порядке возрастания training_date — это
--   принципиально для эффективности BRIN-индекса.
-- =====================================================================
CREATE OR REPLACE PROCEDURE gen_trainings(
    p_n_rows  INTEGER,
    p_sel_pct NUMERIC      -- 0..100 — желаемая селективность временного окна
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_disciplines TEXT[] := ARRAY[
        'Футбол','Баскетбол','Волейбол','Плавание','Лёгкая атлетика',
        'Хоккей','Гимнастика','Самбо','Бокс','Шахматы','Лыжи','Теннис',
        'Дзюдо','Каратэ','Настольный теннис','Художественная гимнастика'
    ];
    v_start          DATE     := cfg_start_date();
    v_total_days     INTEGER  := cfg_total_days();
    v_window_days    INTEGER  := GREATEST(1, FLOOR(v_total_days * p_sel_pct / 100.0)::INT);
    v_offset_seconds BIGINT;
    v_step_seconds   BIGINT;
    i                INTEGER;
BEGIN
    TRUNCATE TABLE trainings RESTART IDENTITY CASCADE;

    -- Считаем шаг «по времени». Например для gen_trainings(1000, ...) это будет 1827 × 86400 / 1000 ≈ 157 853 секунд ≈ 1.83 дня между соседними тренировками.
    -- Равномерно "размазываем" p_n_rows записей по полному периоду
    -- от v_start до v_start + v_total_days. Шаг = TOTAL_SECONDS / N.
    v_step_seconds := (v_total_days::BIGINT * 86400) / GREATEST(p_n_rows,1);

    FOR i IN 1 .. p_n_rows LOOP
        -- возьми начало моего слота и прибавь случайное число секунд, не выходящее за пределы шага.
        -- Так каждая запись попадает строго в свой годовой интервал, но в случайный момент внутри.
        v_offset_seconds := (i - 1)::BIGINT * v_step_seconds
                          + FLOOR(random() * v_step_seconds)::BIGINT;
        INSERT INTO trainings(student_id, discipline, training_date, duration_min)
        VALUES (
            1 + FLOOR(random() * 1000)::BIGINT,                                       -- ссылочное поле, не индексируется. Случайный student_id 1..1000
            v_disciplines[1 + FLOOR(random() * array_length(v_disciplines,1))::INT],  -- случайная дисциплина из 16
            v_start::TIMESTAMP + make_interval(secs => v_offset_seconds),             -- расчёт выше
            30 + FLOOR(random() * 90)::INT                                            -- длительность тренировки 30..119 минут
        );
    END LOOP;

    RAISE NOTICE 'trainings: вставлено % строк за период % .. % (длина окна = % дней ≈ % %%)',
                 p_n_rows,
                 v_start,
                 v_start + v_total_days,
                 v_window_days,
                 ROUND(100.0 * v_window_days / v_total_days, 2);
END;
$$;

-- =====================================================================
-- Удобная обёртка: за один вызов пересоздаёт обе таблицы и собирает
-- статистику. ВАЖНО: после массивной вставки ОБЯЗАТЕЛЬНО ANALYZE,
-- иначе планировщик не "увидит" реальной селективности.
-- =====================================================================
CREATE OR REPLACE PROCEDURE gen_dataset(
    p_n_students     INTEGER,
    p_n_trainings    INTEGER,
    p_sel_tab1_pct   NUMERIC,
    p_sel_tab2_pct   NUMERIC
)
LANGUAGE plpgsql
AS $$
BEGIN
    CALL gen_students (p_n_students,  p_sel_tab1_pct);
    CALL gen_trainings(p_n_trainings, p_sel_tab2_pct);

    ANALYZE students;
    ANALYZE trainings;

    RAISE NOTICE 'Готово. n_students=%, n_trainings=%, sel1=%%%, sel2=%%%',
                 p_n_students, p_n_trainings, p_sel_tab1_pct, p_sel_tab2_pct;
END;
$$;

-- ---------------------------------------------------------------------
-- Полезные служебные функции — посчитать ФАКТИЧЕСКУЮ селективность
-- (отличается от заданной из-за округлений).
-- ---------------------------------------------------------------------
CREATE OR REPLACE FUNCTION sel_tab1_actual_pct() RETURNS NUMERIC
LANGUAGE SQL STABLE AS $$
    SELECT ROUND(100.0 * COUNT(*) FILTER (WHERE disciplines @> ARRAY['Футбол']) / NULLIF(COUNT(*),0), 4)
    FROM students;
$$;

CREATE OR REPLACE FUNCTION sel_tab2_actual_pct(p_window_pct NUMERIC) RETURNS NUMERIC
LANGUAGE SQL STABLE AS $$
    WITH params AS (
        SELECT cfg_start_date()::TIMESTAMP AS d1,
               cfg_start_date()::TIMESTAMP +
                   make_interval(days => FLOOR(cfg_total_days() * p_window_pct / 100.0)::INT) AS d2
    )
    SELECT ROUND(100.0 * COUNT(*) FILTER (
        WHERE training_date >= (SELECT d1 FROM params)
          AND training_date <  (SELECT d2 FROM params)
    ) / NULLIF(COUNT(*),0), 4)
    FROM trainings;
$$;
