/* 
 * File:   init.h
 * Author: TBI
 *
 * Created on 2015年5月1日, 下午11:29
 */

#ifndef INIT_H
#define	INIT_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)


#define REG_SHAKE_INTERRUPT PORTA

#define SYSTEM_TIMER	

#define SHAKE_SENSOR_TRIS	TRISA4	// Shake Sensor Config I/O
#define SHAKE_SENSOR_PORT	RA4	// Shake Sensor I/O

#define LED0_RTIS	TRISA0
#define LED0_PORT	RA0
#define LED1_RTIS	TRISA1
#define LED1_PORT	RA1
#define LED2_RTIS	TRISA2
#define LED2_PORT	RA2


#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */

