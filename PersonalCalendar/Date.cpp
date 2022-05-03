#include<stdexcept>
#include<iostream>
#include<cstdio>
#include<cstring>
#include "Date.h"

Date::Date()
{
	this->day = 1;
	this->month = 1;
	this->year = 2022;
}

Date::Date(int day, int month, int year)
{
	if (month <= 0 || month > 12)
		throw std::invalid_argument("Invalid month value!");

	if (year <= 0)
		throw std::invalid_argument("Invalid year value!");

	if (day <= 0 || day > 31)
		throw std::invalid_argument("Invalid day value!");
	else if (day == 31 &&
		(month == 2 || month == 4 || month == 6 || month == 9 || month == 11))
		throw std::invalid_argument("Invalid day value!");
	else if (day == 30 &&
		(month == 1 || month == 2 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
		throw std::invalid_argument("Invalid day value!");
	else if (day == 29 &&
		month == 2 &&
		!((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		throw std::invalid_argument("Invalid day value! (Leap year)");

	this->day = day;
	this->month = month;
	this->year = year;
}

Date& Date::operator=(const Date& other)
{
	if (this != &other) {
		this->day = other.day;
		this->month - other.month;
		this->year = other.year;
	}
	return *this;
}

int Date::GetDay()
{
	return this->day;
}

int Date::GetMonth()
{
	return this->month;
}

int Date::GetYear()
{
	return this->year;
}

void Date::print()
{
	std::cout << year << "-";
	if (month < 10)
		std::cout << "0" << month << "-";
	else
		std::cout << month << "-";
	if (day < 10)
		std::cout << "0" << day << '\n';
	else
		std::cout << day << '\n';
}

char* Date::getString()
{
	char retVal[11]{};
	char monthS[3]{};
	char dayS[3]{};
	if (month < 10) {
		monthS[0] = '0';
		monthS[1] = (char)('0' + month);
	}
	else {
		monthS[0] = '1';
		monthS[1] = (char)('0' + month % 10);
	}
	if (day < 10) {
		dayS[0] = '0';
		dayS[1] = (char)('0' + day);
	}
	else {
		dayS[0] = (char)('0' + day / 10 % 10);
		dayS[1] = (char)('0' + day % 10);
	}

	sprintf_s(retVal, 11, "%u-%s-%s",
		year,
		monthS,
		dayS);

	return retVal;
}
