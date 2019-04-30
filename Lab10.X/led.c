/*
 * File:   led.c
 * Author: Garrett
 *
 * Created on April 29, 2019, 2:28 PM
 */


#include <xc.h>
#include <math.h>
#include <stdint.h>
#include "clock.h"
#include "buttons.h"
#include "controller.h"
#include "beat.h"
#include "dmx.h"
#include "Lab10Header.h"

static time_t lastTime;
static int state = 0;
static int random = 0;

void lightShow1() {
    if (BEAT_detected()) {
        state = 1;
    }
    switch (state) {
        case 0:
            LED_setColor(0, 0, 0, 0);
            break;
        case 1:
            LED_setColor(255, 0, 0, 0);
            state = 2;
            break;
        case 2:
            LED_setColor(0, 0, 255, 0);
            state = 3;
            break;
        case 3:
            LED_setColor(0, 255, 0, 0);
            state = 0;
            break; //Switches between colors for each next beat
    }
}

void lightShow2() {
    if (BEAT_detected()) {
        state = 1;
    }
    switch (state) {
        case 0:
            LED_setColor(0, 0, 0, 0);
            break;
        case 1:
            LED_setColor(55, 0, 217, 0);
            state = 2;
            break;
        case 2:
            LED_setColor(0, 103, 55, 0);
            state = 3;
            break;
        case 3:
            LED_setColor(20, 255, 54, 24);
            state = 0;
            break; //Switches between colors for each next beat
    }
}

void lightShow3() {
    if (BEAT_detected()) {
        state = 1;
    }
    switch (state) {
        case 0:
            LED_setColor(0, 0, 0, 0);
            break;
        case 1:
            LED_setColor(20, 0, 117, 10);
            state = 2;
            break;
        case 2:
            LED_setColor(0, 3, 255, 0);
            state = 3;
            break;
        case 3:
            LED_setColor(200, 0, 54, 0);
            state = 0;
            break; //Switches between colors for each next beat
    }
}
void lightShow4() {
    if (BEAT_detected()) {
        state = 1;
    }
    switch (state) {
        case 0:
            LED_setColor(0, 0, 0, 0);
            break;
        case 1:
            LED_setColor(0, 0, 0, 255);
            state = 2;
            break;
        case 2:
            LED_setColor(255, 0, 0, 0);
            state = 3;
            break;
        case 3:
            LED_setColor(0, 0, 0, 255);
            state = 0;
            break; //Switches between colors for each next beat
    }
}
void soundTask() {

    if (CLOCK_getTime() - lastTime < 100)
        return;

    lastTime = CLOCK_getTime();

    int random = rand();
    random = random % 4;
            
    if(random == 0) {
        lightShow1();
    } else if (random == 1) {
        lightShow2();
    } else if (random == 2) {
        lightShow3();                           //randomizes series of lightshows
    } else {
        lightShow4();
    }
}
