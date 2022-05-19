#include <stdio.h>
#include <iostream>
#include "Calendar.h"
#include "Utils.h"
#include "Enums.h"

Calendar::Calendar()
{
}

void Calendar::AddEvent(const Event& newEvent)
{
	std::ofstream file("calendar.bin", std::ios::app | std::ios::binary);

	if (file.is_open()) {

		file << newEvent;

		file.close();
	}
}

void Calendar::AddEvent(char* title, Date& date, int startTime, int endTime)
{
	std::ofstream file("calendar.bin", std::ios::app | std::ios::binary);

	Event newEvent(title, date, startTime, endTime);

	if (file.is_open()) {

		file << newEvent;

		file.close();
	}
}

void Calendar::AddEvent(char* title, Date& date, int startTime, int endTime, char* comment)
{
	std::ofstream file("calendar.bin", std::ios::app | std::ios::binary);

	Event newEvent(title, date, startTime, endTime, comment);

	if (file.is_open()) {

		file << newEvent;

		file.close();
	}
}

void Calendar::CancelEvent(const Event& ev)
{
	std::ifstream file("calendar.bin", std::ios::in | std::ios::binary);
	std::ofstream newFile("temp.bin", std::ios::app | std::ios::binary);

	if (file.is_open()) {
		if (newFile.is_open()) {
			while (!file.eof())
			{
				Event currEvent;
				file >> currEvent;
				if (!file)
					break;

				if (currEvent == ev)
				{
					std::cout << "Event deleted" << '\n';
				}
				else {
					newFile << currEvent;
				}
			}

			file.close();
			remove("calendar.bin");

			int res = rename("temp.bin", "calendar.bin");
			if (res != 0)
				throw std::runtime_error("Failed canceling event.");
			newFile.close();
		}
	}
}

void Calendar::CancelEvent(char* title, Date& date)
{
	std::ifstream file("calendar.bin", std::ios::in | std::ios::binary);
	std::ofstream newFile("temp.bin", std::ios::app | std::ios::binary);

	if (file.is_open()) {
		if (newFile.is_open()) {

			while (!file.eof())
			{
				Event currEvent;
				file >> currEvent;
				if (!file)
					break;

				if (strcmp(currEvent.GetTitle(), title) == 0 && currEvent.GetDate() == date)
				{
					std::cout << "Event deleted" << '\n';
				}
				else {
					newFile << currEvent;
				}
			}
			file.close();
			newFile.close();

			remove("calendar.bin");

			int res = rename("temp.bin", "calendar.bin");
			if (res != 0)
				throw std::runtime_error("Failed canceling event.");
		}
	}
}

void Calendar::DailySchedule(Date& date)
{
	std::ifstream file("calendar.bin", std::ios::in | std::ios::binary);

	int idx = -1;
	int capacity = 4;
	Event* dailyEvents = new Event[capacity];

	while (!file.eof())
	{
		Event currEvent;
		file >> currEvent;
		if (!file)
			break;

		if (currEvent.GetDate() == date) {
			++idx;
			if (idx == capacity) {
				Utils::ReallocateArray(dailyEvents, capacity);
			}
			dailyEvents[idx] = currEvent;
		}
	}
	file.close();
	Utils::SortEvents(dailyEvents, idx + 1);

	std::cout << '\n';
	std::cout << "Daily program for (" << date.getString() << ") :" << '\n';
	std::cout << '\n';
	for (int i = 0; i <= idx; i++) {
		dailyEvents[i].DisplayOnConsole();
	}

	delete[] dailyEvents;
}

void Calendar::UpdateEvent(char* title, Date& date, Event& modifiedEvent, int option)
{
	std::ifstream file("calendar.bin", std::ios::in | std::ios::binary);
	std::ofstream newFile("temp.bin", std::ios::app | std::ios::binary);

	if (file.is_open()) {
		if (newFile.is_open()) {

			while (!file.eof())
			{
				Event currEvent;
				file >> currEvent;
				if (!file)
					break;

				if (strcmp(currEvent.GetTitle(), title) == 0 && currEvent.GetDate() == date) {
					if (option == (int)UpdateOption::Title)
						currEvent.SetTitle(modifiedEvent.GetTitle());
					else if (option == (int)UpdateOption::Comment)
						currEvent.SetComment(modifiedEvent.GetComment());
					else if (option == (int)UpdateOption::DateOpt)
						currEvent.SetDate(modifiedEvent.GetDate());
					else if (option == (int)UpdateOption::StartTime)
						currEvent.SetStartTime(modifiedEvent.GetStartTime());
					else if (option == (int)UpdateOption::EndTime)
						currEvent.SetEndTime(modifiedEvent.GetEndTime());
				}

				newFile << currEvent;
			}
			file.close();
			newFile.close();

			remove("calendar.bin");

			int res = rename("temp.bin", "calendar.bin");
			if (res != 0)
				throw std::runtime_error("Failed updating event.");
		}
	}
}

void Calendar::FindEvents(char* searchInput)
{
	std::cout << '\n';
	std::cout << "Results:" << '\n';
	std::cout << '\n';

	bool found = false;
	std::ifstream file("calendar.bin", std::ios::in | std::ios::binary);
	while (!file.eof())
	{
		Event currEvent;
		file >> currEvent;
		if (!file)
			break;

		char* titleOccurance = strstr(currEvent.GetTitle(), searchInput);
		if (titleOccurance) {
			if (!found)
				found = true;
			currEvent.DisplayOnConsole();
		}
		else {
			char* commentOccurance = strstr(currEvent.GetComment(), searchInput);
			if (commentOccurance) {
				currEvent.DisplayOnConsole();
				if (!found)
					found = true;
			}
		}
	}
	if (!found)
		std::cout << "Nothing was found." << '\n';
	file.close();

}

void Calendar::GetReport(Date& startDate, Date& endDate)
{
	char fileName[21]{};
	strcat_s(fileName, 21, "stats-");
	strcat_s(fileName, 21, startDate.getString());
	strcat_s(fileName, 21, ".txt");

	int numberOfDays = endDate.GetDay() - startDate.GetDay(); // end day is not included
	int* dailyWorkload = new int[numberOfDays] {0};
	char** correspondingDates = new char* [numberOfDays];
	for (int i = 0; i < numberOfDays; i++) {
		correspondingDates[i] = new char[11]{};
	}

	std::ifstream dataFile("calendar.bin", std::ios::in | std::ios::binary);
	if (dataFile.is_open()) {
		while (!dataFile.eof())
		{
			Event currEvent;
			dataFile >> currEvent;
			if (!dataFile)
				break;

			Date& currDate = currEvent.GetDate();
			if (currDate.GetMonth() == startDate.GetMonth() &&
				currDate.GetDay() >= startDate.GetDay() && currDate.GetDay() < endDate.GetDay())
			{
				int workload = currEvent.GetEndTime() - currEvent.GetStartTime();
				int day = endDate.GetDay() - currDate.GetDay();

				strcpy_s(correspondingDates[day - 1], 11, currDate.getString());
				dailyWorkload[day - 1] += workload;
			}
		}
		dataFile.close();
	}

	Utils::SortWorkload(dailyWorkload, correspondingDates, numberOfDays);

	std::ofstream file(fileName, std::ios::app);
	if (file.is_open()) {
		file << "Workload results:\n";
		for (int d = numberOfDays - 1; d >= 0; d--) {
			if (dailyWorkload[d] > 0) {
				file << correspondingDates[d] << " : ";
				file << dailyWorkload[d] << " (total hours)" << '\n';
			}
		}

		file.close();
	}

	for (int i = 0; i < numberOfDays; i++) {
		delete[] correspondingDates[i];
	}
	delete[] correspondingDates;
	delete[] dailyWorkload;
}

void Calendar::FindFreeTime(int startTime, int endTime, int month, int week)
{
	std::cout << '\n';
	bool weekEvents[7][24]{};  // mark free time as false and busy as true

	std::ifstream file("calendar.bin", std::ios::in | std::ios::binary);
	while (!file.eof())
	{
		Event currEvent;
		file >> currEvent;
		if (!file)
			break;

		Date& currDate = currEvent.GetDate();
		if (currDate.GetMonth() == month &&
			currDate.GetDay() > ((week * 7) - 7) && currDate.GetDay() <= week * 7)
		{
			int dayOfWeek = currDate.GetDay() - (week * 7 - 7); //  gets the number of the day in a week(1st, 2nd, ...) 
			// h < EndTime because ending time isn't marked as busy
			for (int h = currEvent.GetStartTime(); h < currEvent.GetEndTime(); h++) {
				// -1 BECAUSE INDEXES ARE 1 LOWER THAN DAYS
				weekEvents[dayOfWeek - 1][h] = true;
			}
		}
	}
	file.close();

	// check if the indexes between the choosen start time and end time are free(false or true) !  
	int freeDayNum = 0;
	bool isDayFree = false;
	for (int d = 0; d < 7; d++) {
		isDayFree = true;

		if (weekEvents[d][startTime])
			continue;

		for (int h = startTime + 1; h < endTime; h++) {
			if (weekEvents[d][h]) {
				isDayFree = false;
				break;
			}
		}

		if (isDayFree) {
			freeDayNum = d + 1;
			break;
		}
	}

	if (isDayFree && freeDayNum > 0) {
		Date freeDate((week * 7) - 7 + freeDayNum, month, 2022);
		std::cout << "The time interval you choosed is free on " << freeDate.getString() << " !" << '\n';
	}
	else {
		std::cout << "No free days left for this week!" << '\n';
	}

	return;
}

void Calendar::DisplayAll()
{
	std::ifstream file("calendar.bin", std::ios::in | std::ios::binary);
	while (!file.eof())
	{
		Event currEvent;
		file >> currEvent;
		if (!file)
			break;

		currEvent.DisplayOnConsole();
	}
	file.close();
}
