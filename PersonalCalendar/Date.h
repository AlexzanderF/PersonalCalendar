#pragma once
class Date {
private:
	int day;
	int month;
	int year;
public:
	Date();
	Date(int day, int month, int year);
	Date& operator=(const Date& other);

	int GetDay();
	int GetMonth();
	int GetYear();
	void print();
	char* getString();
};