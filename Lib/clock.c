#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "clock.h"

unsigned long busSpeed = DEF_BUS_CLOCK;

void Clock_EnableOutput(ClockOutDiv) {
    PLLCTL |= 0b01100000;

    if (ClockOutDiv == ClockOutDiv1)  Clock_Set8MHZ();
    else if (ClockOutDiv == ClockOutDiv2)  Clock_Set20MHZ();
    else if (ClockOutDiv == ClockOutDiv3)  Clock_Set24MHZ();
    else if (ClockOutDiv == ClockOutDiv4)  Clock_Set40MHZ();
}

void Clock_Set8MHZ(void) {
    SYNR = 0;
    REFDV = 3;
    busSpeed = DEF_BUS_CLOCK;
}

void Clock_Set20MHZ(void) {
    SYNR = 4;
    REFDV = 7;
    busSpeed = 20000;
}

void Clock_Set24MHZ(void) {
    SYNR = 2;
    REFDV = 3;
    busSpeed = 24000;
}

void Clock_Set40MHZ(void) {
    SYNR = 4;
    REFDV = 3;
    busSpeed = 40000;
}

unsigned long Clock_GetBusSpeed(void) {
    return busSpeed;
}