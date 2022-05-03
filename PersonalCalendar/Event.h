#pragma once
#include "Date.h"

class Event {
private:
	char* title;
	char* comment;
	Date date;
	int startTime;
	int endTime;

	void copy(const Event& other);
	void clear();
public:
	Event();
	Event(char* title, Date& date, int startTime, int endTime);
	Event(char* title, Date& date, int startTime, int endTime, char* comment);
	Event(const Event& other);
	Event& operator=(const Event& other);
	~Event();
};