#include "Utils.h"

void Utils::ReallocateArray(Event* evP, int& capacity)
{
	Event* newEventP = new Event[capacity * 2];
	for (int i = 0; i < capacity; i++) {
		newEventP[i] = evP[i];
	}
	capacity *= 2;
	delete[] evP;
	evP = newEventP;
}

void Utils::SortEvents(Event* arr, int size)
{
	int i, j;
	bool swapp;
	for (i = 0; i < size - 1; i++)
	{
		swapp = false;
		for (j = 0; j < size - i - 1; j++)
		{
			if (arr[j].GetStartTime() > arr[j + 1].GetStartTime())
			{
				Event temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapp = true;
			}
		}
		if (swapp == false)
			break;
	}
}

void Utils::SortWorkload(int* arr, char** secArr, int size)
{
	int i, j;
	bool swapp;
	for (i = 0; i < size - 1; i++)
	{
		swapp = false;
		for (j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				char tempStr[11]{};
				strcpy_s(tempStr, 11, secArr[j]);
				strcpy_s(secArr[j], 11, secArr[j + 1]);
				strcpy_s(secArr[j + 1], 11, tempStr);
				swapp = true;
			}
		}
		if (swapp == false)
			break;
	}
}
