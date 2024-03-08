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

//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
void Tier1Logic(void);
void Tier2Logic(void);
void Tier3Logic(void);
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
  //Any main local variables must be declared here

  // main entry point
  _DISABLE_COP();
  //EnableInterrupts;
  
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
      Tier1Logic();
      Tier2Logic();
      Tier3Logic();
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
void Tier1Logic(void) { //Test with ossciliscope
  if (SWL_Pushed(SWL_UP) > 0) RTI_Delay_ms(8);
  else if (SWL_Pushed(SWL_DOWN) > 0) RTI_Delay_ms(12);
  else RTI_Delay_ms(10);

  SWL_TOG(SWL_RED);
}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
