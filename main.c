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

void dbg(uchar buff)
{
	while(TXSTAbits.TRMT == 0);
	TXREG = buff;
	while(TXSTAbits.TRMT == 0);
}


void interrupt ISR(void) {
	
	if (SYSTEM_TIMER_INT_FLAG) // 定时器中断
	{
		SYSTEM_TIMER_INT_FLAG = 0; //清除TMR0中断标志位
		TMR0 = SYSTEM_TIMER_INIT;

		UpdateSystemTime();
		
	} else if (SHAKE_SENSOR_INT_FLAG) // 震动触发中断
	{
		SHAKE_SENSOR_INT_FLAG = 0;
		dbg(0xaa);
	}
	
}

void InitUSART() {
	TRISAbits.TRISA0 = 0;
	TRISAbits.TRISA1 = 1;
	ANSELAbits.ANSA0 = 0;
	ANSELAbits.ANSA1 = 0;

	APFCON = 0b10000100; //端口复用定义RA5/4 RD TX,RA2 CPP
	TXSTA = 0b00100110; //串口配置字
	RCSTA = 0b10010000; //接受寄存器配置P295
	BAUDCON = 0b01001000; //16位波特率计数器,固定波特率
	SPBRGH = 0b00000000; //011，16位异步,9600波特率,查表103
	SPBRGL = 0x68; //0b01100111;
}//end of initUSART 

void delay(int time)
{
	for(int i=0; i<time; i++)
		for(int j=0; j<200; j++)
			;
}

void print(uchar *buff, char size)
{
	for(int i=0; i<size; i++)
	{
		while(TXSTAbits.TRMT == 0);
		TXREG = *buff;
		while(TXSTAbits.TRMT == 0);
		buff++;
	}
}

#if 1
void Init() {
	OSCCON = 0b00111010;	// 时钟设置为500K
	OPTION_REG = 0x07;		// 256分频

	InitSystemTime();
	InitLed();
	InitLuminance();
	InitUSART();
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
	long luminancetime = 0;
	long time = 0;
	while (1) {
		
		dbg(0xFF);
//		time = GetLastShakeTime();
//		print(&time, sizeof(ulong));
//		time = GetSystemTime();
//		print(&time, sizeof(ulong));

		// 首先判断震动是否超时
		if(GetLastShakeTime() > SHAKE_OFF_TIME || (GetSystemTime() - luminancetime) > LUMINANCE_OFF_TIME)
		{
			if(GetLastShakeTime() > SHAKE_OFF_TIME)
				dbg(0xEE);
			else
				dbg(0xEF);

			// 如果LED已经点亮，等待LED熄灭
			if(GetLedEnable())
				while(GetLedStatus() == 1);
			
			SetLuminanceEnable(0);
			
			// 关闭LED
			SetLedEnable(0);

			// 休眠前先关闭定时器中断，防止定时器将CPU唤醒
			SetSystemTimeInterrupt(0);
			
			// 开启震动中断，震动触发中断后，在中断函数中关闭中断
			SetShakeInterrupt(1);
            
			// 超时没有震动，进入休眠
			SLEEP();

			SetShakeInterrupt(0);

			// 休眠结束后重新计算系统时钟
			InitSystemTime();

			shaketime = GetSystemTime();
			luminancetime = GetSystemTime();

			// 从休眠中唤醒，重置震动定时器
			ResetLastShakeTime();

			// 打开时钟中断
			SetSystemTimeInterrupt(1);

			SetLuminanceEnable(1);
			delay(2);
		}

		if(!GetLedStatus())
		{
			GetLuminance();
		}

		dbg(0x33);
//		dbg(ADRESH);

		if(ADRESH > 0xC5) // || (GetLedStatus() && ADRESH + 0x20 > 0xC5))
		{
			if(GetShakeStatus())
			{
				if(GetSystemTime() - shaketime > SHAKE_ON_TIME)
					SetLedEnable(1);

				ResetLastShakeTime();
				
				dbg(0x22);
			}

			luminancetime = GetSystemTime();
		}
	}
	return 0;
}

#else

void Init() {
	OSCCON = 0b00111010;	// 时钟设置为500K
	OPTION_REG = 0x07;		// 256分频

//	InitSystemTime();
//	InitLed();
	InitLuminance();
	InitUSART();
	InitShake();

//	SetShakeInterrupt(1);
//	SetSystemTimeInterrupt(1);

	IOCIE = 1; // 开启IO中断
	GIE = 1; // 开启总中断
}



int main() {
	// 初始化设置
	Init();

	ulong shaketime = GetSystemTime();
	ulong luminancetime = 0;
	ulong time = 0;
	while (1) {
//		time = GetSystemTime();
		// 首先判断震动是否超时
		//if(GetLastShakeTime() > SHAKE_OFF_TIME || (GetSystemTime() - luminancetime) > 3)
		{
			TXREG = 0xEE;

			SetADEnable(0);

			// 开启震动中断，震动触发中断后，在中断函数中关闭中断
			SetShakeInterrupt(1);

			// 超时没有震动，进入休眠
			SLEEP();

			SetShakeInterrupt(0);
			
			SetADEnable(1);
			delay(2);
		}

		//if(!GetLedStatus())
		{
			ADStart();
			while(ADCON0bits.GO);
		}

		TXREG = 0x33;

		delay(10);
	}
}

#endif