/*
 * File:   controller.c
 * Author: Garrett
 *
 * Created on April 16, 2019, 4:17 PM
 */


#include "controller.h"
#include "buttons.h"
#include "clock.h"
#include "tm1650.h"
#include "beat.h"
#include "led.h"
#include <stdio.h>
#include <xc.h>

extern int count = 1;

static time_t lastTime = 0;
static time_t lastActiveTime;

//extern static bool wasActive;

uint16_t address = 1;

void CONTROLLER_init() {
    TM1650_fastPrintNum(count);
}

/**
 * Increments the address and updates the display
 */
void address_inc() {
    if (count == 512)
        count = 1;
    else
        count++;

    // update the display
    TM1650_fastPrintNum(count);
}

/**
 * Decrements the address and updates the display
 */
void address_dec() {
    if (count == 1)
        count = 512;
    else
        count--;

    // update the display
    TM1650_fastPrintNum(count);
}



void CONTROLLER_task() {

    time_t time = CLOCK_getTime();

    // only run every 10 ms
    if (time - lastTime < 140)
        return;

    lastTime = time;
    bool active = true;
    
    if (BUTTONS_isClicked(up)) {
        address_inc();

    } else if (BUTTONS_isClicked(down)) {
        address_dec();
    }
    else if (BUTTONS_isHeld(up)) {
        address_inc();

    } else if (BUTTONS_isHeld(down)) {
        address_dec();
    } else {
        active = false;
    }

    //add

    if(active)
    {
        TM1650_enable(true);
        lastActiveTime = CLOCK_getTime();
    }
    if(CLOCK_getTime() - lastActiveTime >= 5000)
    {
        TM1650_enable(false);
        lastActiveTime = CLOCK_getTime() - 5001;
    }
       
    //end
}

