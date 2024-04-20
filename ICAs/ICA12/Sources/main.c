/********************************************************************/
// HC12 Program:  Ica 12
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        John N. Nasitem
// Details:       Messing around with lcds
// Date:          Apr 6, 2024
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "clock.h"
#include "lcd.h"

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
  Clock_EnableOutput(ClockOutDiv2);
  lcd_Init();

  lcd_Data('Q');

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {

  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
