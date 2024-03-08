#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "rti.h"

void RTI_Init(void) {
    //Set RTIE to 1, allows RTIF to cause an interrupt request
    CRGINT |= CRGINT_RTIE_MASK; //0b10000000, Enable RTI
}

void RTI_Delay_ms(unsigned int ms) {
    unsigned int counter;                           //counter used to loop ms times

    //Checks if ms is 0 and returns immediately
    if (ms == 0) return;

    //Stops RTI
    RTICTL = 0;

    //Checks if RTIF flag is set
    if (CRGFLG_RTIF) CRGFLG = CRGFLG_RTIF_MASK; // Sets CRGFLG to 0b10000000, clearing it

    //Enables RTI with 1ms period
    RTICTL = 0b10001111;

    //Loops the 1ms period for ms times
    for (counter = 0; counter < ms; counter++) {
        //Checks if RTI period is over
        while (!CRGFLG_RTIF);
        //Clears flag
        CRGFLG = CRGFLG_RTIF_MASK;
    }

    //Stops the RTI
    RTICTL = 0;
}