/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     MHz
// Author:        This B. You
// Details:       A more detailed explanation of the program is entered here
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
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
void TierOne_Logic();
void TierTwo_Logic();
void TierThree_Logic();

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

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    // TierOne_Logic();
    // TierTwo_Logic();
    TierThree_Logic();
  }
}

/********************************************************************/
// Functions
/********************************************************************/
void TierOne_Logic()
{
  if (SWL_Pushed(SWL_LEFT))
  {
    SWL_ON(SWL_RED);
  }
  else
  {
    SWL_OFF(SWL_RED);
  }

  if (SWL_Pushed(SWL_CTR))
  {
    SWL_ON(SWL_YELLOW);
  }
  else
  {
    SWL_OFF(SWL_YELLOW);
  }

  if (SWL_Pushed(SWL_RIGHT))
  {
    SWL_ON(SWL_GREEN);
  }
  else
  {
    SWL_OFF(SWL_GREEN);
  }
}

void TierTwo_Logic()
{
  if (SWL_Pushed(SWL_LEFT))
  {
    SWL_ON(SWL_RED);
  }

  if (SWL_Pushed(SWL_CTR))
  {
    SWL_ON(SWL_YELLOW);
  }

  if (SWL_Pushed(SWL_RIGHT))
  {
    SWL_ON(SWL_GREEN);
  }

  if (SWL_Pushed(SWL_UP) || SWL_Pushed(SWL_DOWN))
  {
    SWL_OFF(SWL_GREEN);
    SWL_OFF(SWL_YELLOW);
    SWL_OFF(SWL_RED);
  }
}

void TierThree_Logic()
{
  if (SWL_Pushed(SWL_LEFT) && !(PT1AD1 & SWL_YELLOW && PT1AD1 & SWL_GREEN))
  {
    SWL_TOG(SWL_RED);
  }

  if (SWL_Pushed(SWL_CTR) && !(PT1AD1 & SWL_RED && PT1AD1 & SWL_GREEN))
  {
    SWL_TOG(SWL_YELLOW);
  }

  if (SWL_Pushed(SWL_RIGHT) && !(PT1AD1 & SWL_RED && PT1AD1 & SWL_YELLOW))
  {
    SWL_TOG(SWL_GREEN);
  }

  if (SWL_Pushed(SWL_UP) || SWL_Pushed(SWL_DOWN))
  {
    SWL_OFF(SWL_GREEN);
    SWL_OFF(SWL_YELLOW);
    SWL_OFF(SWL_RED);
  }
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
