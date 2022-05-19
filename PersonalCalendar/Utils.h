#pragma once
#include "Event.h"
class Utils {
public:
	static void ReallocateArray(Event* evP, int& capacity);
	static void SortEvents(Event* array, int size);
	static void SortWorkload(int* array,char** secArray, int size);
};