/*1. Show all the data in the staff table.
	SELECT *
	  FROM staff;
*/


/*2. Show the id, title and description of all movies.
	SELECT film_id, title, description
	FROM film;
*/


/*3. Show the id and name of all the categories.
	SELECT category_id, name
	FROM category;
*/


/*4. Extend the previous query by sorting the query on name.
	SELECT category_id, name
	FROM category
	ORDER BY name;
*/

/*5.Show all the customers sorted by lastname. Show firstname, lastname, city and email
of eachcustomer.
	SELECT first_name, last_name, city, email
	FROM customer
	ORDER BY last_name;
*/


/*6. Show all the customers sorted by lastname descending and sorted by firstname ascending.
	SELECT first_name, last_name, email
	FROM customer
	ORDER BY last_name DESC, first_name ASC;
*/


/*7. Show the top 20 most recent movies (based on release year). Show the release year,
film id,title, and description.
	SELECT release_year, film_id, title, description
	FROM film
	ORDER BY release_year DESC
	OFFSET 0 ROWS FETCH NEXT 20 ROWS ONLY;
*/


/*8. Show all unique cities of customers, sorted by country name descending. Show both
the cityname and the country name.
	SELECT DISTINCT city, country
	FROM customer
	ORDER BY country DESC;
*/


/*9.Show all unique customers that have rented some films. Sort by customer id descending.
	SELECT DISTINCT c.customer_id, c.first_name, c.last_name
	FROM customer c
	JOIN rental r ON c.customer_id = r.customer_id
	ORDER BY c.customer_id DESC;
*/


/*10.Select all actors that have lastname “Cage”
	SELECT *
	FROM actor
	WHERE last_name = 'Cage';
*/


/*11. Select all the customers that have firstname “Kelly” or firstname “Edith”. Order the
result by lastname.
	SELECT first_name, last_name
	FROM customer 
	WHERE first_name IN ('Kelly', 'Edith')
	ORDER BY last_name;
*/


/*12. Show all movies that possibly are documentaries. Such movies have a description that
contains the word ‘Documentary’. Show film_id, title and description and sort by title.
	SELECT film_id, title, description
	FROM film
	WHERE description LIKE '%Documentary%'
	ORDER BY film_id;
*/


/*13. Show all customers with which the firstname starts with an “A” and where the name
has aminimum of 4 characters.
	SELECT *
	FROM customer
	WHERE first_name LIKE 'A%'
		AND LEN(first_name) >= 4; 
*/


/*14. Show all rentals that aren’t returned yet. Show customer id, rental date, and inventory id.
Sort by customer id.
	SELECT customer_id, rental_date, inventory_id
	FROM rental
	WHERE return_date IS NULL
	ORDER BY customer_id;
*/


/*15. Create a query that shows all films that are rated as “PG-13” and released after “2000”. Sort
by rental duration descending and show title, rental duration, release year, and rating.
	SELECT title, rental_duration, release_year, rating 
	FROM film
	WHERE rating = 'PG-13'
		AND release_year > 2000
	ORDER BY rental_duration DESC
*/


/*16. Show the total number of customers. Use total_customers as column name. 
	SELECT COUNT(*) AS total_customer
	FROM customer;
*/


/*17. Show the total turnover of customer with id 148. Use turnover as column name.
	SELECT SUM(amount) AS turnover
	FROM payment
	WHERE customer_id = 148;
*/


/*18. Show the average duration of all films. Use average_duration as column name. Use
round(X) in order to round to whole minutes.
SELECT ROUND(AVG(length), 0) AS average_duration
FROM film;
*/


/*19. Show the longest duration of all films. Use duration as column name.
Can you use the title in your select statement? Why (not)?
	SELECT MAX(length) AS duration
	FROM film;
	-- No, because when using aggregate functions like MAX(), you must either group by other columns (e.g., title) 
	-- or only use aggregate columns.
	-- Otherwise SQL doesn’t know which title belongs to the longest film unless explicitly grouped.
*/


/*20. Show the number of films per year of release. Show the year of release and the number of
films. Use number_of_films as column name.
	SELECT release_year, COUNT(*) AS number_of_films
	FROM film
	GROUP BY release_year;
*/


/*21. Show the total value of payments per customer. Show the customer_id and the
corresponding total value of payments. Use turnover as column name. Sort by the total
value of payments.
	SELECT customer_id, SUM(amount) AS turnover
	FROM payment
	GROUP BY customer_id
	ORDER BY turnover;
*/


/*22. Show the number of films per category where the category id is less than 10. Sort the result
by the number of films.
	SELECT fc.category_id, COUNT(*) AS number_of_films
	FROM film_category fc
	WHERE fc.category_id < 10
	GROUP BY fc.category_id
	ORDER BY number_of_films;
*/


/*23. Show all rental transactions after ’1 January 2006’
SELECT *
FROM rental
WHERE rental_date > '2006-01-01';
*/


/*24. Show the rental_id and duration of the rental-period, of the movies rented out between ’5
July 2005 22:00’ and ‘5 July 2005 23:00’. Use ‘duration’ as column name, order by duration
(descending).
	SELECT rental_id, (return_date - rental_date) AS duration
	FROM rental
	WHERE rental_date BETWEEN '2005-07-05 22:00:00' AND '2005-07-05 23:00:00'
	ORDER BY duration DESC
*/


/*25. Show how much money was earned in total per hour of the day. Use period and turnover
as column names, order by turnover (descending).
At what time are most films rented?
	SELECT DATEPART(HOUR, payment_date) AS period, SUM(amount) AS turnover
	FROM payment
	GROUP BY DATEPART(HOUR, payment_date)
	ORDER BY turnover DESC;
	-- 13:00 is when most films are rented
*/


/*26. Show the total value of payments per date. Use period and turnover as column names,
order by period (ascending):
This is a good dataset for historic graph showing the turnover per day. But what do you
have to change to retrieve only the best-selling day ? And what is that result?
	SELECT CAST(payment_date AS DATE) AS period,
		SUM(amount) AS turnover
	FROM payment
	GROUP BY CAST(payment_date AS DATE)
	ORDER BY period ASC;
-- To retrieve only the best selling day, add TOP 1 and order by turnover decending
	SELECT TOP 1 CAST(payment_date AS DATE) AS period,
		SUM(amount) AS turnover
	FROM payment
	GROUP BY CAST(payment_date AS DATE)
	ORDER BY turnover DESC;
*/


/*27. Show the total value of payments per month of the year 2007. Use period and turnover as
column names, order by turnover (descending):
What is the best-selling month? Use an SQL comment to add this answer to your SQL file.
	SELECT DATEPART(MONTH, payment_date) AS period, 
		SUM(amount) AS turnover
	FROM payment
	WHERE YEAR(payment_date) = 2007
	GROUP BY DATEPART(MONTH, payment_date)
	ORDER BY turnover DESC;
	-- Best-selling month = April
*/


/*28. Show the average rental duration (the difference between the rental date and the
return_date).
	SELECT AVG(DATEDIFF(DAY, rental_date, return_date)) AS avg_rental_duration
	FROM rental;
*/


/*29. Show per customer_id how many movies he/she rented per month/year. Order the result
by year, month ascending, and then descending by number of rentals.
	SELECT customer_id,
		YEAR(rental_date) AS year,
		MONTH(rental_date) AS month,
		COUNT(*) AS num_of_rentals
	FROM rental
	GROUP BY customer_id, YEAR(rental_date), MONTH(rental_date)
	ORDER BY year, month ASC, num_of_rentals DESC;
*/








