#include <pic.h>
#include <xc.h>
#include "init.h"
#include "Time.h"
#include "Shake.h"
#include "Led.h"


// 获取环境的亮度
int GetLuminance()
{
    return 0;
}

void interrupt Interrupt()
{
	GIE = 0; // 关闭总中断
	if(TMR0IF)
	{
		TMR0IF = 0; //清除TMR0中断标志位
		TMR0 = 61;
		UpdateSystemTime();
	}
	else if(IOCIF)
	{
		SetShakeInterrupt(0);
	}
	GIE = 1; // 打开总中断
}

void Init()
{
	OSCCON = 0x68; //时钟设置为4MHz
	OPTION_REG = 0x87;
	TMR0IF = 0; //清除TMR0中断标志位
    TMR0 = 61;  //设置中断初始值61

	
    InitSystemTime();
	InitShake();
	InitLed();

	IOCIE = 1; // 开启IO中断
	TMR0IE = 1; // 开启Timer0中断
	GIE = 1; // 开启总中断
}

int main()
{
    // 初始化设置
    Init();

    while(1)
    {
        long time = GetLastShakeTime();
        if(time > SHAKE_DELAY_TIME)
        {
			// 关闭LED
			SetLedStatus(0);
			
            // 开启震动中断，震动触发中断后，在中断函数中关闭中断
            SetShakeInterrupt(1);
            
            // 超时没有震动，进入休眠
            SLEEP();

            // 从休眠中唤醒，重置震动定时器
            ResetLastShakeTime();
        }

		// 打开LED
		SetLedStatus(1);
    }
    return 0;
}
