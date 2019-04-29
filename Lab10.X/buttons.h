

#ifndef BUTTONS_H
#define BUTTONS_H
#include <xc.h>
#include <stdint.h>
#include "clock.h"
#include <stdbool.h>
typedef enum {
    EVENT_IDLE,
    EVENT_PRESSED,
    EVENT_HELD
} event_t;

typedef enum {
    STATE_UNPRESSED,
    STATE_PRESSED
} btnState_t;

typedef struct {
    volatile uint8_t* port;
    uint8_t pin;
    btnState_t state;
    btnState_t lastState;
    event_t event;
    btnState_t hold;
} button_t;

void BUTTONS_task();
void BUTTONS_init();
bool BUTTONS_isClicked(button_t* button);
bool BUTTONS_isHeld(button_t* button);
//bool BUTTONS_notPressed(button_t * button);
extern button_t *up, *down, *enter, *menu;
#endif