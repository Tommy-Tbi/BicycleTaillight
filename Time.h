/* 
 * File:   Time.h
 * Author: TBI
 *
 * Created on 2015年5月2日, 下午4:23
 */

#ifndef TIME_H
#define	TIME_H

#ifdef	__cplusplus
extern "C" {
#endif

#define TICK 10 // 10ms 时钟滴答

void InitSystemTime();
void UpdateSystemTime();
long GetSystemTime();
void SetSystemTimeInterrupt(byte enable);


#ifdef	__cplusplus
}
#endif

#endif	/* TIME_H */

