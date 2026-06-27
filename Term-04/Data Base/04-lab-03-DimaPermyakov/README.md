# Laboratory work 3.

```zsh
/Library/PostgreSQL/15/scripts/runpsql.sh      
```

```sql
-- Create the tables.
CREATE TABLE lab03 (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    salary INTEGER NOT NULL
);

CREATE TABLE lab03_2 (
    id SERIAL PRIMARY KEY,
    post VARCHAR(255) NOT NULL,
    note VARCHAR(255)
);

-- Create the views.
CREATE VIEW viewgetinfo AS
SELECT * FROM lab03;

-- Add the data using the view.
INSERT INTO viewgetinfo (name, salary)
VALUES
    ('Dima1', 1),
    ('Dima2', 2),
    ('Dima3', 3);

-- Compare the view's data with the table's data.
SELECT * FROM viewgetinfo;
SELECT * FROM lab03;

-- Alter view's functions. [TROUBLE WITH IT]
ALTER VIEW viewgetinfo AS
SELECT name as workerName, salary as workerSalary
FROM lab03
WHERE salary < 3;

-- Create the view with the checking.
CREATE VIEW viewwithoptions AS
SELECT * FROM lab03
WHERE salary > 2 WITH CHECK OPTION;

-- Drop the view.
DROP VIEW viewgetinfo;
```

# Second part:
```sql
-- Creating the role & user. Sign the user to the role.
CREATE ROLE test_creator CREATEDB CREATEROLE NOLOGIN;
CREATE USER "user1" WITH PASSWORD '1111';
GRANT test_creator TO user1;

-- Creating the roles and the users for a work with the table.
CREATE ROLE withoutrule NOCREATEDB NOCREATEROLE;
CREATE USER "user_no_rule" WITH PASSWORD '1111';
CREATE ROLE withrule CREATEDB NOCREATEROLE;
CREATE USER "user_rule" WITH PASSWORD '1111';
-- Add the permission to work with the db.
GRANT SELECT, INSERT, UPDATE, DELETE on TABLE postgres.public.delivery TO withrule;
-- Sign the users to their roles.
GRANT withoutrule TO "user_no_rule";
GRANT withrule TO "user_rule";

-- Deleting the permission.
REVOKE INSERT ON delivery FROM withrule;

-- Deleting all the roles.
drop role user1;
drop role user_no_rule;
drop role user_rule;
drop role withrule;
drop role withoutrule;
drop role test_creator;
```
