/********************************************************************/
// HC12 Program:  ICA07
// Processor:     MC9S12XDP512
// Bus Speed:     MHz
// Author:        John N. Nasitem
// Details:       LED logic and button
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "rti.h"
#include "SW_LED.h"

// Other system includes or your includes go here
// #include <stdlib.h>
// #include <stdio.h>

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

  // main entry point
  _DISABLE_COP();
  // EnableInterrupts;

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  SWL_Init();
  RTI_Init();

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    if (SWL_Pushed(SWL_RIGHT))
    {
      SWL_OFF(SWL_RED);
      SWL_ON(SWL_GREEN);
    }
    else if (SWL_Pushed(SWL_LEFT))
    {
      SWL_ON(SWL_RED);
      RTI_Delay_ms(1);
      SWL_OFF(SWL_RED);
      RTI_Delay_ms(9);
    }
    else
    {
      if (SWL_Pushed(SWL_UP))
        RTI_Delay_ms(8); // This takes precedence if both are pressed
      else if (SWL_Pushed(SWL_DOWN))
        RTI_Delay_ms(12);
      else
        RTI_Delay_ms(10);

      SWL_TOG(SWL_RED);
      SWL_OFF(SWL_GREEN);
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
