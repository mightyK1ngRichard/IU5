# Laboratory work 5.

## Creating tables.
```sql
-- Creating tables.
CREATE TABLE orders (
    orderID SERIAL PRIMARY KEY,
    orderDate DATE NOT NULL DEFAULT CURRENT_DATE,
    shipmentDate DATE NOT NULL DEFAULT CURRENT_DATE,
    paymentDate DATE NOT NULL DEFAULT CURRENT_DATE,
    status TEXT NOT NULL
);
CREATE TABLE customers (
    customerID SERIAL PRIMARY KEY NOT NULL,
    firstName TEXT NOT NULL DEFAULT 'Аноним',
    lastName TEXT NOT NULL DEFAULT 'Анонимов',
    address TEXT,
    city VARCHAR(20)
);
CREATE TABLE firms (
    firmID SERIAL PRIMARY KEY NOT NULL,
    firmName TEXT NOT NULL,
    address TEXT
);
CREATE TABLE items (
    itemID SERIAL PRIMARY KEY NOT NULL,
    quantity INT NOT NULL,
    total INT NOT NULL
);
CREATE TABLE products (
    productID SERIAL PRIMARY KEY NOT NULL,
    productName VARCHAR(50) NOT NULL,
    productPrice INT NOT NULL DEFAULT 20,
    inStock INT NOT NULL,
    reOrder BOOLEAN NOT NULL DEFAULT false
);
ALTER TABLE customers ADD firmID BIGINT REFERENCES firms(firmID);
ALTER TABLE orders ADD customerID INT NOT NULL REFERENCES customers(customerID);
ALTER TABLE items ADD orderID INT NOT NULL REFERENCES orders(orderID);
ALTER TABLE items ADD productID INT NOT NULL REFERENCES products(productID);

-- Inserting data.
INSERT INTO firms (FirmName, address)
VALUES
('Walmart', '25 Thurloe Square, London,SW7 2SD'),
('Amazon', 'Flat 4, Mayfair, Haselour Road, Birmingham,B37 6EG'),
('Apple', 'North Draycot Park Farm, Upper Seagry,SN15 5HB'),
('CVS Health', '5 Glengorse, Battle,TN33 0LJ'),
('UnitedHealth Group', '28 Abingdon Street, Derby,DE24 8FZ');
INSERT INTO customers (firmID, firstName, lastName, address, City)
VALUES
(1, 'Christopher', 'Brewer', '89661 Mann Orchard West Fernefurt, BC A4C-9L9', 'Clifton'),
(3, 'Walter', 'Baker', '14955 Roob Isle West Dasia, QC H0E9K7', 'Woonsocket'),
(5, 'Darryl', 'Thomas', '12671 Goldner Trail Apt. 183 South Kristophershire, NU J2P-7Y4', 'Clifton'),
(2, 'Donald', 'Walsh', '8149 Nico Valleys Apt. 312 Rhiannatown, SK X0K 1R7', 'Pagosa Springs'),
(1, 'John', 'Drake', '48497 Arlene Junction Lake Hannahview, BC L0C-6N9', 'Mount Westen'),
(3, 'Lean', 'Chandler', '298 Theresia Trail Apt. 004 Wuckertmouth, PE J3T-8V6', 'March'),
(4, 'David', 'Tucker', '5560 Deckow Flat Hegmannbury, NB V4K6X8', 'Emsworth'),
(2, 'Ken', 'Wright', '729 Orval Junctions Apt. 222 Christiansenchester, PE J1L0Y4', 'Kirton-in-Lindsey'),
(4, 'James', 'Perez', '6790 Kavon Brooks Suite 877 West Aliya, NS C6V 5S5', 'Basildon'),
(1, 'Paul', 'Briggs', '637 Shanahan Forges New Elbert, BC C3X0V3', 'Clifton'),
(2, 'Marie', 'Garza', '934 Filomena Track Suite 841 Durganfurt, NT L9Y8T4', 'Alnwick'),
(5, 'Kenneth', 'Campbell', '1993 Andres Flats Apt. 683 Aufderharfurt, NL R4B 8T8', 'Wincanton'),
(3, 'Angela', 'Vaughn', '805 Marietta Stravenue Apt. 282 Libbiehaven, SK C9K-9M7', 'Midhurst'),
(2, 'Richard', 'Guerrero', '472 Zemlak Burg Apt. 626 Krajcikbury, NS T5B-6M8', 'Clifton'),
(1, 'Sandra', 'Webb', '349 Gulgowski Estate Suite 153 Lake Reyeston, NS L2X 2V1', 'Ashington'),
(2, 'Bonnie', 'Cruz', '5784 Simonis Spring Suite 907 Lockmanburgh, MB B6N 3V6', 'Inglewood');
INSERT INTO products (productName, productPrice, inStock, reOrder)
VALUES
('bacon', '16', 51, true),
('beef', '62', 85, DEFAULT),
('chicken', '46', 10, true),
('duck', '91', 1, true),
('ham', '4', 31, DEFAULT),
('lamb', '98', 21, DEFAULT),
('liver', '51', 52, true),
('meat', '75', 57, DEFAULT),
('mutton', '81', 56, DEFAULT),
('partridge', '78', 5, true),
('pork', '44', 72, DEFAULT),
('poultry', '35', 44, DEFAULT),
('sausage', '20', 89, DEFAULT),
('tenderloin', '3', 82, DEFAULT),
('turkey', '19', 4, true),
('veal', '42', 87, DEFAULT),
('venison', '2', 47, true);
INSERT INTO Orders (customerID, orderDate, shipmentDate, paymentDate, status)
VALUES
(3, '2022-09-17', '2020-07-30', '2020-08-30', 'P'),
(5, '2020-11-25', '2022-08-28', '2022-09-28', 'F'),
(2, '2020-05-06', '2019-06-22', '2019-07-22', 'P'),
(1, '2020-11-02', '2022-09-26', '2022-10-26', 'F'),
(4, '2020-08-06', '2021-01-28', '2021-02-28', 'F'),
(5, '2019-06-20', '2020-05-09', '2020-06-09', 'P'),
(3, '2020-11-16', '2022-05-28', '2022-06-28', 'P'),
(2, '2019-01-24', '2020-11-23', '2020-12-23', 'F'),
(3, '2020-01-03', '2020-02-08', '2020-02-08', 'P'),
(5, '2022-09-17', '2022-07-10', '2022-08-10', 'P'),
(4, '2022-01-14', '2019-05-14', '2019-06-14', 'P'),
(1, '2022-02-07', '2019-06-23', '2019-07-23', 'F');
INSERT INTO items(orderID, productID, quantity, total)
VALUES
    ('1', '1', '10', 0),
    ('2', '2', '20', 0),
    ('3', '3', '30', 0),
    ('4', '4', '40', 0),
    ('5', '5', '50', 0),
    ('6', '6', '60', 0),
    ('7', '7', '70', 0),
    ('8', '8', '80', 0);

-- PATH 1.

-- b. Хранимую процедуру для поиска информации по названию компании.

SELECT f.firmName, COUNT(c.customerID)
FROM firms f
JOIN customers c ON (f.firmID = c.firmID)
WHERE f.firmName = 'Amazon'
GROUP BY f.firmID;

-- 1. Method from the manual.

CREATE PROCEDURE GetFirmInfo (parFirmName TEXT)
LANGUAGE SQL AS $$
 		SELECT f.firmName, COUNT(c.customerID)
 		FROM firms f
        JOIN customers c ON (f.firmID = c.firmID)
        WHERE f.firmName = parFirmName
        GROUP BY f.firmID
$$;

CALL GetFirmInfo('Walmart');

-- 2. My method. [X]

CREATE OR REPLACE FUNCTION GetFirmInfo2(parFirmName TEXT) RETURNS TABLE (
    firm_name TEXT,
    customer_count INTEGER
)  AS
$$
    SELECT f.firmName, COUNT(c.customerID)
    FROM firms f
    JOIN customers c ON (f.firmID = c.firmID)
    WHERE f.firmName = parFirmName
    GROUP BY f.firmID
$$ LANGUAGE sql;

SELECT * FROM GetFirmInfo2('Amazon');


-- c. Хранимую процедуру для поиска товаров по диапазону цен.
SELECT *
FROM products
WHERE productPrice BETWEEN 0 AND 10;

-- 1. Method from manual.

CREATE PROCEDURE GetProductsByPriceRange (minPrice INT, maxPrice INT)
LANGUAGE SQL AS $$
    SELECT *
    FROM products
    WHERE productPrice BETWEEN minPrice AND maxPrice
$$;
CALL GetProductsByPriceRange(0, 10);

-- 2. My method. [X]

CREATE OR REPLACE FUNCTION GetProductsByPriceRange2(minPrice INT, maxPrice INT) RETURNS SETOF products AS
$$
  SELECT *
    FROM products
    WHERE productPrice BETWEEN minPrice AND maxPrice
$$ LANGUAGE sql;

SELECT * FROM GetProductsByPriceRange2(0, 10);

-- d. Хранимую процедуру для поиска заказов по дате заказа и диапазону дат заказа, доставки.

-- Method from manual.
CREATE PROCEDURE GetProductsByOrderDate(parOrderDate Date)
LANGUAGE SQL AS $$
  SELECT *
    FROM Orders o
    WHERE  o.orderDate = parOrderDate
$$;
CREATE PROCEDURE GetProductsByShipDateRange(MinShipDate Date, MaxShipDate Date)
LANGUAGE SQL AS $$
    SELECT *
    FROM Orders o
    WHERE o.shipmentDate > MinShipDate AND o.shipmentDate < MaxShipDate
$$;
CALL GetProductsByOrderDate('2022-09-17');
CALL GetProductsByShipDateRange('2021-09-17', '2023-09-17');

-- 2. My method. [X]

CREATE OR REPLACE FUNCTION GetProductsByOrderDate2(parOrderDate Date) RETURNS SETOF orders AS
$$
  SELECT *
    FROM Orders o
    WHERE  o.orderDate = parOrderDate
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION GetProductsByShipDateRange2(MinShipDate Date, MaxShipDate Date) RETURNS SETOF Orders AS
$$
  SELECT *
    FROM Orders o
    WHERE o.shipmentDate > MinShipDate AND o.shipmentDate < MaxShipDate
$$ LANGUAGE sql;

SELECT * FROM GetProductsByOrderDate2('2022-09-17');
SELECT * FROM  GetProductsByShipDateRange2('2021-09-17', '2023-09-17');

-- e. Хранимые процедуры по заданию варианта.
-- Creating selection.
SELECT c.customerID, c.firstName, c.lastName, c.address, c.city
FROM orders o
RIGHT JOIN customers c ON o.customerID = c.customerID
WHERE o.orderID is NULL;
SELECT o.customerID, SUM(i.quantity * p.productPrice) as total
FROM orders o
LEFT JOIN customers c ON o.customerID = c.customerID
RIGHT JOIN items i ON o.orderID = i.orderID
JOIN products p ON i.productID = p.productID
WHERE c.city = 'Clifton'
GROUP BY o.customerID;

-- Creating functions.

CREATE OR REPLACE FUNCTION getCustomersInfoNotExistInOrders() RETURNS TABLE (
    id INTEGER,
    name TEXT,
    surname TEXT,
    address TEXT,
    city TEXT
)  AS
$$
  SELECT c.customerID, c.firstName, c.lastName, c.address, c.city
    FROM orders o
    RIGHT JOIN customers c ON o.customerID = c.customerID
    WHERE o.orderID is NULL;
$$ LANGUAGE sql;
CREATE OR REPLACE FUNCTION getSpentMoneyCustomerFromCity(parCity VARCHAR(20)) RETURNS TABLE (
    id INTEGER,
    spentMoney INTEGER
)  AS
$$
  SELECT o.customerID, SUM(i.quantity * p.productPrice) as total
    FROM orders o
    LEFT JOIN customers c ON o.customerID = c.customerID
    RIGHT JOIN items i ON o.orderID = i.orderID
    JOIN products p ON i.productID = p.productID
    WHERE c.city = parCity
    GROUP BY o.customerID;
$$ LANGUAGE sql;

SELECT * FROM getCustomersInfoNotExistInOrders();
SELECT * FROM getSpentMoneyCustomerFromCity('Clifton');

-- Additional task.

CREATE OR REPLACE FUNCTION test(MinShipDate Date = '2020-09-17', MaxShipDate Date = CURRENT_DATE )
RETURNS TABLE(orderID integer, orderDate Date, shipmentDate Date, paymentdate Date, status Text)
    AS $$
BEGIN
    IF MinShipDate < '2020-09-17' THEN
        MinShipDate = '2020-09-17';
    end if;
    IF MaxShipDate > CURRENT_DATE THEN
        MaxShipDate = CURRENT_DATE;
    end if;

    RETURN QUERY
    SELECT o.orderID, o.orderDate, o.shipmentDate, o.paymentdate, o.status
    FROM Orders o
    WHERE o.shipmentDate > MinShipDate AND o.shipmentDate < MaxShipDate;

END;
$$ LANGUAGE plpgsql;

SELECT test('1921-09-17', '2025-04-18');
SELECT test();


-- *************** PATH 2. ***************
-- DROP TRIGGER IF EXISTS trigger_name ON my_insert_trigger;
-- DROP TRIGGER IF EXISTS my_insert_trigger ON products;

-- Insert trigger.
CREATE TABLE products_log (
    productLogID SERIAL PRIMARY KEY NOT NULL,
    additionDate DATE DEFAULT CURRENT_DATE,
    productID INTEGER
);

CREATE OR REPLACE FUNCTION insert_product_log() RETURNS TRIGGER AS
$$
BEGIN
    IF (TG_OP = 'INSERT' or TG_OP = 'UPDATE') THEN
    INSERT INTO products_log (additionDate, productID)
    VALUES (CURRENT_DATE, NEW.productID);
    end if;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER my_insert_trigger
AFTER INSERT OR UPDATE ON products
FOR EACH ROW
EXECUTE FUNCTION insert_product_log();

INSERT INTO products (productName, productPrice, inStock) VALUES('Тест1', '777', '12');
UPDATE products SET productName='НОВАЯ' WHERE productID = 2;

----------
CREATE TABLE my_other_table (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    address VARCHAR(255) NOT NULL
);

CREATE OR REPLACE FUNCTION my_trigger_with_temp_table()
RETURNS TRIGGER AS $$
BEGIN
    CREATE TEMPORARY TABLE Inserted AS SELECT NEW.*;
    INSERT INTO my_other_table (name, address)
    SELECT NEW.firmname, NEW.address FROM Inserted;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER my_trigger
AFTER INSERT OR UPDATE ON firms
FOR EACH ROW
EXECUTE FUNCTION my_trigger_with_temp_table();

INSERT INTO firms (firmName, address) VALUES ('что-то', 'где-то');

```