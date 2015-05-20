#include "init.h"
#include "Time.h"
#include "Led.h"

static long iSystemTime = 0;
static byte iCount = 0;

void InitSystemTime() {
	iSystemTime = iCount = 0;
	TMR0 = SYSTEM_TIMER_INIT;
	SYSTEM_TIMER_INT_FLAG = 0; //清除TMR0中断标志位
}

void UpdateSystemTime() {
	iCount = (++iCount) % TICK;
	if((iCount % (TICK/2)) == 0)
		SetLedStatus(GetLedStatus());
	if(iCount == 0)
	{
		iSystemTime++;
	}
	
}

long GetSystemTime() {
	return iSystemTime;
}

void SetSystemTimeInterrupt(byte enable) {
	SYSTEM_TIMER_INT_ENABLE = enable;
}