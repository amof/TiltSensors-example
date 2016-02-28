/*
 * File:   main.c
 * Author: Julien
 *
 * Created on 6 février 2016, 12:27
 */

// CONFIG1L
#pragma config WDTEN = OFF      // Watchdog Timer (Disabled - Controlled by SWDTEN bit)
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset (Enabled)
#pragma config XINST = OFF      // Extended Instruction Set (Disabled)

#include <xc.h>

void main(void) {
    
    TRISB=0;
    LATBbits.LATB0=1;
    
    while(1);
    return;
}
