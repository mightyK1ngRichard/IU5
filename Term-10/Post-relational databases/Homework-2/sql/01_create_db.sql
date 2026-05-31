-- =====================================================================
-- ДЗ-2 по курсу «Постреляционные базы данных»
-- Вариант: Задание 5 (GIN + BRIN), Пермяков Д.К.
-- Скрипт 01: создание двух баз данных
--   * sport_school_noidx  — без индексов (контрольная)
--   * sport_school_idx    — с индексами GIN (на tab1) и BRIN (на tab2)
-- Выполнять из роли с правом CREATE DATABASE (например, postgres).
-- =====================================================================

DROP DATABASE IF EXISTS sport_school_noidx;
DROP DATABASE IF EXISTS sport_school_idx;

CREATE DATABASE sport_school_noidx
    WITH ENCODING = 'UTF8'
         LC_COLLATE = 'C'
         LC_CTYPE   = 'C'
         TEMPLATE   = template0;

CREATE DATABASE sport_school_idx
    WITH ENCODING = 'UTF8'
         LC_COLLATE = 'C'
         LC_CTYPE   = 'C'
         TEMPLATE   = template0;

COMMENT ON DATABASE sport_school_noidx IS 'ДЗ-2 ПБД, вариант 5, копия без индексов';
COMMENT ON DATABASE sport_school_idx   IS 'ДЗ-2 ПБД, вариант 5, копия c индексами GIN + BRIN';

-- Далее подключитесь к каждой БД и выполните соответствующий скрипт:
--   \c sport_school_noidx
--   \i 02_create_tables_noindex.sql
--   \i 04_generate_data.sql
--
--   \c sport_school_idx
--   \i 03_create_tables_indexed.sql
--   \i 04_generate_data.sql
