#1 Find all films with maximum length and minimum rental duration (compared to all other films). 
#In other words let L be the maximum film length, and let R be the minimum rental duration in the table film. You need to find all films with length L and rental duration R.
#You just need to return attribute film id for this query.

SELECT film_id AS 'film id'
FROM film 
WHERE length = (
	SELECT MAX(length) 
	FROM film) 
AND rental_duration = (
	SELECT MIN(rental_duration) 
	FROM film);


#2 We want to find out how many actors have played in each film, so for each film return the film id, film title, and the number of actors who played in that film. Some films may have no actors, and your query does not need to return those films.

SELECT f.film_id AS 'film id', f.title AS 'film title', COUNT(fa.actor_id) AS 'number of actors' 
FROM film f
INNER JOIN film_actor fa ON fa.film_id = f.film_id
GROUP BY f.film_id;


#3 Find the average length of films for each language. Your query should return every language even if there is no films in that language. language refers to attribute language_id (not attribute original_language_id)

SELECT l.name AS 'film language', AVG(f.length) AS 'average length'
FROM language l
LEFT JOIN film f ON f.language_id = l.language_id
GROUP BY l.name;


#4 We want to find out how many of each category of film KEVIN BLOOM has started in so return a table with category.name and the count
#of the number of films that KEVIN was in which were in that category order by the category name ascending (Your query should return every category even if KEVIN has been in no films in that category).

SELECT name AS 'category', COUNT(actor_id) AS "starring Kevin Bloom" 
FROM (
	SELECT f.film_id, c.name 
	FROM film f 
	INNER JOIN film_category fc ON fc.film_id = f.film_id
	INNER JOIN category c ON c.category_id = fc.category_id
) AS k1 
LEFT JOIN (
	SELECT f.film_id, a.actor_id 
	FROM film f
	INNER JOIN film_actor fa ON fa.film_id = f.film_id
	INNER JOIN actor a ON a.actor_id = fa.actor_id
	WHERE first_name = "KEVIN" AND last_name = "BLOOM"
) AS k2 ON k1.film_id = k2.film_id
GROUP BY category;


#5 Find the film title of all films which do not feature both SCARLETT DAMON and BEN HARRIS(so you will not list a film if both of these actors have played in that film, but if only one or none of these actors have played in a film, that film should be listed).
#Order the results by title, descending (use ORDER BY title DESC at the end of the query)
#Warning, this is a tricky one and while the syntax is all things you know, you have to think oustide
#the box a bit to figure out how to get a table that shows pairs of actors in movies

SELECT f.title AS 'films not featuring both Scarlett Damon and Ben Harris' 
FROM actor a
INNER JOIN film_actor fa ON a.actor_id = fa.actor_id
INNER JOIN film f ON fa.film_id = f.film_id
WHERE f.title 
NOT IN (
	SELECT BH.title 
	FROM (
		SELECT f.title 
    	FROM actor a 
		INNER JOIN film_actor fa ON a.actor_id = fa.actor_id
   		INNER JOIN film f ON fa.film_id = f.film_id
    	WHERE a.first_name = 'BEN' AND a.last_name = 'HARRIS'
	) AS BH
	INNER JOIN (
		SELECT f.title
    	FROM actor a
		INNER JOIN film_actor fa ON a.actor_id = fa.actor_id
    	INNER JOIN film f ON fa.film_id = f.film_id
    	WHERE a.first_name = 'SCARLETT' AND a.last_name = 'DAMON'
    ) AS SD 
    ON BH.title = SD.title
)
GROUP BY f.title	
ORDER BY f.title DESC;