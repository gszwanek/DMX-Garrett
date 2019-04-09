/*
 * File:   Lab10main.c
 * Author: Garrett
 *
 * Created on April 4, 2019, 6:33 PM
 */



#include <xc.h>
#include <stdint.h>
#include "Lab10Header.h"
#pragma config WDTE = OFF
#define _XTAL_FREQ 4000000
uint8_t buffer[514];                    //creates array of 514, 512 + 2 for the breaks
int value = 0;                          //Global variable that points to values

void __interrupt() iocISR() {
        if(RC1STAbits.OERR == 1) {
            RC1STAbits.CREN = 0;
            RC1STAbits.CREN = 1;           //Checks for overflow, resets interrupt
        } 
        uint8_t dummy = RC1REG;         //Dummy variable to read and therefore clear interrupt

        if(RC1STAbits.FERR == 1) {      //Checks for Framing error
            value = 0;
        } else { 
            buffer[value] = dummy; 
            value++;                    //Sets buffer to current value of RC1REG and increments it
        }
        
}
void main(void) {
    LED_init();
    UART_init();
    setISR();                               //Calls initialization functions
    
    while (1) {
        uint8_t r = buffer[1];              //Channel 1 of DMX (red)
        uint8_t g = buffer[2];              //Channel 2 "  "   (green)
        uint8_t b = buffer[3];              //Channel 3 "  "   (blue)
        uint8_t w = buffer[4];              //Channel 4 "  "   (white)
        LED_setColor(b, w, g, r);           //Sets LED to channel values
    }
}

