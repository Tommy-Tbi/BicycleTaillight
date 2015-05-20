/* 
 * File:   Led.h
 * Author: TBI
 *
 * Created on 2015年5月2日, 下午5:22
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif

void InitLed();
void SetLedEnable(uchar enable);
void SetLedStatus(uchar status);
uchar GetLedStatus();


#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

