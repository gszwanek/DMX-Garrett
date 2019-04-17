/*
 * File:   Lab10Functions.c
 * Author: Garrett
 *
 * Created on April 7, 2019, 1:19 PM
 */


#include <xc.h>
#include <stdint.h>
#include "Lab10Header.h"
#pragma config WDTE = OFF
#define _XTAL_FREQ 4000000
extern int count;

void LED_init() {
    T2CLKCON = 0x01;
    T2CONbits.ON = 1;       //Sets up Timer 2

    CCP1CONbits.CCP1EN = 1;
    CCP1CONbits.MODE = 0b1100;     //CCP1

    RC3PPS = 0x09;   //Routes to RC3, BLUE
    TRISC3 = 0; 
    
    CCP2CONbits.CCP2EN = 1;
    CCP2CONbits.MODE = 0b1100;     //CCP2

    RC4PPS = 0x0A;   //Routes to RC4,  WHITE
    TRISC4 = 0; 
    
    CCP3CONbits.CCP3EN = 1;
    CCP3CONbits.MODE = 0b1100;     //CCP3

    RC6PPS = 0x0B;   //Routes to RC6,  GREEN
    TRISC6 = 0;
    
    CCP4CONbits.CCP4EN = 1;
    CCP4CONbits.MODE = 0b1100;     //CCP4

    RC7PPS = 0x0C;   //Routes to RC7,    RED
    TRISC7 = 0;
}
void LED_setColor (uint8_t x, uint8_t y, uint8_t z, uint8_t w) {
   CCPR1H = 0;        
   CCPR1L = x >> 1;       
   CCPR2H = 0;        
   CCPR2L = y >> 1;
   CCPR3H = 0;        
   CCPR3L = z >> 1;
   CCPR4H = 0;        
   CCPR4L = w >> 1;             //Creates a 12.5% duty cycle for the PWM for each color, RGBW
}
void UART_init() {
    RX1PPS = 0b01100;       //routes RX1 PPS to RB4, Rx Pin
    
    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUD1CON = 0x00;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RC1STA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN disabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TX1STA = 0x04;

    // SP1BRGL 0; 
    SP1BRG = 0x00;
}
void setISR() {
    ANSELB = 0;
    TRISC = 1;
    INTCONbits.PEIE = 1;  //enable peripheral interrupts
    INTCONbits.GIE = 1; // enable global interrupts
    PIE3bits.RC1IE = 1;  // enable RC1 interrupts
}
