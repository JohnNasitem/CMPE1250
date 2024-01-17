/********************************************************************/
// HC12 Program:  ICA02
// Processor:     MC9S12XDP512
// Bus Speed:     MHz
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
#define RED_LED 0b10000000
#define GREEN_LED 0b0010000
/********************************************************************/

/********************************************************************/
// Local Prototypes
static void Red(unsigned int loop);
static void Green(unsigned int loop);
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
  PT1AD1 |= RED_LED;
  DDR1AD1 |= RED_LED;
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
static void Red(unsigned int loop) {
  if (loop < 0x1000) {
    PT1AD1 |= (byte)(((UInt32)1 << (7)));
  }
  else {
    PT1AD1 &= 0x7F;
  }
}

static void Green(unsigned int loop) {
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
