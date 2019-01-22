/// <summary>
/// 1. Boost intrusive pointers
/// 2. F&& foo1 = somefoo;
///	   auto&& foo2 = foo1;
/// 3. thread_local
///		thread registers
/// 4. static initialization
/// 5. thread switch	
/// 6. pragram
/// 7. compilation
/// 8. funciton redifination error
/// 9. compilier version
/// if(x>0) how to tell compiler branch predicton
/// 
/// std::atomic
/// a=1, b=1
/// th 1 // a=2, b=3
/// th 2 // b=3, a=1
/// 
/// </summary>



/// KDB : kdb+ is a column-based relational time series database, with in-memory (IMDB) abilities developed by Kx Systems
/// used to store, process, and analyze large data sets at high speed
/// handle billions of records and analyzes data within a database
/// responds to queries similar to Structured Query Language
/// Q is the query language for kdb+, a disk based and in-memory, column-based database. 
/// kdb+ is based on the language K. Q is a thin wrapper around K, providing a more readable, English-like interface.
/// Q can manipulate streaming, real-time, and historical data
///  kdb+ includes interfaces in C, C++, Java, C#, and Python
/// 
/// 
/// 
/// 
/// 
/// /// <summary>
/// Given the CITY and COUNTRY tables, query the names of all the continents (COUNTRY.Continent) and their respective average city populations (CITY.Population) rounded down to the nearest integer.
/// Note: CITY.CountryCode and COUNTRY.Code are matching key columns.
/// 
/// select country.continent, floor(avg(city.population)) 
/// from country, city 
/// where country.code = city.countrycode 
/// group by country.continent;
/// 
/// or by inner join
/// select country.continent,floor(avg(city.population))
/// from country inner join city
/// on country.Code = city.countrycode
/// group by country.continent;
/// /// </summary>

/// <summary>
/// https://www.hackerrank.com/challenges/write-a-function/problem
/// Students : Id, Name, Marks
/// Grades : Grade, Min_Mark, Max_Mark
/// Ketty gives Eve a task to generate a report containing three columns :
///		Name, Grade and Mark.
/// Ketty doesn't want the NAMES of those students who received a grade lower than 8. 
///		--The report must be in descending order by grade -- i.e.higher grades are entered first.
///		--If there is more than one student with the same grade(8 - 10) assigned to them, order those particular students by their name alphabetically.
/// 
/// Finally, if the grade is lower than 8, use "NULL" as their name and list them by their grades in descending order.
///		--If there is more than one student with the same grade(1 - 7) assigned to them, order those particular students by their marks in ascending order.
/// 
/// select case
///		when grade < 8 then NULL
/// else
///		name
/// end
/// as name, grade, marks
/// from students, grades
/// where marks between min_mark and max_mark
/// order by grade desc, name asc, marks asc;
/// </summary>
/// 
/// 
/// select second largest salary from employee table



/// <summary>
/// Normalization : two purposes
///		-- Eliminating reduntant(useless) data.
///		--  Ensuring data dependencies make sense i.e data is logically stored.
/// </summary>
