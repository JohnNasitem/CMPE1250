#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "clock.h"

unsigned long busSpeed = DEF_BUS_CLOCK;

void Clock_EnableOutput(ClockOutDiv busSpeedType) {
    if (busSpeedType == ClockOutDiv1)  Clock_Set8MHZ();
    else if (busSpeedType == ClockOutDiv2)  Clock_Set20MHZ();
    else if (busSpeedType == ClockOutDiv3)  Clock_Set24MHZ();
    else if (busSpeedType == ClockOutDiv4)  Clock_Set40MHZ();

    CLKSEL_PSTP = 1;
    PLLCTL = 0b11111111;
    while (!CRGFLG_LOCK);
    CLKSEL_PLLSEL = 1;
}

void Clock_Set8MHZ(void) {
    SYNR = 0;
    REFDV = 3;
    busSpeed = DEF_BUS_CLOCK;
}

void Clock_Set20MHZ(void) {
    SYNR = 4;
    REFDV = 3;
    busSpeed = 20000000;
}

void Clock_Set24MHZ(void) {
    SYNR = 1;
    REFDV = 2;
    busSpeed = 24000000;
}

void Clock_Set40MHZ(void) {
    SYNR = 4;
    REFDV = 1;
    busSpeed = 40000000;
}

unsigned long Clock_GetBusSpeed(void) {
    return busSpeed;
}
