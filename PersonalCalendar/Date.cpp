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
	if (IsValid(day, month, year)) {
		this->day = day;
		this->month = month;
		this->year = year;
	}
}

Date& Date::operator=(const Date& other)
{
	if (this != &other) {
		this->day = other.day;
		this->month = other.month;
		this->year = other.year;
	}
	return *this;
}

bool Date::operator==(const Date& other)
{
	return this->day == other.day && this->month == other.month && this->year;
}

bool Date::operator>=(const Date& other)
{
	if (year < other.year)
		return false;
	if (month < other.month)
		return false;
	if (day < other.day)
		return false;

	return true;
}

bool Date::operator<=(const Date& other)
{
	if (year > other.year)
		return false;
	if (month > other.month)
		return false;
	if (day > other.day)
		return false;

	return true;
}

bool Date::operator<(const Date& other)
{
	if (day >= other.day)
		return false;
	if (month >= other.month)
		return false;
	if (year >= other.year)
		return false;

	return true;
}

bool Date::operator>(const Date& other)
{
	if (year <= other.year)
		return false;
	if (month <= other.month)
		return false;
	if (day <= other.day)
		return false;

	return true;
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

char* Date::getString() const
{
	char* retVal = new char[11]{};
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

bool Date::IsValid(int day, int month, int year)
{
	if (month <= 0 || month > 12) {
		std::cout << "\nInvalid month value!";
		return false;
	}
	if (year <= 0) {
		std::cout << "\nInvalid year value!";
		return false;
	}
	if (day <= 0 || day > 31) {
		std::cout << "\nInvalid day value!";
		return false;
	}
	else if (day == 31 &&
		(month == 2 || month == 4 || month == 6 || month == 9 || month == 11)) {
		std::cout << "\nInvalid day value!";
		return false;
	}
	else if (day == 30 &&
		(month == 1 || month == 2 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) {
		std::cout << "\nInvalid day value!";
		return false;
	}
	else if (day == 29 &&
		month == 2 &&
		!((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
		std::cout << "\nInvalid day value! (Leap year)";
		return false;
	}

	return true;
}

std::ostream& operator<<(std::ostream& outStream, const Date& obj)
{
	outStream.write(reinterpret_cast<const char*>(&obj.day), sizeof(obj.day));
	outStream.write(reinterpret_cast<const char*>(&obj.month), sizeof(obj.month));
	outStream.write(reinterpret_cast<const char*>(&obj.year), sizeof(obj.year));

	return outStream;
}

std::istream& operator>>(std::istream& inStream, Date& obj)
{
	inStream.read(reinterpret_cast<char*>(&obj.day), sizeof(obj.day));
	inStream.read(reinterpret_cast<char*>(&obj.month), sizeof(obj.month));
	inStream.read(reinterpret_cast<char*>(&obj.year), sizeof(obj.year));

	return inStream;
}
