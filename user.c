/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
//    LATPORTA=0;
//    LATPORTB=0;
//    LATPORTC=0;

    /* Setup analog functionality and port direction */
    /* Initialize peripherals */
    
    //ADC INIT
    IR_IN_TRIS = TRIS_INPUT;
    IR_IN_ANS = ANS_ANALOG;
    //CONVERSION CLOCK
    ADCON1bits.ADCS=0b001; // FOSC/8. 4 MHz=2.0 ?s
    //ADC VOLTAGE REFERENCE
    ADCON0bits.VCFG=0; //0-VDD, 1 = VREF pin
    //A/D Conversion Result Format Select bit
    ADCON0bits.ADFM=1; //Right justified
    //Analog Channel Select bits
    ADCON0bits.CHS=IR_IN_ANALOG_CHANNEL;
    //ADC Enable
    ADCON0bits.ADON=1;
    
    
    //IR_OUTPUT
    IR_OUTPUT_TRIS = TRIS_OUTPUT;
    IR_OUTPUT = !IR_OUTPUT_ON;
    IR_OUTPUT_FLUSH;
    
    //LED SIGNAL
    LED_SIGNAL_TRIS = TRIS_OUTPUT;
    LED_SIGNAL = LED_SIGNAL_OFF;
    LED_SIGNAL_FLUSH;
    
    //EUSART CONFIG
    #define speed 16   //decimal 103 = 9600 bod, 16=57600 (4Mhz)
    SPBRGH=speed>>8;      
    SPBRG= speed & 0xFF ; 
    TXSTAbits.BRGH=1;    //16-bit/Asynchronous  FOSC/4     
    BAUDCTLbits.BRG16=1; //16-bit/Asynchronous  FOSC/4     
    //transmitter for asynchronous            
    TXSTAbits.SYNC=0; //Clearing the SYNC bit of the TXSTA register configures the EUSART for asynchronous operation.
    RCSTAbits.SPEN=1; //Setting the SPEN bit of the RCSTA register enables the EUSART and automatically configures the TX/CK I/O pin as an output.
    TXSTAbits.TXEN=1; //enables the transmitter circuitry of the EUSART
 
    /* Enable interrupts */
}

