volatile union {
    unsigned char byte;
    PORTAbits_t bits;
} LATPORTA;

#define LATPORTA_FLUSH PORTA = LATPORTA.byte

volatile union {
    unsigned char byte;
    PORTBbits_t bits;
} LATPORTB;

#define LATPORTB_FLUSH PORTB = LATPORTB.byte

volatile union {
    unsigned char byte;
    PORTCbits_t bits;
} LATPORTC;

#define LATPORTC_FLUSH PORTC = LATPORTC.byte



#define TRIS_OUTPUT 0
#define TRIS_INPUT 1
#define ANS_ANALOG 1
#define ANS_DIGITAL 0
#define IR_IN1 PORTCbits.RC7;
#define IR_IN1_ANS ANSELHbits.ANS9
#define IR_IN1_TRIS TRISCbits.TRISC7
#define IR_IN1_ANALOG_CHANNEL 9
#define IR_IN2 PORTCbits.RC6;
#define IR_IN2_ANS ANSELHbits.ANS8
#define IR_IN2_TRIS TRISCbits.TRISC6
#define IR_IN2_ANALOG_CHANNEL 8

#define IR_OUTPUT_TRIS TRISCbits.TRISC5
#define IR_OUTPUT LATPORTC.bits.RC5
#define IR_OUTPUT_ON  1
#define IR_OUTPUT_FLUSH LATPORTC_FLUSH

#define LED_SIGNAL_TRIS TRISBbits.TRISB6
#define LED_SIGNAL LATPORTB.bits.RB6
#define LED_SIGNAL_ON  1
#define LED_SIGNAL_OFF !LED_SIGNAL_ON
#define LED_SIGNAL_FLUSH LATPORTB_FLUSH

#define use_IR_IN1 0
#define use_IR_IN2 1






/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
