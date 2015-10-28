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





#define durationLogic1  1675  //sum 2232  //us
#define durationLogic0  562   //sum 1125  //us
#define durationBeacon 9000  //us
#define durationSpace  4500  //us
#define durationSpaceRepeat  2250  //us
#define durationRepeat 11174  //us

// USERS SUB


void sendByteEUSART(unsigned char byte, bool sync) {

    TXREG = byte;
    if (sync) while (!TXSTAbits.TRMT); //WAIT Trasmition finish

}

void send2BytesEUSART(unsigned char byte1, unsigned char byte2, bool sync) {

    TXREG = byte1;
    NOP();
    TXREG = byte2;
    if (sync) while (!TXSTAbits.TRMT); //WAIT Trasmition finish

}

void sendIRbit(bool b) {
    enablePWMoutput;
    __delay_us(durationLogic0);
    disablePWMoutput;
    if (b) {
        __delay_us(durationLogic1);
    } else {
        __delay_us(durationLogic0);
    }
}



void sendIRByte(unsigned char c) {
    for (int j = 0; j < 8; j++) {
        sendIRbit(c & 0x80);
        c <<= 1;
        LED_SIGNAL = !IR_IN2;
        LED_SIGNAL_FLUSH;
    }
}

void sendIRServiceBit(bool type) {
    //type 0-prefix, 1-suffix
    enablePWMoutput;
    if (type) {
        __delay_us(durationLogic0);
        disablePWMoutput;
        __delay_ms(40); // wait for the Data Frame time. 
    } else {
        __delay_us(durationBeacon); // leading PULSE
        disablePWMoutput;
        __delay_us(durationSpace); // space
    }
}

void sendFrame(unsigned char address, unsigned char command) {
        sendIRServiceBit(0);
        sendIRByte(address);
        sendIRByte(~address);
        sendIRByte(command);
        sendIRByte(~command);
        sendIRServiceBit(1);
}

void sendRepeate()
{
    enablePWMoutput;
	__delay_us(durationBeacon);				//wait for ~9ms 	
	disablePWMoutput;
	__delay_us(durationSpaceRepeat);	    //wait for 2.25ms

    enablePWMoutput;
	__delay_us(durationLogic0);				//wait for ~562.5us
    disablePWMoutput;
	__delay_us(96187);				//delay for 96.187 ms before sending the next repeate code
	
}


//----------------------------------------------------

void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    uint16_t result;
    uint8_t IrTry;
    //IR LED - ON
    IR_OUTPUT = IR_OUTPUT_OFF;
    IR_OUTPUT_FLUSH;

    IrTry = IR_TRY;

//    unsigned char *command;
//    command[0] = 0x8D; // addres
//    command[1] = 0xB1; // command


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

        sendFrame(0x8D,0xB1);
        __delay_ms(5000);

#endif        

    }

}

