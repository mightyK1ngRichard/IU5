# Laboratory work №2.

## General task:
```SQL
SELECT * FROM prices;

SELECT product_id, price FROM prices;

SELECT * FROM prices
ORDER BY price;

SELECT * FROM prices
ORDER BY price
LIMIT  5;

SELECT * FROM prices
WHERE price > 5000;

SELECT * FROM prices
WHERE start_date BETWEEN '2019-01-01' AND '2019-01-29';

SELECT * FROM prices
WHERE product_id in (1,2,3);

SELECT * FROM products
WHERE products.category LIKE 'м%';

SELECT * FROM sales
WHERE customer_id is not null;

SELECT COUNT(product_id) FROM prices
WHERE product_id = 4;

SELECT avg(price), product_id
FROM prices
WHERE start_date >= '2022-01-01' AND start_date <= '2022-12-31'
GROUP BY product_id
HAVING round(avg(price) , -3) = 17000 

SELECT sale_date, name
FROM sales
INNER JOIN customers c on c.customer_id = sales.customer_id;

SELECT DISTINCT region FROM stores;

SELECT name FROM customers
WHERE EXISTS (
    SELECT DISTINCT customer_id FROM sales
    WHERE customer_id is not NULL
)
```

## Personal task:
### Задание: 
1. Продукты, чаще всего покупаемые, 5 шт.
2. На какую сумму какой покупатель назаказывал.

```SQL
SELECT product_id, count(product_id) as counter
FROM sales
GROUP BY product_id
ORDER BY counter DESC
LIMIT 5 

-- Идея: Смотрим кто на сколько накупил в один определённый день, учитывая текущую цену. 
SELECT customers.customer_id, customers.surname, customers.name, sum(prices.price)
FROM customers
INNER JOIN sales ON sales.customer_id = customers.customer_id
INNER JOIN prices ON sales.product_id = prices.product_id
WHERE sales.sale_date = '2019-01-01' AND prices.start_date <= '2019-01-01' AND prices.end_date >= '2019-01-01'
GROUP BY customers.customer_id, customers.surname, customers.name;
```
