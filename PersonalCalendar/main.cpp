#include <iostream>
#include <cstring>
#include "Date.h"
#include "Event.h"
#include "Calendar.h"

void StartApplication();
void AddNewEvent();
void CancelEvent();
void DailySchedule();
void Search();
void UpdateEvent();
void GetReport();
void FindFreeTime();

int main() {
	Calendar cal;
	cal.DisplayAll();

	StartApplication();

	return 0;
}

void StartApplication() {
	std::cout << "Choose action from the menu options and enter its value(1-5): " << "\n";
	std::cout << "(1) - Add New Event" << "\n";
	std::cout << "(2) - Cancel Event" << "\n";
	std::cout << "(3) - Get Daily Schedule" << "\n";
	std::cout << "(4) - Update Event" << "\n";
	std::cout << "(5) - Search for Event" << "\n";
	std::cout << "(6) - Find Free time" << "\n";
	std::cout << "(7) - Get Workload Report for a period of time" << "\n";
	int option = 0;
	std::cout << "Enter your choice: ";
	std::cin >> option;
	std::cout << "\n";

	if (option == MenuAction::eAddEvent)
		AddNewEvent();
	else if (option == MenuAction::eCancelEvent)
		CancelEvent();
	else if (option == MenuAction::eDailySchedule)
		DailySchedule();
	else if (option == MenuAction::eSearch)
		Search();
	else if (option == MenuAction::eUpdateEvent)
		UpdateEvent();
	else if (option == MenuAction::eFindFreeTime)
		FindFreeTime();
	else if (option == MenuAction::eGetReport)
		GetReport();
	else
		std::cout << "Invalid option value!\n";

	std::cout << "\nDo you want to continue using the application?\n";
	std::cout << "(Y or N) : ";
	char cont;
	std::cin >> cont;
	if (cont == 'Y')
		StartApplication();
	else
		return;
}
void AddNewEvent() {
	char name[101];
	int day;
	int month;
	int year;
	int starTime;
	int endTime;

	std::cout << "Create Event:" << "\n";
	std::cout << "Enter name: ";
	std::cin.ignore();
	std::cin.getline(name, 100, '\n');
	std::cout << "Enter day: ";
	std::cin >> day;
	std::cout << "Enter month: ";
	std::cin >> month;
	std::cout << "Enter year: ";
	std::cin >> year;
	if (!Date::IsValid(day, month, year))
		return;
	Date date(day, month, year);
	std::cout << "Enter starting time: ";
	std::cin >> starTime;
	std::cout << "Enter end time: ";
	std::cin >> endTime;
	std::cout << "Do you want to add a comment?\n";
	std::cout << "(Y or N) : ";
	char opt;
	std::cin >> opt;
	if (opt == 'Y') {
		char comment[251];
		std::cout << "Enter comment: ";
		std::cin.ignore();
		std::cin.getline(comment, 251, '\n');
		std::cout << "\n";
		Event newEvent(name, date, starTime, endTime, comment);
		Calendar calendar;
		calendar.AddEvent(newEvent);
	}
	else if (opt == 'N') {
		std::cout << "\n";
		Event newEvent(name, date, starTime, endTime);
		Calendar calendar;
		calendar.AddEvent(newEvent);
	}
	std::cout << "...\n";
	std::cout << "Event created!";
};
void CancelEvent() {
	char name[101];
	int day;
	int month;
	int year;

	std::cout << "Cancel an Event by entering its title and date:" << "\n";
	std::cout << "Enter name: ";
	std::cin.ignore();
	std::cin.getline(name, 101, '\n');
	std::cout << "Enter day: ";
	std::cin >> day;
	std::cout << "Enter month: ";
	std::cin >> month;
	std::cout << "Enter year: ";
	std::cin >> year;
	if (!Date::IsValid(day, month, year))
		return;
	Date date(day, month, year);
	std::cout << "\n";
	Calendar calendar;
	calendar.CancelEvent(name, date);
	std::cout << "...\n";
	std::cout << "Event was canceled!";

};
void DailySchedule() {
	int day;
	int month;
	int year;

	std::cout << "Get the daily schedule for a certain date:" << "\n";
	std::cout << "Enter day: ";
	std::cin >> day;
	std::cout << "Enter month: ";
	std::cin >> month;
	std::cout << "Enter year: ";
	std::cin >> year;
	if (!Date::IsValid(day, month, year))
		return;
	Date date(day, month, year);
	std::cout << "...\n";
	Calendar calendar;
	calendar.DailySchedule(date);

};
void Search() {
	char input[251];
	std::cout << "Search events by their title or comment:" << "\n";
	std::cout << "Enter search value: ";
	std::cin.ignore();
	std::cin.getline(input, 251, '\n');
	std::cout << "\n";
	Calendar calendar;
	calendar.FindEvents(input);
};
void UpdateEvent() {
	char name[101];
	int day;
	int month;
	int year;

	std::cout << "Update an Event by providing its title and date:" << "\n";
	std::cout << "Enter name: ";
	std::cin.ignore();
	std::cin.getline(name, 101, '\n');
	std::cout << "Enter day: ";
	std::cin >> day;
	std::cout << "Enter month: ";
	std::cin >> month;
	std::cout << "Enter year: ";
	std::cin >> year;
	if (!Date::IsValid(day, month, year))
		return;
	Date date(day, month, year);
	std::cout << "Choose what do you want to update (1-5):" << "\n";
	std::cout << "(1) - Title" << "\n";
	std::cout << "(2) - Comment" << "\n";
	std::cout << "(3) - Date" << "\n";
	std::cout << "(4) - StartTime" << "\n";
	std::cout << "(5) - EndTime" << "\n";
	int option = 0;
	std::cout << "Enter your choice: ";
	std::cin >> option;
	std::cout << "\n";

	Event newMod;
	Calendar calendar;
	if (option == UpdateOption::Title) {
		char newName[101];
		std::cout << "Enter new title: ";
		std::cin.ignore();
		std::cin.getline(newName, 101, '\n');
		newMod.SetTitle(newName);
		calendar.UpdateEvent(name, date, newMod, option);
	}
	else if (option == UpdateOption::Comment) {
		char newComment[251];
		std::cout << "Enter new comment: ";
		std::cin.ignore();
		std::cin.getline(newComment, 251, '\n');
		newMod.SetComment(newComment);
		calendar.UpdateEvent(name, date, newMod, option);
	}
	else if (option == UpdateOption::DateOpt) {
		int newDay;
		int newMonth;
		int newYear;
		std::cout << "Enter day: ";
		std::cin >> newDay;
		std::cout << "Enter month: ";
		std::cin >> newMonth;
		std::cout << "Enter year: ";
		std::cin >> newYear;
		if (!Date::IsValid(newDay, newMonth, newYear))
			return;
		Date newDate(newDay, newMonth, newYear);
		newMod.SetDate(newDate);
		calendar.UpdateEvent(name, date, newMod, option);
	}
	else if (option == UpdateOption::EndTime) {
		int newTime;
		std::cout << "Enter new start time: ";
		std::cin >> newTime;
		newMod.SetStartTime(newTime);
		calendar.UpdateEvent(name, date, newMod, option);
	}
	else if (option == UpdateOption::StartTime) {
		int newTime;
		std::cout << "Enter new end time: ";
		std::cin >> newTime;
		newMod.SetEndTime(newTime);
		calendar.UpdateEvent(name, date, newMod, option);
	}
	else
		std::cout << "Invalid option value!";
};
void GetReport() {
	int firstDay;
	int secDay;
	int month;
	int year;
	std::cout << "Enter start day: ";
	std::cin >> firstDay;
	std::cout << "Enter end day: ";
	std::cin >> secDay;
	std::cout << "Enter month: ";
	std::cin >> month;
	std::cout << "Enter year: ";
	std::cin >> year;
	if (!Date::IsValid(firstDay, month, year))
		return;
	if (!Date::IsValid(secDay, month, year))
		return;

	Date startDate(firstDay, month, year);
	Date endDate(secDay, month, year);
	Calendar calendar;
	calendar.GetReport(startDate, endDate);
}
void FindFreeTime() {
	int startTime;
	int endTime;
	int month;
	int weekOfMonth;

	std::cout << "Find the closest free time available for you:" << "\n";
	std::cout << "Enter month: ";
	std::cin >> month;
	std::cout << "Enter the number of the week for this month(1-4): ";
	std::cin >> weekOfMonth;
	std::cout << "Enter start time: ";
	std::cin >> startTime;
	std::cout << "Enter end time: ";
	std::cin >> endTime;

	Calendar calendar;
	calendar.FindFreeTime(startTime, endTime, month, weekOfMonth);
}
