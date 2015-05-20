#include "init.h"
#include "Time.h"
#include "Shake.h"

static long iShakeTime = 0;

void InitShake() {
	SHAKE_SENSOR_TRIS = 1;
	WPUAbits.WPUA1 = 1; // 开启弱上拉
	ANSELAbits.ANSA1 = 0; // 关闭模拟功能
}

// 获取上次震动到现在的时间
long GetLastShakeTime() {
	return GetSystemTime() - iShakeTime;
}

void ResetLastShakeTime() {
	iShakeTime = GetSystemTime();
}

void SetShakeInterrupt(byte enable) {
	SHAKE_SENSOR_INT_ENABLE = enable;
}

byte GetShakeStatus() {
	return !SHAKE_SENSOR_PORT;
}