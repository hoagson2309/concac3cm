--Student: Son Cao
--Student number: 570135
-- Exam: Databases 2025-2026 - Solutions file (queries labeled by question)

--1.1.Give the descriptions of those movies containing the string “amazing” and either “car” or “robot” or both.Take care that each description is mentioned only once.
SELECT DISTINCT CAST(description AS NVARCHAR(MAX)) AS description --the type of description is text so cannot use distinct directly so 
FROM film
WHERE description LIKE '%amazing%'
  AND (description LIKE '%car%' OR description LIKE '%robot%');

--1.2. Give the names of the countries that have at least 10 customers and order them by the amount of customers in that country in descending order. Also give that amount per country.
SELECT country AS country_name, COUNT(*) AS customer_count
FROM customer 
GROUP BY country
HAVING COUNT(customer_id) >= 10
ORDER BY customer_count DESC;

--1.3
SELECT title 
FROM film
WHERE LEN(title) = (SELECT MIN(LEN(title)) FROM film)
ORDER BY title;

--1.4
SELECT TOP(10) c.first_name, c.last_name, COUNT(r.rental_id) AS quantity
FROM rental r
INNER JOIN customer c ON r.customer_id = c.customer_id
GROUP BY c.first_name, c.last_name
ORDER BY COUNT(r.rental_id) DESC;

--1.5
SELECT first_name, last_name
FROM actor
WHERE actor_id NOT IN (
    SELECT fa.actor_id
    FROM film_actor fa
    JOIN film f ON fa.film_id = f.film_id
    WHERE f.release_year < 1973
);

--1.6
SELECT f.title, COUNT(fa.actor_id) AS number_of_actor
FROM film f
INNER JOIN film_actor fa ON f.film_id = fa.film_id
GROUP BY f.film_id, f.title
HAVING COUNT(fa.actor_id) < (  --fewer
    SELECT COUNT(*)
    FROM film_actor fa2
    INNER JOIN film f2 ON fa2.film_id = f2.film_id
    WHERE f2.title = 'Shootist Superfly'
);
	
--1.7
SELECT DISTINCT a.first_name, a.last_name, f.title
FROM actor a
INNER JOIN film_actor fa ON a.actor_id = fa.actor_id
INNER JOIN film f ON fa.film_id = f.film_id
WHERE fa.film_id IN (
    SELECT fa2.film_id
    FROM actor a2
    INNER JOIN film_actor fa2 ON a2.actor_id = fa2.actor_id
    WHERE a2.first_name = 'Rita' AND a2.last_name = 'Reynolds'
)
AND NOT (a.first_name = 'Rita' AND a.last_name = 'Reynolds') --this removes Rita from the list-leaving only her coworker
ORDER BY a.last_name, a.first_name, f.title;

--2.1 Write a command to add the actor "John Rodrigo" to the actor table.
INSERT INTO actor (actor_id, first_name, last_name)
VALUES ('201', 'John', 'Rodrigo');
--to check
SELECT * FROM actor WHERE first_name = 'John' AND last_name = 'Rodrigo';

--2.2 
--drop database if existed
IF DB_ID('GradeSystem') IS NOT NULL
    DROP DATABASE GradeSystem;
GO

--create database
CREATE DATABASE GradeSystem;
GO

USE GradeSystem;
GO

--DROP TABLE if IS NOT NULL (EXISTED)
IF OBJECT_ID('dbo.Grade', 'U') IS NOT NULL DROP TABLE dbo.Grade;
IF OBJECT_ID('dbo.Teacher', 'U') IS NOT NULL DROP TABLE dbo.Teacher;
IF OBJECT_ID('dbo.Course', 'U') IS NOT NULL DROP TABLE dbo.Course;
IF OBJECT_ID('dbo.Student', 'U') IS NOT NULL DROP TABLE dbo.Student;
GO

--student table
CREATE TABLE dbo.Student (
    student_number INT NOT NULL PRIMARY KEY,
    first_name VARCHAR(100) NOT NULL,
    last_name VARCHAR(100) NOT NULL
);

--teacher table
CREATE TABLE dbo.Teacher (
   teacher_code VARCHAR(10) NOT NULL PRIMARY KEY,
   first_name VARCHAR(100) NOT NULL,
   last_name VARCHAR(100) NOT NULL
);

--course table (course_id PK; teacher_code FK)
CREATE TABLE dbo.Course (
    course_id VARCHAR(10) NOT NULL PRIMARY KEY,
    course_name VARCHAR(100) NOT NULL,
    teacher_code VARCHAR(10) NULL,
    CONSTRAINT FK_Course_Teacher FOREIGN KEY (teacher_code)
        REFERENCES dbo.Teacher (teacher_code)
);

--Grade table
CREATE TABLE dbo.Grade (
    student_number INT NOT NULL,
    course_id VARCHAR(10) NOT NULL,
    grade_name VARCHAR(10) NOT NULL,
    percentage INT NULL,
    date DATE NULL,
    grade INT NULL,
    CONSTRAINT PK_Grade PRIMARY KEY (student_number, course_id, grade_name),
    CONSTRAINT FK_Grade_Student FOREIGN KEY (student_number) REFERENCES dbo.Student(student_number),
    CONSTRAINT FK_Grade_Course FOREIGN KEY (course_id) REFERENCES dbo.Course(course_id)
);