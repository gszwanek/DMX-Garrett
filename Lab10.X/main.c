
#include "mcc_generated_files/mcc.h"
#include "dmx.h"
#include "Lab10Header.h"
#include "clock.h"
#include "tm1650.h"
int count = 0;
uint8_t buffer[514];  
void Blink1();
/*
                         Main application
 */
void main(void)
{
    SYSTEM_Initialize();

    DMX_init();
    CLOCK_init();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    TM1650_init();
   
    while (1)
    {
        uint8_t r = buffer[1];              //Channel 1 of DMX (red)
        uint8_t g = buffer[2];              //Channel 2 "  "   (green)
        uint8_t b = buffer[3];              //Channel 3 "  "   (blue)
        uint8_t w = buffer[4];              //Channel 4 "  "   (white)
        LED_setColor(b, w, g, r);           //Sets LED to channel values
        
        Blink1();
    }
}

 void Blink1() {
    static bool value = 0;
    static time_t lastTime = 0;
    
    time_t time = CLOCK_getTime();
    if(time <= lastTime + 237)
        return;
    
    lastTime = time;
    value = !value;
    
    if(value)
        TM1650_setDigit(0, '8', 0);
    else
        TM1650_setDigit(0, ' ', 0);
    
}