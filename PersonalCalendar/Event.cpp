#include <cstring>
#include <iostream>
#include "Event.h"

void Event::copy(const Event& other)
{
	size_t titleLen = strlen(other.title);
	this->title = new char[titleLen + 1];
	strcpy_s(this->title, titleLen + 1, other.title);
	this->title[titleLen] = 0;

	size_t commentLen = strlen(other.comment);
	this->comment = new char[commentLen + 1];
	strcpy_s(this->comment, commentLen + 1, other.comment);
	this->comment[commentLen] = 0;

	this->date = other.date;

	this->startTime = other.startTime;
	this->endTime = other.endTime;
}

void Event::clear()
{
	delete[] title;
	delete[] comment;
}

Event::Event()
{
	this->title = new char[1]{};
	this->comment = new char[1]{};
	this->date = Date(1, 1, 2022);
	this->startTime = 0;
	this->endTime = 0;
}

Event::Event(char* title, Date& date, int startTime, int endTime)
{
	size_t titleLen = strlen(title);
	this->title = new char[titleLen + 1];
	strcpy_s(this->title, titleLen + 1, title);
	this->title[titleLen] = 0;

	this->date = date;

	this->startTime = startTime;
	this->endTime = endTime;

	this->comment = new char[1]{};
}

Event::Event(char* title, Date& date, int startTime, int endTime, char* comment)
{
	size_t titleLen = strlen(title);
	this->title = new char[titleLen + 1];
	strcpy_s(this->title, titleLen + 1, title);
	this->title[titleLen] = 0;

	size_t commentLen = strlen(comment);
	this->comment = new char[commentLen + 1];
	strcpy_s(this->comment, commentLen + 1, comment);
	this->comment[commentLen] = 0;

	this->date = date;

	this->startTime = startTime;
	this->endTime = endTime;
}

Event::Event(const Event& other)
{
	copy(other);
}

Event& Event::operator=(const Event& other)
{
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

bool Event::operator==(const Event& other)
{
	if (strcmp(this->title, other.title) != 0)
		return false;
	if (strcmp(this->comment, other.comment) != 0)
		return false;
	if (!(this->date == other.date))
		return false;
	if (this->endTime != other.endTime || this->startTime != other.startTime)
		return false;

	return true;
}

void Event::DisplayOnConsole()
{
	std::cout << "Title: " << this->title << '\n';
	std::cout << "Date: " << this->date.getString() << '\n';
	std::cout << "Start time: " << this->startTime << ":00" << '\n';
	std::cout << "End time: " << this->endTime << ":00" << '\n';
	if (comment && comment[0] != 0)
		std::cout << "Comment: " << this->comment << '\n';
}

char* Event::GetTitle()
{
	return this->title;
}

char* Event::GetComment()
{
	return this->comment;
}

Date& Event::GetDate()
{
	return this->date;
}

int Event::GetStartTime()
{
	return this->startTime;
}

int Event::GetEndTime()
{
	return this->endTime;
}

void Event::SetTitle(char* title)
{
	delete[] this->title;
	size_t len = strlen(title);
	this->title = new char[len + 1];
	strcpy_s(this->title, len + 1, title);
	this->title[len] = 0;
}

void Event::SetComment(char* comm)
{
	delete[] this->comment;
	size_t len = strlen(comm);
	this->comment = new char[len + 1];
	strcpy_s(this->comment, len + 1, comm);
	this->comment[len] = 0;
}

void Event::SetDate(Date& date)
{
	this->date = date;
}

void Event::SetStartTime(int time)
{
	this->startTime = time;
}

void Event::SetEndTime(int time)
{
	this->endTime = time;
}

Event::~Event()
{
	clear();
}

std::ostream& operator<<(std::ostream& outStream, const Event& obj)
{
	size_t tLen = std::strlen(obj.title);
	outStream.write(reinterpret_cast<const char*>(&tLen), sizeof(tLen));
	outStream.write(obj.title, tLen);

	outStream << obj.date;
	outStream.write(reinterpret_cast<const char*>(&obj.startTime), sizeof(obj.startTime));
	outStream.write(reinterpret_cast<const char*>(&obj.endTime), sizeof(obj.endTime));

	size_t commLen = std::strlen(obj.comment);
	outStream.write(reinterpret_cast<const char*>(&commLen), sizeof(commLen));
	outStream.write(obj.comment, commLen);

	return outStream;
}

std::istream& operator>>(std::istream& inStream, Event& obj)
{
	size_t tLen = 0;
	inStream.read(reinterpret_cast<char*>(&tLen), sizeof(tLen));
	obj.title = new char[tLen + 1]{};
	inStream.read(obj.title, tLen);

	inStream >> obj.date;
	inStream.read(reinterpret_cast<char*>(&obj.startTime), sizeof(obj.startTime));
	inStream.read(reinterpret_cast<char*>(&obj.endTime), sizeof(obj.endTime));

	size_t commLen = 0;
	inStream.read(reinterpret_cast<char*>(&commLen), sizeof(commLen));
	obj.comment = new char[commLen + 1]{};
	inStream.read(obj.comment, commLen);

	return inStream;
}
