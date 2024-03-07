#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "rti.h"

void RTI_Init(void) {
    CRGINT |= CRGINT_RTIE_MASK; //0b10000000, Enable RTI
}

void RTI_Delay_ms(unsigned int ms) {
    if (ms == 1 || ms == 2 || ms == 5 || ms == 10 || ms == 20 || ms == 50 || ms == 100 || ms == 200 || ) {
        RTICTL |= 0b10001111; //Set RTDEC to Decimal prescale with a modulus of 16
        RTICTL |= ms << 4; //Set the prescale to to the number of ms, because with a modulus of 16 the ms can represent the prescale
    }//Add an error if the ms isnt one of the set values

    // hz = 16000000 / (ms * counter), counter being 1-16
}