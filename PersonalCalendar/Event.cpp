#include <cstring>
#include "Event.h"

void Event::copy(const Event& other)
{
	size_t titleLen = strlen(other.title);
	this->title = new char[titleLen + 1];
	strcpy_s(this->title, titleLen + 1, other.title);

	if (other.comment) {
		size_t commentLen = strlen(other.comment);
		this->comment = new char[commentLen + 1];
		strcpy_s(this->comment, commentLen + 1, other.comment);
	}

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
	this->title = nullptr;
	this->comment = nullptr;
	this->date = Date(1, 1, 2022);
	this->startTime = 0;
	this->endTime = 0;
}

Event::Event(char* title, Date& date, int startTime, int endTime)
{
	size_t titleLen = strlen(title);
	this->title = new char[titleLen + 1];
	strcpy_s(this->title, titleLen + 1, title);

	this->date = date;

	this->startTime = startTime;
	this->endTime = endTime;
}

Event::Event(char* title, Date& date, int startTime, int endTime, char* comment)
{
	size_t titleLen = strlen(title);
	this->title = new char[titleLen + 1];
	strcpy_s(this->title, titleLen + 1, title);

	size_t commentLen = strlen(comment);
	this->comment = new char[commentLen + 1];
	strcpy_s(this->comment, commentLen + 1, comment);

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

Event::~Event()
{
	clear();
}
