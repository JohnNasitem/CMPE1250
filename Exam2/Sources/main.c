/********************************************************************/
// HC12 Program:  Exam 2
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
#include "sci.h"
#include "rti.h"
#include "misc.h"

//Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>



/********************************************************************/
//Defines
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
  //Any main local variables must be declared here
  unsigned int counter = 0;
  unsigned char character = '.';
  unsigned int characterWidth = 0;
  unsigned int numCharSent = 0;
  char buffer[40]; 
  unsigned int countColour = 39;
  unsigned char pData;
  // main entry point
  _DISABLE_COP();
  //EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
/********************************************************************/
SWL_Init();
Clock_EnableOutput(ClockOutDiv2);
sci0_Init(38400, 0);
RTI_Init();

/********************************************************************/
  // main program loop
/********************************************************************/
  for (;;)
  {
    RTI_Delay_ms(10);
    counter++;
    SWL_TOG(SWL_RED);

    if (sci0_rxByte(&pData)) {
      pData = toupper(pData);
      if (pData == 'R') countColour = 31;
      else if (pData == 'G') countColour = 32;
      else if (pData == 'B') countColour = 34;
    }

    if (counter == 10) {
      SWL_TOG(SWL_GREEN);
      numCharSent++;

      sprintf(buffer, "\x1b[%dm", countColour);
      sci0_txStr(buffer);

      sprintf(buffer, "%05d", numCharSent);
      sci0_txStrXY(0, 1, buffer);

      if (SWL_Pushed(SWL_UP)) character = '!';
      else if (SWL_Pushed(SWL_DOWN)) character = '?';
      else if (SWL_Pushed(SWL_CTR)) character = '.';

      sci0_txStr("\x1b[39m");

      sci0_GotoXY(characterWidth, 3);
      sci0_txByte(character);
      characterWidth++;
      if (characterWidth > 80) characterWidth = 0;
      counter = 0;
    }
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
