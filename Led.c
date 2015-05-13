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

void SetLedStatus(char status) {
	LED0_PORT = status;
	LED1_PORT = status;
	LED2_PORT = status;
}