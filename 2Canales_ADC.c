
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config IESO = ON
#pragma config FCMEN = ON
#pragma config LVP = ON

#pragma config BOR4V = BOR40V
#pragma config WRT = OFF


#include <xc.h>
unsigned int counter = 0;
unsigned int adc[3]= {0};

void main(void) {
    unsigned int i=0;
    OSCCON = 0xFF;
    TRISA = 0b00000111;
    ANSEL = 0b00000111;
    ANSELH = 0x00;
    PORTA = 0x00;
    
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0x00;
    
    TMR0 = 0x07;
    TMR0IF = 0;
    ADCON0bits.ADCS = 0b010;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    ADCON1bits.ADFM = 0x01;
    ADCON0bits.ADON = 0x01;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.T0IE = 1;
    
    while(1){
        for(i=0;i<3;i++){
            ADCON0bits.CHS = i;
            if (counter == 10){
                counter = 0;
                ADCON0bits.GO = 1;
                while(!ADCON0bits.nDONE){
                    continue;
                }
                adc[i] = ADRESL + (ADRESH <<8);
            }
    }
    }
    return;
}
void __interrupt() isr(void){
    if (TMR0IE && TMR0IF){
        TMR0IF=0;
        TMR0 = 0x07;
        counter++;
        }
    return;
    
}
