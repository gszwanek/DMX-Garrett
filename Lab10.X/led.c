/*
 * File:   led.c
 * Author: Garrett
 *
 * Created on April 29, 2019, 2:28 PM
 */


#include <xc.h>
#include <stdint.h>
#include "clock.h"
#include "buttons.h"
#include "controller.h"
#include "beat.h"
#include "dmx.h"
#include "Lab10Header.h"

static time_t lastTime;
static int state = 0;

void soundTask() {

    if (CLOCK_getTime() - lastTime < 100)
        return;

    lastTime = CLOCK_getTime();
    //    LED_setColor(0, 0, 0, 0);

    if (BEAT_detected()) {
            switch (state) {
                case 0:
                    LED_setColor(0, 0, 0, 0);
                    break;
                case 1:
                    LED_setColor(255, 0, 0, 0);
                    break;
                case 2:
                    LED_setColor(0, 0, 255, 0);
                    break;
                case 3:
                    LED_setColor(255, 155, 0, 0);
                    break;
                case 4:
                    LED_setColor(0, 255, 0, 0);
                    break;
                case 5:
                    LED_setColor(0, 0, 0, 255);
                    break;
                case 6:
                    LED_setColor(120, 120, 120, 10);
                    break;                                          //Switches between colors for each next beat
            }
            state++;
            if(state==7) {
                state = 1;                              //Resets state to 0
            }
    }
}
