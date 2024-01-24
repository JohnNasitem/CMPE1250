/********************************************************************/
// HC12 Program:  ICA02
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        John N. Nasitem
// Details:       A more detailed explanation of the program is entered here               
// Date:          Date Created
// Revision History :



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
void RED(int loop);
void GREEN(int loop);
/********************************************************************/

/********************************************************************/
// Global Variables
unsigned int uiMainLoopCount;             //Clock
/********************************************************************/

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  //Any main local variables must be declared here

  // main entry point
  _DISABLE_COP();
  //EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
  PT1AD1 &= 0x1F;
  DDR1AD1 = 0xE0;
  uiMainLoopCount = 0;
/********************************************************************/


/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
      ++uiMainLoopCount;
      RED(uiMainLoopCount);
      GREEN(uiMainLoopCount);
  }                   
}

/********************************************************************/
// Functions
void RED (loop) {
  if (loop < 0x1000) {
    PT1AD1 |= 1 << 7;
  }
  else {
    PT1AD1 &= 0x7F;
  }
}

void GREEN (loop) {
  if (loop >= 0x1000) {
    PT1AD1 |= 0x20;
  }
  else {
    PT1AD1 &= 0b11011111;
  }
}
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
