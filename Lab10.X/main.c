
#include "mcc_generated_files/mcc.h"
#include "dmx.h"
#include "Lab10Header.h"
#include "clock.h"
#include "tm1650.h"
#include "buttons.h"
#include "controller.h"
#include "beat.h"
#include "led.h"
int count = 0;
uint8_t buffer[514];
bool DMX_var;

/*
                         Main application
 */
void main(void) {
    SYSTEM_Initialize();

    DMX_init();
    CLOCK_init();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    __delay_ms(500);

    TM1650_init();
    BUTTONS_init();
    CONTROLLER_init();
    BEAT_init();                //Initializes everything
    TRISCbits.TRISC5 = 0;
    while (1) {
        BUTTONS_task();
        CONTROLLER_task();
        BEAT_task();
        DMX_task();                 //Calls tasks for dmx, beat, buttons, etc.

        if (DMX_var == true) {
            uint8_t r = buffer[1]; //Channel 1 of DMX (red)
            uint8_t g = buffer[2]; //Channel 2 "  "   (green)
            uint8_t b = buffer[3]; //Channel 3 "  "   (blue)
            uint8_t w = buffer[4]; //Channel 4 "  "   (white)
            LED_setColor(b, w, g, r); //Sets LED to channel values
        } else {
            soundTask();                                                        //If dmx being received, outputs channel values
        }                                                                       //If no dmx, turn on sound and beat detection
    }
}
