#include "init.h"
#include "Time.h"
#include "Shake.h"

static int iShakeTime = 0;

void InitShake()
{
	SHAKE_SENSOR_TRIS = 1;
}

// 获取上次震动到现在的时间
int GetLastShakeTime()
{
    return GetSystemTime() - iShakeTime;
}

void ResetLastShakeTime()
{
    iShakeTime = GetSystemTime();
}

void SetShakeInterrupt(char enable)
{
    //REG_SHAKE_INTERRUPT = 0;
}

char GetShakeStatus()
{
	return SHAKE_SENSOR_PORT;
}