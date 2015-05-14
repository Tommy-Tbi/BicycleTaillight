#include "init.h"
#include "Time.h"

static long iSystemTime = 0;
static int iCount = 0;

void InitSystemTime() {
	iSystemTime = iCount = 0;
}

void UpdateSystemTime() {
	if(iCount++ >= TICK)
	{
		iSystemTime++;
		iCount = 0;
	}
}

long GetSystemTime() {
	return iSystemTime;
}

void SetSystemTimeInterrupt(char enable) {
	SYSTEM_TIMER_INT_ENABLE = enable;
}