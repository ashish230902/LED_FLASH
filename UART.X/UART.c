/*
 * File:   LED_FLASH.c
 * Author: Ashish Sharma
 *
 * Created on 11 January, 2021, 3:45 PM
 */


#include "configure.h"

#define _XTAL_FREQ 40000000//40Mhz 

#include <xc.h>


void setting_registers()
{    
     TRISCbits.TRISC6 = 0;       //direction of Tx and Rx pins
     TRISCbits.TRISC7 = 1;
   
     SPBRG = 12;      /* set the baud rate 9600 
     
     RCSTA1bits.SPEN = 1;        /* enable serial port pins */
     RCSTA1bits.CREN = 1;        /* enable reception */
     TXSTA1bits.TXEN = 1;        /* enable the transmitter */ 
}

void transmit_character(char out)
{ 
while(TXIF==0); /*wait for transmit interrupt flag*/
TXREG=out; /*wait for transmit interrupt flag to set which indicates TXREG is ready
           for another transmission*/ 
}

char USART_ReceiveChar()
{

while(RCIF==0); /*wait for receive interrupt flag*/
if(RCSTAbits.OERR)
{ 
RCSTA1bits.CREN = 0;
NOP();
RCSTA1bits.CREN=1;
}
return(RCREG); /*received in RCREG register and return to main program */
}


void main()
{
    
char out;
char rc_data[100];
unsigned int i; /*array index variable */
setting_registers();
//out = USART_ReceiveChar();
for(i=0;;i++)
{
while(!RCIF);
rc_data[i]=RCREG; 
if(rc_data[i]=='\r') /*character is received until end of the string received */
{
rc_data[i]='\0';
break;
}
} 
for(i=0;i<100;i++)
{ transmit_character(rc_data[i]);
}
    
}


