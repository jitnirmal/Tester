/// <summary>
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
/


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