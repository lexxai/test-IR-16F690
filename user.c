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
    
    //IR_IN1
    IR_IN1_TRIS = TRIS_INPUT;
    IR_IN1_ANS = ANS_ANALOG;
    //ADC INIT    
    //CONVERSION CLOCK
    ADCON1bits.ADCS=0b001; // FOSC/8. 4 MHz=2.0 ?s
    //ADC VOLTAGE REFERENCE
    ADCON0bits.VCFG=0; //0-VDD, 1 = VREF pin
    //A/D Conversion Result Format Select bit
    ADCON0bits.ADFM=1; //Right justified
    //Analog Channel Select bits
    ADCON0bits.CHS=IR_IN1_ANALOG_CHANNEL;
    //ADC Enable
#if (use_IR_IN1)
    ADCON0bits.ADON=1; // enabled now
#else
    ADCON0bits.ADON=0; // disabled now
#endif    
    
    //IR_IN2
    IR_IN2_TRIS = TRIS_INPUT;
    IR_IN2_ANS = ANS_DIGITAL;
    
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
    
    
    //GENERATOR 38 kHz
    //Fos=4MHz, F=38000Hz, 26.31578 us
    //For Timer increment to overflow
    //TIMER0  = 230 (0xE6) //26us(+1.2%)) 38461.53846 kHz
    //TIMER1H = 0xFF;      //26us(+1.2%))
    //TIMER1L = 0xE6;      //26us(+1.2%))
    //For Timer increment from 0000 (Compare mode PWM)
    //CCPR1H = 0x00;      //26us(+1.2%))
    //CCPR1L = 26;        //26us(+1.2%))
    
 
#if (use_IR_IN2)
    //use PWM module - Compare Mode
    //use Timer1
    T1CONbits.nT1SYNC=1;   //non Async mode
    T1CONbits.TMR1CS=0;    //Source Fosc/4
    T1CONbits.T1CKPS=0b00; //Prescaler 00-1
    TMR1=0x0000;
    
    //Compare Mode of PWM
    CCP1CONbits.CCP1M=0b1011;   //Compare MODE, triger event reset TMR1
    //CCP1CONbits.CCP1M=0b0010;   //Compare MODE, toggle output pin, interrupt
    
    
    CCPR1H = 0x00;         //26us
    CCPR1L = 26/2;          //13 = 1/2 period
    
    PIE1bits.CCP1IE=1;     //enable capture inetrupt
    PIR1bits.CCP1IF=0;     //reset capture inetrupt flag
 
    INTCONbits.PEIE=1;     //enable periph interrupt
    INTCONbits.GIE=1;      //enable global interrupt

    T1CONbits.TMR1ON=1;    //Enable Timer1
    
#endif
    
 
    /* Enable interrupts */
}

