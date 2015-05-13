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

#define SHAKE_DELAY_TIME 100 // 震动延时休眠时间

int GetLastShakeTime();
void ResetLastShakeTime();
void SetShakeInterrupt(char enable);
char GetShakeStatus();


#ifdef	__cplusplus
}
#endif

#endif	/* SHAKETIME_H */

