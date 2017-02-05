#include "PETime.h"

int PETime::time = 0;
int PETime::stopTime = 0;
int PETime::st_StopTime = 0;
int PETime::ed_StopTime = 0;
int PETime::realTime = 0;

PETime::PETime() {
	realTime = PETime::GetCurrentTimeInMilli();
}

PETime::~PETime() {

}

void PETime::init() {
	PETime();
}

int PETime::GetTime() {
	int tempTime = PETime::GetCurrentTimeInMilli();
	time = tempTime - realTime - stopTime;
	return time;
}

void PETime::StopTime() {
	st_StopTime = PETime::GetCurrentTimeInMilli();
}

void PETime::StartTime() {
	ed_StopTime = PETime::GetCurrentTimeInMilli();
	stopTime += (ed_StopTime - st_StopTime);
}

int PETime::GetCurrentTimeInMilli()
{
	_STRUCT_TIMEVAL time;
	gettimeofday(&time, NULL);

	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return millisecs;
}
