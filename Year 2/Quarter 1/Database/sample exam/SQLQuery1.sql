--1.1
SELECT DISTINCT CAST(description AS NVARCHAR(MAX)) AS description
FROM film
WHERE description LIKE '%amazing%'
AND (description LIKE '%car%' OR description LIKE '%robot%');
--1.2
SELECT country AS country_name, COUNT(customer_id) AS num_of_customer
FROM customer
GROUP BY country
HAVING COUNT(customer_id) >= 10
ORDER BY num_of_customer DESC;
--1.3
SELECT title 
FROM film
WHERE LEN(title) = (SELECT MIN(LEN(title)) FROM film)
ORDER BY title;
--1.4
SELECT TOP(10) c.first_name, c.last_name, COUNT(r.rental_id) AS quantity
FROM customer c
INNER JOIN rental r ON r.customer_id = c.customer_id
GROUP BY c.first_name, c.last_name
ORDER BY COUNT(r.rental_id) DESC;
--1.5
SELECT first_name, last_name
FROM actor 
WHERE actor_id NOT IN(
	SELECT fa.actor_id
	FROM film_actor fa
	INNER JOIN film f ON f.film_id = fa.film_id
	WHERE f.release_year < 1973
);
--1.6
SELECT f.title, COUNT(fa.actor_id) AS num_actor
FROM film f
INNER JOIN film_actor fa ON fa.film_id = f.film_id
GROUP BY f.film_id, f.title
HAVING COUNT(fa.actor_id) < (
	SELECT COUNT(*)
	FROM film_actor fa2
	INNER JOIN film f2 ON fa2.film_id = f2.film_id
	WHERE f2.title = 'Shootist Superfly'
);

--1.7
SELECT a.first_name, a.last_name, f.title
FROM actor a
INNER JOIN film_actor fa ON fa.actor_id = a.actor_id
INNER JOIN film f ON f.film_id = fa.film_id
WHERE fa.film_id IN (
	SELECT fa2.film_id
	FROM actor a2
	INNER JOIN film_actor fa2 ON fa2.actor_id = a2.actor_id
	WHERE a2.first_name = 'Rita' AND a2.last_name = 'Reynolds'
)	
AND NOT (a.first_name = 'Rita' AND a.last_name = 'Reynolds')
ORDER BY a.last_name, a.first_name, f.title;


--2.1
--check num of actor
SELECT COUNT(*) FROM actor;
--add name
INSERT INTO actor(actor_id, first_name, last_name)
VALUES(202, 'John', 'Rodrigo');

--2.2
IF DB_ID('GradeSystem') IS NOT NULL
	DROP DATABASE GradeSystem;

CREATE DATABASE GradeSystem
GO

USE [GradeSystem]
GO

IF OBJECT_ID('Student', 'U') IS NOT NULL DROP TABLE dbo.Student
IF OBJECT_ID('Grade', 'U') IS NOT NULL DROP TABLE dbo.Grade
IF OBJECT_ID('Course', 'U') IS NOT NULL DROP TABLE dbo.Course
IF OBJECT_ID('Teacher', 'U') IS NOT NULL DROP TABLE dbo.Teacher
Go

CREATE TABLE dbo.Student(
	student_number INT NOT NULL PRIMARY KEY,
	first_name VARCHAR(100) NOT NULL,
	last_name VARCHAR(100) NOT NULL
);

CREATE TABLE dbo.Teacher(
	teacher_code VARCHAR(10) NOT NULL PRIMARY KEY,
	first_name VARCHAR(100) NOT NULL,
	last_name VARCHAR(100) NOT NULL
);

CREATE TABLE dbo.Course(
	course_id VARCHAR(10) NOT NULL PRIMARY KEY,
	course_name VARCHAR(100) NOT NULL,
	teacher_code VARCHAR(10) NULL,
	CONSTRAINT FK_Course_Teacher FOREIGN KEY (teacher_code)
		REFERENCES dbo.Teacher(teacher_code)
);

CREATE TABLE dbo.Grade(
	student_number INT NOT NULL,
	course_id VARCHAR(10) NOT NULL,
	grade_name VARCHAR(10) NOT NULL,
	percentage INT NULL,
	date DATE NULL,
	grade INT NULL,
	CONSTRAINT PK_GRADE PRIMARY KEY (student_number, course_id, grade_name),
	CONSTRAINT FK_GRADE_STUDENT FOREIGN KEY (student_number) REFERENCES dbo.Student(student_number),
	CONSTRAINT FK_GRADE_COURSE FOREIGN KEY (course_id) REFERENCES dbo.Course(course_id)
);
