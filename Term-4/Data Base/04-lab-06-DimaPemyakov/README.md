# Laboratory work 6.

## Creating tables.
```sql
create table users (
    id      serial primary key,
    name    varchar(255),
    surname varchar(255),
    address varchar(255)
);

COPY users FROM '/Users/dmitriy/data.csv' DELIMITER ',' CSV HEADER;
COPY users TO '/tmp/data2.csv' DELIMITER ',' CSV HEADER;

-- Commands for the terminal:
-- pg_dump postgres -h localhost -p 8080 -U postgres > dump_dump.sql
-- psql lab06_for_dump < dump_dump.sql -U postgres -h localhost -p 8080
-- tar -cf backup.tar /Library/PostgreSQL/15/data

```