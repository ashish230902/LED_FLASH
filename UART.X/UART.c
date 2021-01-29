/*
 * File:   LED_FLASH.c
 * Author: Ashish Sharma
 *
 * Created on 11 January, 2021, 3:45 PM
 */


#include "configure.h"

#define _XTAL_FREQ 8000000//8Mhz 

#include <xc.h>
char out;
char rc_data[100];
unsigned int i; /*array index variable */

void setting_registers()
{    
     TRISCbits.TRISC6 = 0;       //direction of Tx and Rx pins
     TRISCbits.TRISC7 = 1;
   
     SPBRG = 12;      /* set the baud rate 9600 
                
     RCSTA1bits.SPEN = 1;        /* enable serial port pins */
     
     RCSTA1bits.SPEN=1;
     RCSTA1bits.CREN = 1;        /* enable reception */
     TXSTA1bits.TXEN = 1;        /* enable the transmitter */ 
}

void transmit_character(char out)
{ 
while(TXIF==0); /*wait for transmit interrupt flag*/
TXREG=out; 

}


__interrupt() void ISR(void)
{
    
    for(i=0;;i++)
{
        
while(RCIF==0); /*wait for receive interrupt flag*/
if(RCSTAbits.OERR)
{ 
RCSTA1bits.CREN = 0;
NOP();
RCSTA1bits.CREN=1;
}
rc_data[i]=RCREG;

if(rc_data[i]=='\r') /*character is received until end of the string received */
{
  for(i=0;i<100;i++)
{ transmit_character(rc_data[i]);
}
rc_data[i]='\0';
break;
}
TXREG=0;
RCREG=0;
}
    
    
 
}

void main()
{
 setting_registers();
 INTCONbits.GIE=1;
 INTCONbits.PEIE=1;
 PIE1bits.RCIE=1;
 IPR1bits.RCIP=1;
 PIE1bits.RCIE=1;
 PIE1bits.TXIE=1;
 while(1);
  
}