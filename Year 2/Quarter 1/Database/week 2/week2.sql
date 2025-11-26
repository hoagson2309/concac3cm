--Lab Assignment: Week 2
--Name: Son Cao
--Student number: 570135

--14. Show all customers that have more than one unreturned movie. 
--Display per customer the first name, last name, and the amount of unreturned movies. Order the result by first name, last name.

--JOINS
SELECT c.first_name, c.last_name, COUNT(r.rental_id) AS unreturned_count
FROM customer c
INNER JOIN rental r ON c.customer_id = r.customer_id
WHERE r.return_date IS NULL
GROUP BY c.customer_id, c.first_name, c.last_name
HAVING COUNT(r.rental_id) > 1
ORDER BY c.first_name, c.last_name;

--SUBQUERY
SELECT c.first_name, c.last_name, uc.unreturned_count
FROM customer c
INNER JOIN (
	SELECT customer_id, COUNT(rental_id) AS unreturned_count
	FROM rental
	WHERE return_date IS NULL
	GROUP BY customer_id
	HAVING COUNT(rental_id) > 1
	) AS uc ON c.customer_id = uc.customer_id
ORDER BY c.first_name, c.last_name; 


--15. Given the 10 most rented movies, show the movies of which there are less than 9 pieces available in the inventory.

--JOINS
WITH Toprented AS (
	SELECT TOP 10 f.film_id, f.title, COUNT(r.rental_id) AS rental_count
	FROM film f
	INNER JOIN inventory i ON f.film_id = i.film_id
	INNER JOIN rental r ON i.inventory_id = r.inventory_id
	GROUP BY f.film_id, f.title
	ORDER BY rental_count DESC
) 
SELECT tr.title, COUNT(i.inventory_id) AS available_copies
FROM Toprented tr
INNER JOIN inventory i ON tr.film_id = i.film_id
WHERE i.inventory_id NOT IN ( 
	SELECT inventory_id		
	FROM rental 
	WHERE return_date IS NULL
)
GROUP BY tr.title
HAVING COUNT(i.inventory_id) < 9; 

--SUBQUERY
SELECT tr.title, COUNT(i.inventory_id) AS available_copies
FROM (
	SELECT TOP 10 f.film_id, f.title
	FROM film f
	INNER JOIN inventory i ON f.film_id = i.film_id
	INNER JOIN rental r ON i.inventory_id = r.inventory_id
	GROUP BY f.film_id, f.title
	ORDER BY COUNT(r.rental_id) DESC
) AS tr
INNER JOIN inventory i ON tr.film_id = i.film_id
WHERE i.inventory_id NOT IN (
	SELECT inventory_id 
	FROM rental
	WHERE return_date IS NULL
)
GROUP BY tr.title
HAVING COUNT(i.inventory_id) < 9; 





--1. Show the first name and last name of the staff together with the address of the store where they work.
SELECT s.first_name, s.last_name, st.address
FROM staff s
INNER JOIN store st ON s.store_id = st.store_id; 


 --2. Give the first name and the last name of the staff that ever rented a movie to customer id 526. Eliminate duplicate results. => unique => DISTINCT
SELECT DISTINCT s.first_name, s.last_name, r.customer_id
FROM staff s
INNER JOIN rental r ON s.staff_id = r.staff_id
WHERE r.customer_id = 526; 


 --3. Show the first name and last name of the customers in combination with the first name and last name of the staff who helped customers. 
SELECT c.first_name AS customer_first, c.last_name AS customer_last,
	   s.first_name AS staff_first, s.last_name AS staff_last
FROM rental r
INNER JOIN customer c ON r.customer_id = c.customer_id
INNER JOIN staff s ON r.staff_id = s.staff_id;	


 --4. Show all film titles and their category names. Order by category name and film name.
SELECT f.title, c.name AS category_name
FROM film f
INNER JOIN film_category fc ON f.film_id = fc.film_id
INNER JOIN category c ON c.category_id = fc.category_id
ORDER BY c.name, f.title; 


 --5. Show the first name and the last name of customers, and the movie titles of movies they have rented in the past.
--Sort the result by last name, first name, and movie title.
SELECT c.first_name, c.last_name, f.title
FROM rental r
INNER JOIN customer c ON c.customer_id = r.customer_id
INNER JOIN inventory i ON i.inventory_id = r.inventory_id
INNER JOIN film f ON f.film_id = i.film_id
ORDER BY c.last_name, c.first_name, f.title; 


 --6. Show the first name and last name of customers and the total amount of money they spent on renting movies. Order by this amount descending.
SELECT c.first_name, c.last_name, SUM(p.amount) AS total_spent
FROM payment p
INNER JOIN rental r ON r.rental_id = p.rental_id
INNER JOIN customer c ON c.customer_id = r.customer_id
GROUP BY c.customer_id, c.first_name, c.last_name
ORDER BY total_spent DESC; 

 --7. Show which film titles are available per store. Show the film name, the address of the store ,
--and the number of copies that the store has of the film. Order by film title ascending.
SELECT f.title, st.address, COUNT(i.inventory_id) AS copies
FROM inventory i
INNER JOIN film f ON f.film_id = i.film_id
INNER JOIN store st ON st.store_id = i.store_id
GROUP BY f.title, st.address, i.inventory_id
ORDER BY f.title ASC; 


 --8. Show per movie title the number of actors in the movie. Order the result by the number of actors descending.
SELECT f.title, COUNT(fa.actor_id) AS num_of_actor
FROM film f
INNER JOIN film_actor fa ON f.film_id = fa.film_id
GROUP BY f.film_id, f.title
ORDER BY num_of_actor DESC; 


 --9. Give the top 10 of the most rented movies.
SELECT TOP 10 f.title, COUNT(r.rental_id) AS rental_count
FROM rental r
INNER JOIN inventory i ON r.inventory_id = i.inventory_id
INNER JOIN film f ON f.film_id = i.film_id
GROUP BY f.film_id, f.title
ORDER BY rental_count DESC; 


 -- 10. Select all movies that have never been rented.
-- JOINS
SELECT f.title
FROM film f
LEFT JOIN inventory i ON f.film_id = i.film_id
LEFT JOIN rental r ON i.inventory_id = r.inventory_id
WHERE r.rental_id IS NULL;

-- SUBQUERY
SELECT title 
FROM film
WHERE film_id NOT IN (
	SELECT i.film_id
	FROM inventory i
	INNER JOIN rental r ON i.inventory_id = r.inventory_id 
); 

--11. Select all titles of movies of which there are exactly 8 copies available in the inventory
-- JOINS
SELECT f.title 
FROM film f
INNER JOIN inventory i ON f.film_id = i.film_id
GROUP BY f.film_id, f.title
HAVING COUNT(i.inventory_id) = 8;

--SUBQUERY
SELECT title
FROM film
WHERE film_id IN (
	SELECT film_id
	FROM inventory
	GROUP BY film_id
	HAVING COUNT(inventory_id) = 8
);


--12. Show all customers who have spent over 100 dollars on movies. 
--JOINS
SELECT c.first_name, c.last_name, SUM(p.amount) AS total_spent 
FROM customer c
INNER JOIN rental r ON c.customer_id = r.customer_id
INNER JOIN payment p ON r.rental_id = p.rental_id
GROUP BY c.customer_id, c.first_name, c.last_name
HAVING SUM(p.amount) > 100;

--SUBQUERY
SELECT *
FROM customer 
WHERE customer_id IN(
	SELECT r.customer_id
	FROM rental r
	INNER JOIN payment p ON r.rental_id = p.rental_id
	GROUP BY r.customer_id
	HAVING SUM(p.amount) > 100
);



 --13. Show all customers who have rented a movie in the horror category.
--JOINS
SELECT DISTINCT c.first_name, c.last_name
FROM customer c
INNER JOIN rental r ON c.customer_id = r.customer_id
INNER JOIN inventory i ON r.inventory_id = i.inventory_id
INNER JOIN film f ON i.film_id = f.film_id
INNER JOIN film_category fc ON f.film_id = fc.film_id
INNER JOIN category ct ON fc.category_id = ct.category_id
WHERE ct.name = 'Horror';

--SUBQUERY
SELECT DISTINCT first_name, last_name
FROM customer
WHERE customer_id IN (
	SELECT r.customer_id
	FROM rental r
	INNER JOIN inventory i ON r.inventory_id = i.inventory_id
	INNER JOIN film_category fc ON i.film_id = fc.film_id
	INNER JOIN category ct ON fc.category_id = ct.category_id
	WHERE ct.name = 'Horror'
); 


 -- 16. Show the amount of money that has been earned per store
SELECT st.store_id, SUM(p.amount) AS total_earned
FROM store st
INNER JOIN staff s ON st.store_id = s.store_id
INNER JOIN rental r ON s.staff_id = r.staff_id
INNER JOIN payment p ON r.rental_id = p.rental_id
GROUP BY st.store_id; 

--subquery
SELECT st.store_id, sub.total_per_staff
FROM store st
INNER JOIN ( 
	SELECT s.store_id, SUM(p.amount) AS total_per_staff
	FROM staff s
	INNER JOIN rental r ON r.staff_id = s.staff_id
	INNER JOIN payment p ON p.rental_id = r.rental_id
	GROUP BY s.store_id
) AS sub 
ON sub.store_id = st.store_id;



 --17. Give the number of customers per store. Show the address of the store and the number of customers per store.
SELECT st.store_id, st.address, COUNT(DISTINCT c.customer_id) AS num_customers
FROM store st
INNER JOIN customer c ON st.store_id = c.store_id
GROUP BY st.store_id, st.address; 


 --18. Show all the first name and last name of the tables customer, actor, and staff and order by last name and first name.
SELECT first_name, last_name
FROM customer
UNION
SELECT first_name, last_name
FROM actor
UNION
SELECT first_name, last_name
FROM staff
ORDER BY first_name, last_name; 


 --19. Show all the firstnames that occur in both the customer and actor table. Order alphabetically.
SELECT first_name, last_name
FROM customer
INTERSECT
SELECT first_name, last_name
FROM actor
ORDER BY first_name ASC; 


 --20. Show all the firstname of all the actors, which firstname does not occur in the customer table. Order alphabetically
SELECT first_name, last_name
FROM actor
EXCEPT
SELECT first_name, last_name
FROM customer
ORDER BY first_name ASC; 


 -- 21. Add yourself as a customer to the database
INSERT INTO customer (customer_id, store_id, first_name, last_name, email, address, activebool)
VALUES (9999, '1', 'Son', 'Cao', 'soncaoabc@gmail.com', 'ABC straat', 1); 


 --22. Rent the movies 'Trip Newton' and 'Hardly Robbers' with your newly created account. Make sure that the return date is not set!
--SEARCH FOR HIGHEST EXISTING rental_id
SELECT MAX(rental_id) AS last_id FROM rental;

INSERT INTO rental (rental_id, rental_date, inventory_id, customer_id, staff_id)
VALUES (16051, GETDATE(), (SELECT TOP 1 i.inventory_id FROM inventory i JOIN film f ON i.film_id = f.film_id WHERE f.title = 'Trip Newton'), 9999, 1);

INSERT INTO rental (rental_id, rental_date, inventory_id, customer_id, staff_id)
VALUES (16052, GETDATE(), (SELECT TOP 1 i.inventory_id FROM inventory i JOIN film f ON i.film_id = f.film_id WHERE f.title = 'Hardly Robbers'), 9999, 1); 


 --23. Add a new movie to the database with the title 'Going Dutch' and come up with the other attributes
INSERT INTO film (film_id, title, description, release_year, rental_duration, rental_rate, length, replacement_cost, rating, fulltext)
VALUES (1001, 'Going Dutch', 'A new comedy movie', 2024, 5, 2.99, 100, 20.00, 'PG', 'nice'); 

 --24. Add the newly created movie to the categories 'Horror' and 'Comedy'.
INSERT INTO film_category (film_id, category_id)
VALUES ((SELECT film_id
		FROM film 
		WHERE title = 'Going Dutch'),
		(SELECT category_id
		FROM category
		WHERE name = 'Horror'));

INSERT INTO film_category (film_id, category_id)
VALUES ((SELECT film_id
		FROM film 
		WHERE title = 'Going Dutch'),
		(SELECT category_id
		FROM category
		WHERE name = 'Comedy')); 


 --25. Customer Bernard Colby has moved recently. His new address is 105 Petronas Street, 
--zipcode: 5326, city Kuala Lumpur, country: Malaysia.
UPDATE customer
SET address = '105 Petronas Street, 5326 Kuala Lumpur, Malaysia'
WHERE first_name = 'Benard' AND last_name = 'Colby'; 


 --26. You just handed in the movies 'Trip Newton' and 'Hardly Robbers' with your own account. Update the database and set the return date.
UPDATE rental 
SET return_date = GETDATE()
WHERE customer_id = 9999
	AND inventory_id IN (
		SELECT i.inventory_id
		FROM inventory i
		JOIN film f ON f.film_id = i.film_id
		WHERE f.title IN ('Trip Newton', 'Hardly Robbers')
	); 



 --27. The movie 'Factory Dragon' has a wrong release year. Update it to 2002.
UPDATE film 
SET release_year = 2002
WHERE title = 'Factory Dragon'; 


 --28. Update all the movies with release years between 1980 and 1985 and set the rental duration to 10 days
UPDATE film
SET rental_duration = 10
WHERE release_year BETWEEN 1980 AND 1985; 


 --29. Remove yourself from the database. Make sure that your rental history is removed first.
DELETE FROM rental
WHERE customer_id = 9999

DELETE FROM payment
WHERE customer_id = 9999

DELETE FROM customer
WHERE customer_id = 9999; 


 --30. Remove the movie 'Going Dutch'. Make sure that you remove all the references to the movie first.
DELETE FROM film_category
WHERE film_id = (SELECT film_id FROM film WHERE title = 'Going Dutch')

DELETE FROM inventory 
WHERE film_id = (SELECT film_id FROM film WHERE title = 'Going Dutch')

DELETE FROM film_actor 
WHERE film_id = (SELECT film_id FROM film WHERE title = 'Going Dutch')

DELETE FROM film
WHERE title = 'Going Dutch'; 








































