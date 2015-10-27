/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
#define IR_LIMIT1 1010
#define IR_LIMIT2 20
#define IR_TRY   100

void sendByteEUSART(unsigned char byte){
    
    TXREG=byte;
    while(!TXSTAbits.TRMT); //WAIT Trasmition finish
    
}

void send2BytesEUSART(unsigned char byte1,unsigned char byte2){
    
    TXREG=byte1;
    NOP();
    TXREG=byte2;
    while(!TXSTAbits.TRMT); //WAIT Trasmition finish
    
}

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    uint16_t result;
    uint8_t IrTry;
    //IR LED - ON
    IR_OUTPUT = IR_OUTPUT_ON;
    IR_OUTPUT_FLUSH;

    IrTry=IR_TRY;
            
    while(1)
    {
#if (use_IR_IN1)
        //Read analog value 
        __delay_ms(5);
        ADCON0bits.GO_nDONE=1;
        while(ADCON0bits.GO_nDONE);
        result=ADRESH<<8|ADRESL;
        if (result<=IR_LIMIT1 && result>=IR_LIMIT2) {
           if (IrTry>0) IrTry--;
        }else{
           IrTry=IR_TRY;
        }
        LED_SIGNAL = (IrTry==0) ? LED_SIGNAL_ON : LED_SIGNAL_OFF;
        LED_SIGNAL_FLUSH;
        //Send DWORD to UART
        //sendByteEUSART(IrTry==0);
        send2BytesEUSART(ADRESH,ADRESL);
        //sendByteEUSART(ADRESH);
        //sendByteEUSART(ADRESL);
#endif
#if (use_IR_IN2)
     __delay_ms(5);
     LED_SIGNAL=!IR_IN2;
     LED_SIGNAL_FLUSH;
        
#endif        
        
    }

}

