#include "init.h"
#include "Led.h"

void InitLed() {
	ANSELA = 0; // 关闭模拟配置

	LED0_RTIS = 0;
	LED0_PORT = 1;
	LED1_RTIS = 0;
	LED1_PORT = 1;
	LED2_RTIS = 0;
	LED2_PORT = 1;
}

// 设置允许点亮LED，1 允许点亮， 0 不允许点亮
void SetLedEnable(uchar enable)
{
	LED2_RTIS = !enable;
}

// 获取允许点亮LED，1 允许点亮， 0 不允许点亮
byte GetLedEnable()
{
	return !LED2_RTIS;
}

// 点亮LED，1 点亮， 0 不点亮
void SetLedStatus(uchar status) {
	LED0_PORT = status;
	LED1_PORT = status;
	LED2_PORT = status;
}

// 获取LED点亮状态，1 点亮， 0 不点亮
uchar GetLedStatus()
{
	return !LED2_PORT;
}