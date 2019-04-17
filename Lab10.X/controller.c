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
#include <stdio.h>

static time_t lastTime = 0;

uint16_t address = 1;

void CONTROLLER_init() {
    TM1650_fastPrintNum(address);
}

/**
 * Increments the address and updates the display
 */
void address_inc() {
    if (address == 512)
        address = 1;
    else
        address++;

    // update the display
    TM1650_fastPrintNum(address);
}

/**
 * Decrements the address and updates the display
 */
void address_dec() {
    if (address == 1)
        address = 512;
    else
        address--;

    // update the display
    TM1650_fastPrintNum(address);
}

void CONTROLLER_task() {

    time_t time = CLOCK_getTime();

    // only run every 10 ms
    if (time - lastTime < 125)
        return;

    lastTime = time;

    if (BUTTONS_isClicked(up)) {
        address_inc();

    } else if (BUTTONS_isClicked(down)) {
        address_dec();
    }
    if (BUTTONS_isHeld(up)) {
        address_inc();

    } else if (BUTTONS_isHeld(down)) {
        address_dec();
    }
}