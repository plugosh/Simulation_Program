#include "Process.h"

Process::Process() : index(0), Duration(0.5)
{
}


void Process::setDurationTime(double x)
{
	Duration = x;
}

double Process::returnDurationTime()
{
	return Duration;
}

int Process::returnIndex()
{
	return index;
}

void Process::replaceIndex(double replace)
{
	this->index = replace;
}
