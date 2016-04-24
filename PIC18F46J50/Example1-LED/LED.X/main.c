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

// CONFIG1H
#pragma config CPUDIV = OSC1    // CPU System Clock Postscaler (No CPU system clock divide)
#pragma config CP0 = OFF        // Code Protect (Program memory is not code-protected)

// CONFIG2L
#pragma config OSC = HS         // Oscillator (HS, USB-HS)
#pragma config T1DIG = ON       // T1OSCEN Enforcement (Secondary Oscillator clock source may be selected)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator (High-power operation)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor (Enabled)
#pragma config IESO = OFF        // Internal External Oscillator Switch Over Mode (Enabled)

// CONFIG2H
#pragma config WDTPS = 32768    // Watchdog Postscaler (1:32768)

// CONFIG3L
#pragma config DSWDTOSC = INTOSCREF// DSWDT Clock Select (DSWDT uses INTRC)
#pragma config RTCOSC = T1OSCREF// RTCC Clock Select (RTCC uses T1OSC/T1CKI)
#pragma config DSBOREN = OFF     // Deep Sleep BOR (Enabled)
#pragma config DSWDTEN = OFF     // Deep Sleep Watchdog Timer (Enabled)
#pragma config DSWDTPS = G2     // Deep Sleep Watchdog Postscaler (1:2,147,483,648 (25.7 days))

// CONFIG3H
#pragma config IOL1WAY = ON     // IOLOCK One-Way Set Enable bit (The IOLOCK bit (PPSCON<0>) can be set once)
#pragma config MSSP7B_EN = MSK7 // MSSP address masking (7 Bit address masking mode)

// CONFIG4L
#pragma config WPFP = PAGE_63   // Write/Erase Protect Page Start/End Location (Write Protect Program Flash Page 63)
#pragma config WPEND = PAGE_WPFP// Write/Erase Protect Region Select (valid when WPDIS = 0) (Page WPFP<5:0> through Configuration Words erase/write protected)
#pragma config WPCFG = OFF      // Write/Erase Protect Configuration Region (Configuration Words page not erase/write-protected)

// CONFIG4H
#pragma config WPDIS = OFF      // Write Protect Disable bit (WPFP<5:0>/WPEND region ignored)

#define LedGreen                PORTDbits.RD6
#define TRISLedGreen			TRISDbits.TRISD6

#include <p18F46J50.h>

#pragma interrupt low_isr save=PROD //Context Save
void low_isr (void)
{
	if (PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF=0;
        TMR1H=0xE0;
        TMR1L=0x00;
        LedGreen=~LedGreen;
    }
}
#pragma	code

#pragma code low_vector=0x18 //Low interrupt priority starts at 0x18
void low_interrupt(void)
{
_asm GOTO low_isr _endasm
}
#pragma code



void main(void) {
    
    TRISLedGreen=0;
    PIE1bits.TMR1IE=1; //Enable interruption
    TMR1H=0x80;
    TMR1L=0x00;
    T1CONbits.TMR1CS=0x02; // Timer clock source is the T1OSC
    T1CONbits.T1SYNC=0x01; // Do not synchronize external clock input
    T1CONbits.T1OSCEN=0x01; // Power up the Timer1 crystal driver and supply the Timer1 clock from the crystal output

    
    T1CONbits.TMR1ON=1; // Enables Timer1

    
    
    IPR1 = 0;  IPR2 = 0;   IPR3 = 0;//Toutes les interruptions en low priority
    //	RCON		//RESET CONTROL REGISTER
    RCONbits.IPEN = 1; //RESET CONTROL REGISTER

    //	INTCON
    INTCONbits.GIE = 1; //Global Interrupt Enable bit
    INTCONbits.PEIE = 1; //Peripheral Interrupt Enable bit
    
    OSCCONbits.IDLEN = 0; // Not in Idle
    WDTCONbits.REGSLP=1; // Regulator Low power
    Sleep();
    
    while(1);
    return;
}
