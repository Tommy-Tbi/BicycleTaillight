/* 
 * File:   Luminance.h
 * Author: TBI
 *
 * Created on 2015年5月14日, 下午9:09
 */

#ifndef LUMINANCE_H
#define	LUMINANCE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LUMINANCE_OFF_TIME 3

void InitLuminance();
int GetLuminance();
void SetLuminanceEnable(byte enable);


#ifdef	__cplusplus
}
#endif

#endif	/* LUMINANCE_H */

