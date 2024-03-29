#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "misc.h"
#include <stdlib.h>
#include <stdio.h>

int GetRandom (int iLow, int iHighEx) {
    //Returns a random value inclusively between iLow and iHighEx - 1
    return (rand() % (iHighEx - iLow)) + iLow;
}

void SendString (char const * stringAdress, ColorEscapeValues forecolor, ColorEscapeValues backcolor, int row, int column) {
    char buffer[1024];
    
    //Set locaton
    if (!(row == -1 && column == -1)) {
        sprintf(buffer, "\x1b[%d;%dH", row, column);
        sci0_txStr(buffer);
    }

    //sets the foreground clour
    if (forecolor != CEV_Default) {
        sprintf(buffer, "\x1b[%dm", forecolor);
        sci0_txStr(buffer);
    }

    if (backcolor != CEV_Default) {
        sprintf(buffer, "\x1b[%dm", backcolor + 10);
        sci0_txStr(buffer);
    }

    sci0_txStr(stringAdress);
}