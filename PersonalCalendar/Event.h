#pragma once
#include "Date.h"
#include <fstream>

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
	~Event();
	Event& operator=(const Event& other);
	bool operator==(const Event& other);

	friend std::ostream& operator<< (std::ostream& outStream, const Event& obj);
	friend std::istream& operator>> (std::istream& inStream, Event& obj);

	void DisplayOnConsole();
	char* GetTitle();
	char* GetComment();
	Date& GetDate();
	int GetStartTime();
	int GetEndTime();

	void SetTitle(char* title);
	void SetComment(char* comm);
	void SetDate(Date& date);
	void SetStartTime(int time);
	void SetEndTime(int time);
};