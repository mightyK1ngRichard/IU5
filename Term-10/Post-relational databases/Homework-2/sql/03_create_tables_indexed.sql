-- =====================================================================
-- ДЗ-2 ПБД, вариант 5 (GIN + BRIN), Пермяков Д.К.
-- Скрипт 03: создание таблиц с индексами GIN и BRIN
-- Выполнять в базе sport_school_idx
-- =====================================================================

DROP TABLE IF EXISTS trainings CASCADE;
DROP TABLE IF EXISTS students  CASCADE;

-- ---------------------------------------------------------------------
-- tab1: ученики + GIN по массиву секций
-- ---------------------------------------------------------------------
CREATE TABLE students (
    student_id  BIGSERIAL PRIMARY KEY,
    full_name   TEXT      NOT NULL,
    birth_date  DATE      NOT NULL,
    disciplines TEXT[]    NOT NULL
);

-- ВАРИАНТНЫЙ ИНДЕКС № 1 — GIN на TEXT[]
-- GIN — Generalized Inverted Index, обратный индекс: каждому элементу
-- (виду спорта) сопоставляется упорядоченный список TID-ов строк,
-- в массивах которых этот элемент встречается. Поддерживает операторы
-- @>, <@, &&, = ANY(...) и т.п. для типов "коллекций".
CREATE INDEX idx_students_disciplines_gin
    ON students
    USING gin (disciplines);

COMMENT ON INDEX idx_students_disciplines_gin
    IS 'GIN-индекс на массив секций (вариантный, ДЗ-2)';

-- ---------------------------------------------------------------------
-- tab2: тренировки + BRIN по дате тренировки
-- ---------------------------------------------------------------------
CREATE TABLE trainings (
    training_id   BIGSERIAL  PRIMARY KEY,
    student_id    BIGINT     NOT NULL,
    discipline    TEXT       NOT NULL,
    training_date TIMESTAMP  NOT NULL,
    duration_min  INT        NOT NULL
);

-- ВАРИАНТНЫЙ ИНДЕКС № 2 — BRIN на TIMESTAMP
-- BRIN — Block Range INdex: хранит для каждого диапазона страниц
-- агрегированную "сводку" (min/max значений), не сами значения и не
-- TID-ы строк. Очень компактный, но эффективен только если данные
-- физически упорядочены по индексируемому полю — что и обеспечивается
-- генератором (даты тренировок вставляются по возрастанию).
CREATE INDEX idx_trainings_date_brin
    ON trainings
    USING brin (training_date)
    WITH (pages_per_range = 32);

COMMENT ON INDEX idx_trainings_date_brin
    IS 'BRIN-индекс на дату тренировки (вариантный, ДЗ-2)';
