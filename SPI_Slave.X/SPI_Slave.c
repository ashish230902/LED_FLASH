/* File:   LED_FLASH.c
 * Author: Ashish Sharma
 *
 * Created on 11 January, 2021, 3:45 PM
 */


#include "configure.h"

#define _XTAL_FREQ 8000000//8Mhz 

#include <xc.h>

void SPI_Init_Slave()
{
    /* PORT definition for SPI pins*/    
    TRISBbits.TRISB5 = 1;	/* RB0 as input(SDI) */
    TRISBbits.TRISB4 = 1;	/* RB1 as input(SCK) */
    TRISAbits.TRISA5 = 1;	/* RA5 as a input(SS') */
    TRISCbits.TRISC7 = 0;	/* RC7 as output(SDO) */
    TRISBbits.TRISB0 = 0;

    /* To initialize SPI Communication configure following Register*/
    
    SSPSTAT=0x40;		/* Data change on rising edge of clk , BF=0*/
    SSPCON1=0b00110100;		/* Slave mode,Serial enable, idle state 
				high for clk */ 
    PIR1bits.SSPIF=0;

    /* Disable the ADC channel which are on for multiplexed pin 
    when used as an input */    
    ADCON0=0;			/* This is for de-multiplexed the SCL
				and SDI from analog pins*/
    ADCON1=0x0F;		/* This makes all pins as digital I/O */    
}

void SPIS_Write(unsigned char x)
{
    unsigned char data_flush;
    SSPBUF=x;			/* Copy data in SSBUF to transmit */
    while(!PIR1bits.SSPIF);	/* Wait for complete 1 byte transmission */
    PIR1bits.SSPIF=0;		/* Clear SSPIF flag */
    data_flush=SSPBUF;		/* Flush the data */
}

unsigned char SPIS_Read()
{    
    SSPBUF=0xff;		/* Copy flush byte in SSBUF */
    while(!PIR1bits.SSPIF);	/* Wait for complete 1 byte transmission */
    PIR1bits.SSPIF=0;
    return(SSPBUF);		/* Return received byte */   
}

void main()
{  unsigned char x;
    SPI_Init_Slave();
    for(int i=0;i<2;i++)
    {
        PORTBbits.RB0=1;
        __delay_ms(1000);
        PORTBbits.RB0=0;
        __delay_ms(1000);
    }
    while(1)
    {
        
        x = SPIS_Read();
        if(x =='a')
        {
            PORTBbits.RB0=1;           
        }
        else if(x=='b')
        {
            PORTBbits.RB0=0;
        }
        
       
    
    }
}