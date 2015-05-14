#include <pic.h>
#include <xc.h>
#include "init.h"
#include "Time.h"
#include "Shake.h"
#include "Led.h"
#include "Luminance.h"


//***************************************************
//                  ________________
//             VDD-| 1            8 |-VSS
//             RA5-| 2            7 |-RA0/ICSPDAT
//   ____      RA4-| 3            6 |-RA1/ICSPCLK
//   MCLR/Vpp/RA3--| 4            5 |-RA2
//                 |________________|
//                      12LF1840
//***************************************************

void interrupt ISR(void) {
	
	if (SYSTEM_TIMER_INT_FLAG) // 定时器中断
	{
		SYSTEM_TIMER_INT_FLAG = 0; //清除TMR0中断标志位
		TMR0 = SYSTEM_TIMER_INIT;

		UpdateSystemTime();
//		LED1_PORT = ~LED1_PORT;
		
	} else if (SHAKE_SENSOR_INT_FLAG) // 震动触发中断
	{
		SHAKE_SENSOR_INT_FLAG = 0;
		SetShakeInterrupt(0);
	}
	
}

void Init() {
	OSCCON = 0x3B;		// 时钟设置为500K
	OPTION_REG = 0x07;	// 256分频
	SYSTEM_TIMER_INT_FLAG = 0; //清除TMR0中断标志位
	TMR0 = SYSTEM_TIMER_INIT; // 设置中断初始值


	InitSystemTime();
	InitLed();
	InitShake();

	SetShakeInterrupt(1);
	SetSystemTimeInterrupt(1);

	IOCIE = 1; // 开启IO中断
	GIE = 1; // 开启总中断
}

int main() {
	// 初始化设置
	Init();

	long shaketime = GetSystemTime();
	while (1) {

		// 首先判断震动是否超时
		if(GetLastShakeTime() > SHAKE_OFF_TIME)
		{
			// 关闭LED
			SetLedStatus(1);
			
			// 开启震动中断，震动触发中断后，在中断函数中关闭中断
			SetShakeInterrupt(1);

			// 休眠前先关闭定时器中断，防止定时器将CPU唤醒
			SetSystemTimeInterrupt(0);
            
			// 超时没有震动，进入休眠
			SLEEP();

			// 休眠结束后重新计算系统时钟
			InitSystemTime();

			shaketime = GetSystemTime();

			// 从休眠中唤醒，重置震动定时器
			ResetLastShakeTime();

			// 打开时钟中断
			SetSystemTimeInterrupt(1);
		}

		if(!GetShakeStatus())
		{
			if(GetSystemTime() - shaketime > SHAKE_ON_TIME)
				SetLedStatus(0);
			
			ResetLastShakeTime();
		}
	}
	return 0;
}