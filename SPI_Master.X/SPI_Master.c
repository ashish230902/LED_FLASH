/*
 * File:   LED_FLASH.c
 * Author: Ashish Sharma
 *
 * Created on 11 January, 2021, 3:45 PM
 */


#include "configure.h"

#define _XTAL_FREQ 8000000//8Mhz 

#include <xc.h>
void SPI_Init_Master()
{
    /* PORT definition for SPI pins*/    
    TRISBbits.TRISB5 =1;	/* RB0 as input(SDI) */
    TRISBbits.TRISB4=0;		/* RB1 as output(SCK) */
    TRISAbits.TRISA5=0;		/* RA5 as a output(SS') */
    TRISCbits.TRISC7=0;		/* RC7 as output(SDO) */
    TRISAbits.TRISA5 =0;

    /* To initialize SPI Communication configure following Register*/
    PORTAbits.RA5= 1;
    SSPSTAT=0x40;		/* Data change on rising edge of clk , BF=0*/
    SSPCON1=0b00100010;		/* Master mode,Serial enable,
				idle state low for clk, fosc/64 */ 
    PIR1bits.SSPIF=0;

    /* Disable the ADC channel which are on for multiplexed pin when
    used as an input */    
    ADCON0=0;			/* This is for de-multiplexed the 
				SCL and SDI from analog pins*/
    ADCON1=0x0F;		/* This makes all pins as digital I/O */
}
void SPIM_Write(unsigned char x)
{
    unsigned char data_flush;
    SSPBUF=x;			/* Copy data in SSBUF to transmit */

    while(!PIR1bits.SSPIF);	/* Wait for complete 1 byte transmission */
    PIR1bits.SSPIF=0;		/* Clear SSPIF flag */
    data_flush=SSPBUF;		/* Flush the data */
}

unsigned char SPIM_Read()
{    
    SSPBUF=0xff;		/* Copy flush data in SSBUF */
    while(!PIR1bits.SSPIF);	/* Wait for complete 1 byte transmission */
    PIR1bits.SSPIF=0;
    return(SSPBUF);		/* Return received data.*/   
}

void main()
{  
    SPI_Init_Master();
    while(1)
    {   for(int i=0;i<2;i++)
    {
        PORTAbits.RA5 = 0;
        SPIM_Write('a');
        __delay_ms(1000);
        SPIM_Write('b');
         __delay_ms(1000);
        PORTAbits.RA5 = 1;
    }    
    
    }
}