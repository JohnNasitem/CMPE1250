#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "misc.h"

int GetRandom (int iLow, int iHighEx) {
    //Returns a random value inclusively between iLow and iHighEx - 1
    return (rand() % (iHighEx - iLow)) + iLow;
}