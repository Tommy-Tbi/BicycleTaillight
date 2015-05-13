#include "init.h"
#include "Time.h"
#include "Shake.h"

static int iShakeTime = 0;

void InitShake() {
	SHAKE_SENSOR_TRIS = 1;
	WPUAbits.WPUA1 = 1; // 开启弱上拉
//	WPUAbits.WPUA0 = 1;
}

// 获取上次震动到现在的时间

int GetLastShakeTime() {
	return GetSystemTime() - iShakeTime;
}

void ResetLastShakeTime() {
	iShakeTime = GetSystemTime();
}

void SetShakeInterrupt(char enable) {
	SHAKE_SENSOR_INT_ENABLE = enable;
}

char GetShakeStatus() {
	return SHAKE_SENSOR_PORT;
}