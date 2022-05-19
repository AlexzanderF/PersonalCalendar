#pragma once
#include "Event.h"
#include "Date.h"
#include "Enums.h"

class Calendar {
private:
public:
	Calendar();

	void AddEvent(const Event& newEvent);
	void AddEvent(char* title, Date& date, int startTime, int endTime);
	void AddEvent(char* title, Date& date, int startTime, int endTime, char* comment);

	void CancelEvent(const Event& ev);
	void CancelEvent(char* title, Date& date);

	void DailySchedule(Date& date);

	void UpdateEvent(char* title, Date& date, Event& modifiedEvent, int option);

	void FindEvents(char* searchInput);

	void GetReport(Date& startDate, Date& endDate);

	void FindFreeTime(int startTime, int endTime, int month, int week);

	void DisplayAll();
};