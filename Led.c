#include "init.h"
#include "Led.h"

void InitLed()
{
	LED0_RTIS = 0;
	LED0_PORT = 1;
	LED1_RTIS = 0;
	LED1_PORT = 1;
	LED2_RTIS = 0;
	LED2_PORT = 1;
}

void SetLedStatus(char status)
{
	LED0_PORT = status;
	LED1_PORT = status;
	LED2_PORT = status;
}