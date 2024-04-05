#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "misc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Gets a random number between low, including low and high but not including high
int GetRandom (int iLow, int iHighEx) {
    //Returns a random value inclusively between iLow and iHighEx - 1
    return (rand() % (iHighEx - iLow)) + iLow;
}

//Send string with location and colour to tera term
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

//Convert hexadecimal digit to decimal
int ToDigitVal (char digit) {
    if (digit >= 0 + 48 && digit <= 9 + 48) {
        return (unsigned int)(digit - 48);
    }

    if (digit >= 'A' && digit <= 'F') {
        return (unsigned int)((digit - 'A') + 10);
    }

    return 0;
}

//Convert array of hex to decimal
unsigned int HexArrayToUInt16 (char * pArray) {
    int counter = strlen(pArray) - 1;
    unsigned int decVal = 0;

    while (counter >= 0) {
        decVal += ToDigitVal(pArray[counter]) * pow(16, strlen(pArray) - 1 - counter);
        counter--;
    }

    return decVal;
}


