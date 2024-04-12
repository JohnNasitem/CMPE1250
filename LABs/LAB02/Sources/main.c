/********************************************************************/
// HC12 Program:  LAB02
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

/********************************************************************/
// Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
int counter = 0;
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  // Any main local variables must be declared here
  int RTIPasses = 0;
  int dpIndex = 4;
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

  //ISR
  DDRJ &= 0b00000000;
  PPSJ &= 0b00000000;
  PIEJ |= 0b11111111;

  Segs_Clear();
  Segs_16D(0, Segs_LineTop);

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    RTI_Delay_ms(50);
    RTIPasses++;
    SWL_TOG(SWL_RED);

    //if (SWL_Pushed(SWL_CTR)) counter = 0;
    /* Ask for clarification
      If the CTR switch is pushed, reset the count back to zero. This code will be positioned in the
      main loop, outside of any constructs related to operating the RTI.
    */

    if (RTIPasses % 4 == 0) Segs_Custom(dpIndex++, 0b00000000);

    //1 second has passed
    if (RTIPasses >= 20) {
      RTIPasses = 0;
      counter++;
      if (counter > 9999) counter = 0;

      SWL_TOG(SWL_GREEN);
      Segs_ClearLine(Segs_LineBottom);
      Segs_16D(counter, Segs_LineTop);

      dpIndex = 4;
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
//maybe put reset here in an interrupt
interrupt VectorNumber_Vportj void Vportj_ISR(void)           //get this to work
{
  PIFJ |= 0b00000000;
  //CRGFLG = CRGFLG_RTIF_MASK; //clear flag;
  SWL_ON(SWL_YELLOW);
  if (SWL_Pushed(SWL_CTR)) {
    counter = 0;
    Segs_16D(counter, Segs_LineTop);
  }
} 