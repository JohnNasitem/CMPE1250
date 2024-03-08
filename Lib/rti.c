#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "rti.h"

void RTI_Init(void) {
    CRGINT |= CRGINT_RTIE_MASK; //0b10000000, Enable RTI
}

void RTI_Delay_ms(unsigned int ms) {
    unsigned int counter;

    //Checks if ms is 0 and returns immediately
    if (ms == 0) return;

    //Stops RTI
    RTICTL = 0;

    //Checks if RTIF flag is set, and clears it if it is
    if (CRGFLG_RTIF) CRGFLG = CRGFLG_RTIF_MASK; 

    //Enables RTI with 1ms period
    RTICTL = 0b10001111;

    //Loops the 1ms period for ms times
    for (counter = 0; counter < ms; counter++) {
        //Checks if RTI period is over
        while (!CRGFLG_RTIF) {}
        //Clears flag
        CRGFLG = CRGFLG_RTIF_MASK;
    }

    //Stops the RTI
    RTICTL = 0;
}