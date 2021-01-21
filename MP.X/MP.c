/*
 * File:   LED_FLASH.c
 * Author: Ashish Sharma
 *
 * Created on 11 January, 2021, 3:45 PM
 */




#include "configure.h"

#define _XTAL_FREQ 20000000 //20Mhz 

#include <xc.h>
void delayzz(void)
{  
   TMR0H=0xB3;      // Placing Lower byte in TMR0L

   TMR0L=0xB4;      // Placing Lower byte in TMR0L
       
   T0CONbits.TMR0ON=1;  // Timer0 On
        
   while(INTCONbits.TMR0IF==0) ; // Wait until TMR0IF gets flagged
     PORTBbits.RB4=0;

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

}

}

