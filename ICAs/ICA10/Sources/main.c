/********************************************************************/
// HC12 Program:  Ica 10
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        John N. Nasitem
// Details:
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "SW_LED.h"
#include "clock.h"
#include "rti.h"
#include "misc.h"
#include "segs.h"

// Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
void Tier1(void);
void Tier2(void);
void Tier3(void);
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
  Clock_EnableOutput(ClockOutDiv2);
  RTI_Init();
  Segs_Init();

  Segs_Clear();

  Segs_8H(7, 0xE4);
  Segs_Normal(4, 3, Segs_DP_OFF);

  Segs_Custom(1, 0b01001010);
  Segs_Custom(2, 0b11110000);
  Segs_Custom(3, 0b10000000);
  Segs_Custom(5, 0b10001011);
  Segs_Custom(6, 0b10110001);

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    Tier1();
    //Tier2();
    //Tier3();
  }
}

/********************************************************************/
// Functions
/********************************************************************/
void Tier1()
{
  int counter = 0x0;

  if (SWL_Pushed(SWL_CTR))
  {
    RTI_Delay_ms(100);
    Segs_Clear();

    Segs_16H(counter, Segs_LineTop);
    Segs_16H(0xFFFF - counter++, Segs_LineBottom);
  }
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
