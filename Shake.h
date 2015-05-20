/* 
 * File:   ShakeTime.h
 * Author: TBI
 *
 * Created on 2015年5月2日, 下午2:42
 */

#ifndef SHAKETIME_H
#define	SHAKETIME_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "init.h"

#define SHAKE_OFF_TIME	15	// 震动关闭LED延时
#define SHAKE_ON_TIME	5	// 震动开启LED延时

long GetLastShakeTime();
void ResetLastShakeTime();
void SetShakeInterrupt(byte enable);
byte GetShakeStatus();


#ifdef	__cplusplus
}
#endif

#endif	/* SHAKETIME_H */

