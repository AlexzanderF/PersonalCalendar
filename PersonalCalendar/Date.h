#pragma once
#include <fstream>
class Date {
private:
	int day;
	int month;
	int year;
public:
	Date();
	Date(int day, int month, int year);
	Date& operator=(const Date& other);
	bool operator==(const Date& other);
	bool operator>=(const Date& other);
	bool operator<=(const Date& other);
	bool operator<(const Date& other);
	bool operator>(const Date& other);

	friend std::ostream& operator<< (std::ostream& outStream, const Date& obj);
	friend std::istream& operator>> (std::istream& inStream, Date& obj);

	int GetDay();
	int GetMonth();
	int GetYear();
	void print();
	char* getString() const;

	static bool IsValid(int day, int month, int year);
};