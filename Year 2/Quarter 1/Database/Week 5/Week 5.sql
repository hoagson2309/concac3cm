-- EXERCISE 1: 
-- 2.Delete the database you just created (DVDfilms)
IF DB_ID(N'DVDfilms') IS NOT NULL
BEGIN
    PRINT 'Dropping existing database [DVDfilms]';
    ALTER DATABASE [DVDfilms] SET SINGLE_USER WITH ROLLBACK IMMEDIATE;
    DROP DATABASE [DVDfilms];
END

--3.Create (again) the DVDfilms Database to hold data for this exercise.
CREATE DATABASE [DVDfilms];

--set [DVDfilms] to multiple users
USE [master];
ALTER DATABASE [DVDfilms] SET MULTI_USER WITH ROLLBACK IMMEDIATE;

--then use [DVDfilms]
USE [DVDfilms];




--4.Show the list of databases on an instance of SQL server. 
SELECT name, database_id, create_date
FROM sys.databases;


--EXERCISE 2: Create category table and insert data
IF OBJECT_ID('dbo.category', 'U') IS NOT NULL DROP TABLE dbo.category;


CREATE TABLE dbo.category (
    category_id INT NOT NULL CONSTRAINT PK_category PRIMARY KEY CLUSTERED, 
    name VARCHAR(25) NOT NULL  --text column up to 25 characters
);


--Add some data to CATEGORY
INSERT INTO dbo.category (category_id, name)
VALUES
    (1, 'Action'), (2, 'Animation'), (3, 'Children'), (4, 'Classics'), (5, 'Comedy'),
    (6, 'Documentary'), (7, 'Drama'), (8, 'Family'), (9, 'Foreign'), (10, 'Games'),
    (11, 'Horror'), (12, 'Music'), (13, 'New'), (14, 'Sci-Fi'), (15, 'Sports'), (16, 'Travel');

--Verify the category table contents
SELECT * FROM dbo.category;

--Exercise 3: Create a table and add data based on another existing table 
--Create the FILM table in the new DVDfilms database from the existing one in the DVDrental database, based on the SELECT query result set. 

-- If film already exists in DVDfilms, drop it so SELECT INTO can run repeatedly
IF OBJECT_ID('dbo.film', 'U') IS NOT NULL DROP TABLE dbo.film;


--Create FILM table and copy data from dvdrental.dbo.film  (SELECT INTO only copies columns + data, but not indexes, PKs, or constraints)
SELECT *
INTO dbo.film
FROM dvdrental.dbo.film;

--Count imported rows
SELECT COUNT(*) AS film_rows_imported FROM dbo.film;

--Add a Primary Key (PK) constraint to FILM( film_id) since SELECT INTO does not create PKs
    ALTER TABLE dbo.film
    ADD CONSTRAINT PK_film PRIMARY KEY CLUSTERED (film_id);

-- Verify PKs in the database (list PK constraints)
SELECT name, type, unique_index_id, is_system_named
FROM sys.key_constraints
WHERE type = 'PK';

--Add DEFAULT values to FILM
--a) rental_duration default (3days)
IF NOT EXISTS(SELECT * FROM sys.default_constraints WHERE parent_object_id = OBJECT_ID('dbo.film') AND name = 'DF_film_rental_duration')
BEGIN
    ALTER TABLE dbo.film
    ADD CONSTRAINT DF_film_rental_duration DEFAULT ((3)) FOR rental_duration;
END

--b) rental_rate default (4.99)
IF NOT EXISTS (SELECT * FROM sys.default_constraints WHERE parent_object_id = OBJECT_ID('dbo.film') AND name = 'DF_film_rental_rate')
BEGIN
    ALTER TABLE dbo.film
    ADD CONSTRAINT DF_film_rental_rate DEFAULT ((4.99)) FOR rental_rate;
END

--c) replacement_cost default (19.99)
IF NOT EXISTS (SELECT * FROM sys.default_constraints WHERE parent_object_id = OBJECT_ID('dbo.film') AND name = 'DF_film_replacement_cost')
BEGIN
    ALTER TABLE dbo.film
    ADD CONSTRAINT DF_film_replacement_cost DEFAULT ((19.99)) FOR replacement_cost;
END

--d) rating default (G)
IF NOT EXISTS (SELECT * FROM sys.default_constraints WHERE parent_object_id = OBJECT_ID('dbo.film') AND name = 'DF_film_rating')
BEGIN
    ALTER TABLE dbo.film
    ADD CONSTRAINT DF_film_rating DEFAULT ('G') FOR rating;
END

--Inspect defaults
SELECT dc.name AS DefaultName, t.name AS TableName, c.name AS ColumnName, dc.definition
FROM sys.default_constraints dc
JOIN sys.columns c ON dc.parent_column_id = c.column_id AND dc.parent_object_id = c.object_id
JOIN sys.tables t ON c.object_id = t.object_id
WHERE t.name = 'film'

--Exercise 4: Create the schema of a table and add data based on another existing table 
--drop if existed
IF OBJECT_ID('dbo.film_category', 'U') IS NOT NULL
BEGIN
    DROP TABLE dbo.film_category;
END

--Create the FILM_CATEGORY table and define two attributes as a concatenated PK.
CREATE TABLE dbo.film_category (
    film_id INT NOT NULL,
    category_id INT NOT NULL,
    CONSTRAINT PK_film_category PRIMARY KEY CLUSTERED (film_id ASC, category_id ASC)   --ADD CONSTRAINT only use in ALTER TABLE
);

--15. Add the Foreign key constraints to film_category, referencing dbo.film and dbo.category.
--FK to film
ALTER TABLE dbo.film_category
ADD CONSTRAINT FK_filmcategory_film
FOREIGN KEY (film_id) REFERENCES dbo.film (film_id); --to add foreign key reference to the main key

--FK to category
ALTER TABLE dbo.film_category
ADD CONSTRAINT FK_filmcategory_category
FOREIGN KEY (category_id) REFERENCES dbo.category (category_id);

--16.Insert data into film_category from dvdrental.dbo.film_category
INSERT INTO dbo.film_category (film_id, category_id)
SELECT film_id, category_id
FROM dvdrental.dbo.film_category;

--verify film_category counts
SELECT COUNT(*) AS film_category_rows FROM dbo.film_category;

--Exercise 5: Saving your work
-- 17. Create a full backup of an existing DVDfilms database
BACKUP DATABASE [DVDfilms]
TO DISK = N'C:\SAXION\Year 2\Quarter 1\Database\Week 5\DVDfilms_full.bak'
WITH FORMAT, INIT, NAME = N'DVDfilms-Full Database Backup';

--Final checks (optional) Show key objects created
SELECT 'Tables' = t.name, s.name AS schema_name
FROM sys.tables t
JOIN sys.schemas s ON t.schema_id = s.schema_id
WHERE t.name IN ('category','film','film_category');

SELECT * FROM dbo.category;
SELECT TOP 10 * FROM dbo.film;
SELECT TOP 10 * FROM dbo.film_category;


--Create a new empty test database
USE master;
CREATE DATABASE [DVDfilms_test];
ALTER DATABASE [DVDfilms_test] SET MULTI_USER WITH ROLLBACK IMMEDIATE;