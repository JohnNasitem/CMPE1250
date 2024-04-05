#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "segs.h"

void Segs_Init (void) (
    // ensure port pins are high
    PORTA |= 0x03;

    // set port pins as outputs
    DDRA |= 0x03;
    DDRB = 0xFF;
)