      
#include <xc.h>
#include "mcc_generated_files/eusart1.h"
extern int count = 0;
extern uint8_t buffer[514];  



void DMX_receive_handler() {
        if(RC1STAbits.OERR == 1) {
            RC1STAbits.CREN = 0;
            RC1STAbits.CREN = 1;           //Checks for overflow, resets interrupt
        } 
        uint8_t dummy = RC1REG;         //Dummy variable to read and therefore clear interrupt

        if(RC1STAbits.FERR == 1) {      //Checks for Framing error
            count = 0;
        } else { 
            buffer[count] = dummy; 
            count++;                    //Sets buffer to current value of RC1REG and increments it
        }
}

void DMX_init() {
    EUSART1_SetRxInterruptHandler(DMX_receive_handler);
}