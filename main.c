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

void sendByteEUSART(unsigned char byte) {

    TXREG = byte;
    while (!TXSTAbits.TRMT); //WAIT Trasmition finish

}

void send2BytesEUSART(unsigned char byte1, unsigned char byte2) {

    TXREG = byte1;
    NOP();
    TXREG = byte2;
    while (!TXSTAbits.TRMT); //WAIT Trasmition finish

}

#define enablePWMoutput  IR_OUTPUT_TRIS = TRIS_OUTPUT // Enable PWM pin (CCP1) 
#define disablePWMoutput IR_OUTPUT_TRIS = TRIS_INPUT  // Disable PWM pin (CCP1) 

#define durationLogic1 2232  //us
#define durationLogic0 1120  //us
#define durationBeacon 13409  //us
#define durationRepeat 11174  //us

void sendIRbit(bool b) {
    enablePWMoutput;
    if (b) {
        __delay_us(durationLogic1);
    } else {
        __delay_us(durationLogic0);
    }
    disablePWMoutput;
    __delay_us(durationLogic0);
}

void sendIRByte(unsigned char c) {
    for (int j = 0; j < 8; j++) {
        sendIRbit(c & 1);
        c >> 1;
        LED_SIGNAL=!IR_IN2;
        LED_SIGNAL_FLUSH;
    }
}

void sendIRServiceBit(bool type) {
    //type 0-prefix, 1-suffix
    enablePWMoutput;
    if (type) {
        __delay_us(durationRepeat);
    } else {
        __delay_us(durationBeacon);
    }
    disablePWMoutput;
    __delay_us(durationLogic0);
}

void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    uint16_t result;
    uint8_t IrTry;
    //IR LED - ON
    IR_OUTPUT = IR_OUTPUT_ON;
    IR_OUTPUT_FLUSH;

    IrTry = IR_TRY;

    unsigned char *command;
    command[0] = 0x34;
    command[1] = 0x43;
    command[2] = 0x54;
    command[3] = 0x94;


    while (1) {
#if (use_IR_IN2_PWM_COMPARE)
        //Read analog value 
        __delay_ms(5);
        ADCON0bits.GO_nDONE = 1;
        while (ADCON0bits.GO_nDONE);
        result = ADRESH << 8 | ADRESL;
        if (result <= IR_LIMIT1 && result >= IR_LIMIT2) {
            if (IrTry > 0) IrTry--;
        } else {
            IrTry = IR_TRY;
        }
        LED_SIGNAL = (IrTry == 0) ? LED_SIGNAL_ON : LED_SIGNAL_OFF;
        LED_SIGNAL_FLUSH;
        //Send DWORD to UART
        //sendByteEUSART(IrTry==0);
        send2BytesEUSART(ADRESH, ADRESL);
        //sendByteEUSART(ADRESH);
        //sendByteEUSART(ADRESL);
#endif
#if (use_IR_IN2_PWM)

        sendIRServiceBit(0);
        for (int i = 0; i < 4; i++) {
            sendIRByte(command[i]);
        }
        sendIRServiceBit(1);
        
        __delay_ms(1000);


#endif        

    }

}

