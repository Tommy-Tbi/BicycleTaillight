#include <pic.h>
#include <xc.h>
#include "init.h"
#include "Time.h"
#include "Shake.h"
#include "Led.h"


//***************************************************
//                  ________________
//             VDD-| 1            8 |-VSS
//             RA5-| 2            7 |-RA0/ICSPDAT
//   ____      RA4-| 3            6 |-RA1/ICSPCLK
//   MCLR/Vpp/RA3--| 4            5 |-RA2
//                 |________________|
//                     12LF1840
//***************************************************
char led_status = 0;

// 获取环境的亮度

int GetLuminance() {
	return 0;
}

void interrupt isr(void) {
	if (SYSTEM_TIMER_INT_FLAG) // 定时器中断
	{
		SYSTEM_TIMER_INT_FLAG = 0; //清除TMR0中断标志位
		TMR0 = 61;
		UpdateSystemTime();
	} else if (SHAKE_SENSOR_INT_FLAG) // 震动触发中断
	{
		SHAKE_SENSOR_INT_FLAG = 0;
		SetShakeInterrupt(0);
		LED2_PORT = ~LED2_PORT;
	}
	
}

void Init() {
	OSCCON = 0x68; //时钟设置为4MHz
	OPTION_REG = 0x07;
	SYSTEM_TIMER_INT_FLAG = 0; //清除TMR0中断标志位
	TMR0 = 61; //设置中断初始值61


	InitSystemTime();
	InitLed();
	InitShake();

	SetShakeInterrupt(1);
	SetSystemTimeInterrupt(1);

	IOCIE = 1; // 开启IO中断
	GIE = 1; // 开启总中断
}

void delay(int time) {
	for (int i = 0; i < time; i++)
		for (int j = 0; j < 200; j++)
			;
}

#if 1

int main() {
	// 初始化设置
	Init();

	while (1) {
		long time = GetLastShakeTime();
		if(time > SHAKE_DELAY_TIME)
		{
			// 关闭LED
			SetLedStatus(1);
			
			// 开启震动中断，震动触发中断后，在中断函数中关闭中断
//			SetShakeInterrupt(1);

			// 休眠前先关闭定时器中断，防止定时器将CPU唤醒
			SetSystemTimeInterrupt(0);
            
			// 超时没有震动，进入休眠
			//SLEEP();
			delay(200);

			// 从休眠中唤醒，重置震动定时器
			ResetLastShakeTime();

			// 打开时钟中断
			SetSystemTimeInterrupt(1);
		}

		// 打开LED
		SetLedStatus(0);

		if(!GetShakeStatus())
		{
			ResetLastShakeTime();
			LED1_PORT = ~LED1_PORT;
		}
	}
	return 0;
}

#else

void init_fosc(void) {
	OSCCON = 0x68;
}

void init_gpio(void) {
	PORTA = 0;
	LATA = 0;
	ANSELA = 0;
	TRISAbits.TRISA5 = 0;
}

void init_timer0(void) {
	OPTION_REG = 0x87;
}
//void interrupt isr(void)//中断程序，interrupt是个关键字说明该函数，是中断函数。
//{
//    LED2_PORT = ~LED2_PORT;//改变LED的状态
//    INTCONbits.TMR0IF=0;//清零中断标志位 如果在离开中断程序前没有清零，程序将不停的中断。
//    TMR0=61;//给TMR0付初始值61 ，开始下一个50ms计时做准备。
//   //中断函数结束 返回主函数。哪里来回 回那里去，也就是回到主函数的while(1);处
//
//}

int main(int argc, char** argv) {
	init_fosc();
	init_gpio();
	init_timer0();

	INTCONbits.GIE = 1; //开启总中断

	INTCONbits.TMR0IF = 0; //清零TMR0溢出中断标志位
	INTCONbits.TMR0IE = 1; //开启TMR0溢出中断
	TMR0 = 61;
	while (1); //主函数 在此什么都没做一直在死循环。但等到50ms时间到了TMR0将会溢出，程序就会跳到void interrupt isr(void)处执行。

}

#endif