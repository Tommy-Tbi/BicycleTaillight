#include "init.h"
#include "Luminance.h"

void InitLuminance()
{
	TRISAbits.TRISA2 = 1; // 设置为输入
	ANSELAbits.ANSA2 = 1; // 设置模拟功能启用
	ADCON0 = 0B00001000; // 设置启用AN2
	ADCON1 = 0B01110000; //
}

void SetLuminanceEnable(byte enable)
{
	ADCON0bits.ADON = enable;
}

int GetLuminance()
{
	ADCON0bits.GO = 1;
	while(ADCON0bits.GO);
	return ADRESH;
}
