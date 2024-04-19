#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "SW_LED.h"

//Old states of switches
/* Index legend
    0 = ctr
    1 = right
    2 = down
    3 = left
    4 = up
*/
//unsigned char oldStates[] = {0, 0, 0, 0, 0};

void SWL_Init (void) {
    PT1AD1 &= 0x1F;
    DDR1AD1 = 0xE0;
    ATD1DIEN1 |= 0x1F;
}

void SWL_ON (SWL_LEDColour led) {
    PT1AD1 |= (unsigned char)led;
}

void SWL_OFF (SWL_LEDColour led) {
    PT1AD1 &= ~(unsigned char)led;
}

void SWL_TOG (SWL_LEDColour led) {
    PT1AD1 ^= (unsigned char)led;
}

int SWL_Pushed (SWL_SwitchPos pos) {
    return PT1AD1 & pos;
}

/* int SWL_Held (SWL_SwitchPos pos) {
    int pressedButtonIndex = -1;

    switch (pos) {
        case 1:
            pressedButtonIndex = 0; 
            break;
        case 2: 
            pressedButtonIndex = 1; 
            break;
        case 4: 
            pressedButtonIndex = 2; 
            break;
        case 8: 
            pressedButtonIndex = 3; 
            break;
        case 16: 
            pressedButtonIndex = 4; 
            break;
        default:
            return 0;
    }


    if (SWL_Pushed(pos)) {                                  //logic doesnt work
        oldStates[pressedButtonIndex]++;
    }
    else if (oldStates[pressedButtonIndex] > 10) {
        return 1;
    }
    else if (!SWL_Pushed(pos)) {
        oldStates[pressedButtonIndex] = 0;
        return 0;
    }
} */