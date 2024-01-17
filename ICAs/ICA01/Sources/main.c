/********************************************************************/
// HC12 Program:  ICA01
// Processor:     MC9S12XDP512
// Bus Speed:     16 MHz
// Author:        John N. Nasitem
// Details:       Toggles the red led on and off on a cycle
// Date:          1/17/2024
// Revision History :

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

// Other system includes or your includes go here
// #include <stdlib.h>
// #include <stdio.h>

/********************************************************************/
// Defines
#define RED_LED 0b10000000
#define INDEX_MAX 10
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
unsigned int counter;               // Used to make a clock       
unsigned int index;                 // extension of the clock to make it longer

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
  PT1AD1 |= RED_LED;
  DDR1AD1 |= RED_LED;
  counter = 0;
  index = 0;
  /********************************************************************/

  /********************************************************************/
  // main program loop
  /********************************************************************/

  // Infinite loop
  for (;;)
  {
    // Clock, increments counter var until it reachs limit then it resets to zero when trying to increment again
    if (++counter == 0)
    {
      // Making the clock last longer
      if (++index >= INDEX_MAX)
      {
        index = 0;
        //Toggles the red legd
        PT1AD1 ^= RED_LED;
      }
    }
  }
}

  /********************************************************************/
  // Functions
  /********************************************************************/

  /********************************************************************/
  // Interrupt Service Routines
  /********************************************************************/
