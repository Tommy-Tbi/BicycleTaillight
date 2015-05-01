#include <pic.h>
#include <xc.h>
#include "init.h"

int iShakeTime = 0;

// 获取环境的亮度
int GetLuminance()
{
    return 0;
}

// 获取上次休眠到现在的时间
int GetShakeTime()
{
    return 0;
}

void ResetShakeTime()
{
    iShakeTime = 0;
}

int main()
{
    int i = 0;
    
    while(1)
    {
        i++;
    }
    return 0;
}
