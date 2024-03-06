/********************************************************************/
// HC12 Program:  ICA06 - Clock Library
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        John N. Nasitem
// Details:       See how frequency changes with the change of bus speed frequency
// Date:          Mar. 3/2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "clock.h"
#include "SW_LED.h"

//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned long delay; 

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
/********************************************************************/
SWL_Init();
Clock_EnableOutput(ClockOutDiv3);

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    //Turn on LED
    SWL_ON(SWL_RED);
    //Delay by 100ms (on bus rate of 8MHz)
    /*
    How I got 8512.
    First Tested with 4000 and got a frequency of 10.640
    I did (4000 * 10.640) / 5 = 8512
    5 came from my target Hz
    */
    for (delay = 0; delay < 8512; delay++) { }
    //Turn off LED
    SWL_OFF(SWL_RED);
    //Same delay as before
    for (delay = 0; delay < 8512; delay++) { }
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/