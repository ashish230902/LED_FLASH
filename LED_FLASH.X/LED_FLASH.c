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
#define _XTAL_FREQ 4000000

#include <xc.h>
void delayzz(void)
{              int i, j;
for(i=0;i<5000;i++)
{
for(j=0;j<2;j++)
{          
}    }   }



void main(void)
{
int analog_reading;
ANCON0 = 0b00000000;
ANCON1 = 0b00000000;
TRISA=1;
ADCON0 = 0b00000001;
ADCON1 = 0b10111110;
// Setting Pwm pin

 
CCP4CON=0b00111100;
CCPR4H = 0b00010000;

TRISB = 0 ; // PORT B Setting: Set all the pins in port B to Output.
TMR2ON =1;
T2CON = 0b100;
CCPTMRS1 = 0b00000000;




while (1)
{

ADON=1;
GO_nDONE=1;
while(GO_nDONE==1);
analog_reading= (ADRESH*256) | (ADRESL);

ADIF =0;

CCPR4L = analog_reading;
//LATBbits.LATB4= analog_reading;
}


}
