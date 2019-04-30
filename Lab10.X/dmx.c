      
#include <xc.h>
#include "mcc_generated_files/eusart1.h"
#include "clock.h"
extern int count = 0;
extern uint8_t buffer[514];  
static bool task1;
extern bool DMX_var;

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
            task1 = true;               //variable to check  if dmx is received
        }
}

void DMX_init() {
    EUSART1_SetRxInterruptHandler(DMX_receive_handler);
}
static time_t lastTime;
void DMX_task() {
    time_t time = CLOCK_getTime();

    // only run every 10 ms
    if (time - lastTime < 1000)
        return;

    lastTime = time;
    
    if(task1 == true) {
        DMX_var = true;                 //sets second variable to true when dmx is still being received
        task1 = false;                  //sets first check of dmx to false so it can be checked again
    } else {
        DMX_var = false;                //sets second check to false if still no dmx received
    }
}