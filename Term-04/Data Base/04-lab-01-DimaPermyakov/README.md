# Laboratory work №1.

## Work with postgresql in macOS:
```zsh
brew services start postgresql@15
brew services stop postgresql@15
```

## Creating tables:
```sql
CREATE TABLE supplier (
	supplier_id bigserial not null primary key,
	name_supplier varchar(50) NOT NULL,
	telephone varchar,
	WWW varchar(150)
);

CREATE TABLE delivery (
	delivery_id bigserial not null primary key,
	date_delivery DATE DEFAULT CURRENT_DATE,
	numbers_packets INT DEFAULT 0,
	price_order INT
);

CREATE TABLE fertilizer (
	fertilizer_id bigserial not null primary key,
	fertilizer_name VARCHAR(50) NOT NULL,
	price INT NOT NULL,
	mass INT NOT NULL
);

CREATE TABLE type_tree (
	type_id bigserial not null primary key,
	name_type varchar(50) not null,
	notes varchar(150)
);

CREATE TABLE tree (
	tree_id bigserial not null primary key,
	name_tree varchar(50) not null,
	volume INT not null CONSTRAINT negative_number CHECK (volume > 0),
	date_measurements DATE DEFAULT CURRENT_DATE,
	notes varchar(150),
	type_tree_id int REFERENCES type_tree(type_id)
);

CREATE TABLE plot (
	plot_id bigserial not null primary key,
	name_plot varchar(50) not null,
	date_planting DATE DEFAULT CURRENT_DATE,
	type_tree_id int REFERENCES type_tree(type_id) not null,
	address varchar(200) not null
);

CREATE TABLE coordinates (
	coordinates_id bigserial not null primary key,
	tree_id int REFERENCES tree(tree_id) not null,
	x_begin int CONSTRAINT negative_x_begin CHECK (x_begin >= 0) not null,
	x_end int CONSTRAINT negative_x_end CHECK (x_end >= 0) not null,
	y_begin int CONSTRAINT negative_y_begin CHECK (y_begin >= 0) not null,
	y_end int CONSTRAINT negative_y_end CHECK (y_end >= 0) not null
);

CREATE TABLE watering (
	watering_id bigserial not null primary key,
	date_watering DATE DEFAULT CURRENT_DATE,
	plot_id int REFERENCES plot(plot_id) not null
);

CREATE TABLE employer (
	employer_id bigserial not null primary key,
	full_name varchar(50) not null,
	post varchar(30) not null,
	phone_number varchar(12)
);
```

## Adding the foreign keys:

```sql
ALTER TABLE delivery ADD supplier_id BIGINT REFERENCES supplier(supplier_id);

ALTER TABLE delivery ADD fertilizer_id BIGINT REFERENCES fertilizer(fertilizer_id);

ALTER TABLE fertilizer ADD type_tree_id BIGINT REFERENCES type_tree(type_id);

ALTER TABLE tree ADD plot_id BIGINT REFERENCES plot(plot_id);

ALTER TABLE plot ADD employer_id BIGINT REFERENCES employer(employer_id);
```
