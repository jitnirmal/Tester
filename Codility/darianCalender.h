#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;


constexpr int monthDays[24] = { 28, 28, 28, 28, 28, 27,
28, 28, 28, 28, 28, 27,
28, 28, 28, 28, 28, 27,
28, 28, 28, 28, 28, 27 };

constexpr int NumOfDaysInYear = 668;

/// <summary>
/// Helper Date class for conversions
/// </summary>
class Date
{
public:
	Date(const std::string& str) {
		_day = std::stoi(str.substr(0, 2));
		_month = std::stoi(str.substr(2, 2));
		_year = std::stoi(str.substr(4, 4));
	}

	/// <summary>
	/// returns number of days since start of calender 
	/// </summary>

	int getNumOfDaysForDate()
	{
		auto numOfDaysForDate = _year * NumOfDaysInYear + _day;

		for (int i = 0; i < _month - 1; ++i)
			numOfDaysForDate += monthDays[i];

		numOfDaysForDate += getLeapYearsCount();
		return numOfDaysForDate;
	}
private:


	int getLeapYearsCount() const noexcept
	{
		auto lYears = 0;
		if (_year > 1)
		{
			lYears = _year / 2 + (_year - 1) / 10;
		}

		return lYears;
	}


private:
	int _day, _month, _year;
};

int calc_days_between(string start, string end) {

	auto numOfDaysForStartDate = Date{ start }.getNumOfDaysForDate();
	auto numOfDaysForEndDate = Date{ end }.getNumOfDaysForDate();

	return (numOfDaysForEndDate - numOfDaysForStartDate);
}


int test()
{
	//Date dt1 = { "01012010" }; 	Date dt2 = { "10012010" };
	//Date dt1 = { "01012010" }; 	Date dt2 = { "01022010" };
	Date dt1 = { "01012011" }; 	Date dt2 = { "01012010" };

	std::cout << "Difference between two dates is " << calc_days_between("01010001", "01010002");

	return 0;
}


int getLeapYearsCount1(int _year)
{
	auto lYears = 0;
	bool decadePassed(false);



	for (int i = 1; i <= _year; ++i)
	{
		if (decadePassed == true)
		{
			++lYears;
			decadePassed = false;
		}

		if (i >= 2 && (i % 2 == 0))
			++lYears;

		if (i >= 10 && (i % 10 == 0))
			decadePassed = true;
	}

	return lYears;
}


int getLeapYearsCount2(int _year)
{
	auto lYears = 0;
	if (_year > 1)
	{
		lYears = _year / 2 + (_year - 1) / 10;
	}

	return lYears;

}