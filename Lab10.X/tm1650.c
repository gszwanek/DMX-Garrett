/*
 * File:   tm1650.c
 * Author: Garrett
 *
 * Created on April 16, 2019, 2:04 PM
 */


#include <xc.h>
#include <stdlib.h>
#include <stdint.h>
#include "i2c.h"
#include "tm1650.h"
#define _XTAL_FREQ 4000000
static int variable;



const uint8_t charTable[] = 
{
    0x00, 0x82, 0x21, 0x00, 0x00, 0x00, 0x00, 0x02, 0x39, 0x0F, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00,
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7f, 0x6f, 0x00, 0x00, 0x00, 0x48, 0x00, 0x53,
    0x00, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x6F, 0x76, 0x06, 0x1E, 0x00, 0x38, 0x00, 0x54, 0x3F,
    0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x00, 0x0F, 0x00, 0x08, 
    0x63, 0x5F, 0x7C, 0x58, 0x5E, 0x7B, 0x71, 0x6F, 0x74, 0x02, 0x1E, 0x00, 0x06, 0x00, 0x54, 0x5C,
    0x73, 0x67, 0x50, 0x6D, 0x78, 0x1C, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x30, 0x0F, 0x00, 0x00 
};
static void writeData(uint8_t address, uint8_t data) {
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;
    I2C1_MasterWrite(&data, 1, address, &status);               //writes to address and data with status
    while(status == I2C1_MESSAGE_PENDING);                     //waits for i2c to complete
}
void TM1650_init(void){
//       tm1650_config_t config;
//config.dispType = 1;
//config.on = 1;
//writeData(0x24, config.value);
    writeData(0x24, 1);                         //Initializes tm1650 by writing 1 to start address
    TM1650_setDigit(0, 32, 0);
    TM1650_setDigit(1, 32, 0);
    TM1650_setDigit(2, 32, 0);
    TM1650_setDigit(3, 32, 0);                  //Clears led so anything saved will reset
}
void TM1650_setDigit(uint8_t digit, char data, int dp) {
    
    if(dp == 1) {
        uint8_t letter = 0b10000000 + charTable[data - 32];
        writeData( (digit + 0x34) , letter);                    //Writes data and includes decimal point if selected
       // break;
    } else if(dp == 0) {
        uint8_t letter = charTable[data - 32];
        writeData( (digit + 0x34) , letter);                    //Writes data if no decimal point selected
    }
}
void putch(char hold) {
      if(hold == '\r') {
        variable = 0;
//        __delay_ms(20);                                       //Resets to the first led if it encounters a \r
    } else {
        TM1650_setDigit(variable, hold, 0);                        //Sets digit for character thats in printf statement
        variable++; 
        if(variable == 4) {
            variable = 0;
            __delay_ms(20);                                     //resets led if more than 4 characters are in printf
        }
    }
}
void clearBar(void) {
    TM1650_setDigit(0, 32, 0);
    TM1650_setDigit(1, 32, 0);
    TM1650_setDigit(2, 32, 0);
    TM1650_setDigit(3, 32, 0);                                  //clears led and turns all of them off
}