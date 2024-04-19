/********************************************************************/
// HC12 Program:  LAB03
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        John N. Nasitem
// Details:       
// Date:          Apr 12, 2024
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "clock.h"
#include "rti.h"
#include "segs.h"
#include "SW_LED.h"

// Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/********************************************************************/
// Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  // Any main local variables must be declared here
  /*
    0 = up
    1 = down
    2 = left
    3 = right
  */
  int buttonPressed = -1;
  char valueArr[] = {0, 0, 0, 0};
  int value = 0;
  unsigned char edittingIndex = 3;
  int incr = 0;
  // main entry point
  _DISABLE_COP();
  // EnableInterrupts;

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  Clock_EnableOutput(ClockOutDiv2);
  RTI_Init();
  Segs_Init();
  SWL_Init();

  Segs_Clear();
  Segs_16D(0, Segs_LineTop);

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    RTI_Delay_ms(50);
    value = 0;

    if (SWL_Pushed(SWL_UP) && buttonPressed != 0) {
      buttonPressed = 0;
      valueArr[edittingIndex]++;
      if (valueArr[edittingIndex] == 10) valueArr[edittingIndex] = 0;
    }
    else if (!SWL_Pushed(SWL_UP) && buttonPressed == 0) buttonPressed = -1;

    if (SWL_Pushed(SWL_DOWN) && buttonPressed != 1) {
      buttonPressed = 1;
      valueArr[edittingIndex]--;
      if (valueArr[edittingIndex] == -1) valueArr[edittingIndex] = 9;
    }
    else if (!SWL_Pushed(SWL_DOWN) && buttonPressed == 1) buttonPressed = -1;

    if (SWL_Pushed(SWL_LEFT) && buttonPressed != 2 && edittingIndex > 0) {
      buttonPressed = 2;
      edittingIndex--;
    }
    else if (!SWL_Pushed(SWL_LEFT) && buttonPressed == 2) buttonPressed = -1;

    if (SWL_Pushed(SWL_RIGHT) && buttonPressed != 3 && edittingIndex < 3) {
      buttonPressed = 3;
      edittingIndex++;
    }
    else if (!SWL_Pushed(SWL_RIGHT) && buttonPressed == 3) buttonPressed = -1;
    

    for (incr = 0; incr < 4; incr++) {
      value += valueArr[incr] * pow(10, 3 - incr);
      //Segs_Normal(incr, valueArr[incr], Segs_DP_OFF);
    }

    Segs_16D(value, Segs_LineTop);
    Segs_16H(value, Segs_LineBottom);
    Segs_Normal(edittingIndex, valueArr[edittingIndex], Segs_DP_ON);
  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/