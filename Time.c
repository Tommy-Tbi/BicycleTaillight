#include "init.h"
#include "Time.h"

static long iSystemTime = 0;

void InitSystemTime()
{
    iSystemTime = 0;
}

void UpdateSystemTime()
{
	iSystemTime++;
}

long GetSystemTime()
{
	return iSystemTime;
}

void SetSystemTimeInterrupt(char enable)
{
	SYSTEM_TIMER_INT = enable;
}