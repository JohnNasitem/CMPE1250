#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "misc.h"
#include <stdlib.h>
#include <stdio.h>

int GetRandom (int iLow, int iHighEx) {
    //Returns a random value inclusively between iLow and iHighEx - 1
    return (rand() % (iHighEx - iLow)) + iLow;
}

/* void SendString (char const * stringAdress, ColorEscapeValues forecolor, ColorEscapeValues backcolor, int xPos, int yPos) {
    char buffer[1024];
    
    //Set locaton
    if (!(xPos == -1 && yPos == -1)) {
        snprintf(buffer, sizeof(buffer), "\x1b[%d;%dH", xPos, yPos);
        sci0_txStr(buffer);
    }

    //sets the foreground clour
    if (forecolor != CEV_Default) {
        snprintf(buffer, sizeof(buffer), "\x1b[%dm", forecolor);
        sci0_txStr(buffer);
    }

    if (backcolor != CEV_Default) {
        snprintf(buffer, sizeof(buffer), "\x1b[%dm", forecolor + 10);
        sci0_txStr(buffer);
    }

    sci0_txStr(stringAdress);
} */