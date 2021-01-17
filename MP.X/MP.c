/*
 * File:   LED_FLASH.c
 * Author: Ashish Sharma
 *
 * Created on 11 January, 2021, 3:45 PM
 */


#pragma config DSWDTOSC = INTOSCREF// DSWDT Clock Select (DSWDT uses INTRC)
#pragma config RTCOSC = T1OSCREF// RTCC Clock Select (RTCC uses T1OSC/T1CKI)
#pragma config DSBOREN = ON     // Deep Sleep BOR (Enabled)
#pragma config DSWDTEN = ON     // Deep Sleep Watchdog Timer (Enabled)
#pragma config DSWDTPS = G2     // Deep Sleep Watchdog Postscaler (1:2,147,483,648 (25.7 days))

// CONFIG3H
#pragma config IOL1WAY = ON     // IOLOCK One-Way Set Enable bit (The IOLOCK bit (PPSCON<0>) can be set once)
#pragma config ADCSEL = BIT10   // ADC 10 or 12 Bit Select (10 - Bit ADC Enabled)
#pragma config MSSP7B_EN = MSK7 // MSSP address masking (7 Bit address masking mode)

// CONFIG4L
#pragma config WPFP = PAGE_127  // Write/Erase Protect Page Start/End Location (Write Protect Program Flash Page 127)
#pragma config WPCFG = OFF      // Write/Erase Protect Configuration Region  (Configuration Words page not erase/write-protected)

// CONFIG4H
#pragma config WPDIS = OFF      // Write Protect Disable bit (WPFP<6:0>/WPEND region ignored)
#pragma config WPEND = PAGE_WPFP// Write/Erase Protect Region Select bit (valid when WPDIS = 0) (Pages WPFP<6:0> through Configuration Words erase/write protected)
#pragma config LS48MHZ = SYS48X8// Low Speed USB mode with 48 MHz system clock bit (System clock at 48 MHz USB CLKEN divide-by is set to 8)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 20000000 //20Mhz 

#include <xc.h>
#include <stdio.h>
void delayzz(void)
{  
         TMR0H=0xB3;      // Placing Lower byte in TMR0L

         TMR0L=0xB4;      // Placing Lower byte in TMR0L
       // for(int i =0;i<5;i++) {
        T0CONbits.TMR0ON=1;  // Timer0 On
        
while(INTCONbits.TMR0IF==0) ; // Wait until TMR0IF gets flagged

        T0CONbits.TMR0ON=0;   // Timer0 Off

        INTCONbits.TMR0IF=0;  // Clear Timer0 interrupt flag
       
        //}   
}


void main(void)
{
//Setting timer 0
 T0CON=0b00010111;  // prescale 1:256

 TRISB=0; // all b pins output

while (1)
{
PORTBbits.RB4= 1;
delayzz();
PORTBbits.RB4=0;
delayzz();

}

}

