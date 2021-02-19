#pragma once
#include <time.h>
#include <cstdlib>
#include <math.h>

class Process
{
	unsigned short index;
	double Duration;

public:

	Process();

	void setDurationTime(double x);			//sprawdzanie i ustawianie czasu wykonania procesu
	double returnDurationTime();		//zwracanie czasu wykonania
	int returnIndex();
	void replaceIndex(double replace); //potrzebne do algorytmu SJF
};

