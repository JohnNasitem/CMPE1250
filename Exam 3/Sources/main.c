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
#include "SW_LED.h"
#include "sci.h"
#include "rti.h"
#include "segs.h"

// Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

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
  //Question A
  /*
  unsigned int totalMS = 0;
  char buffer[50] = "";
  */
  //Question B
  unsigned int xPos = 0;
  unsigned int yPos = 0;
  unsigned int oldXPos = 0;
  unsigned int oldYPos = 0;
  int buttonPressed = -1;
  unsigned int buttonPressCount = 0;
  char lastname[] = "Nasitem";
  // main entry point
  _DISABLE_COP();
  // EnableInterrupts;

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  Clock_EnableOutput(ClockOutDiv2);
  SWL_Init();
  RTI_Init();
  sci0_Init(38400, 0);
  Segs_Init();
  lcd_Init();

  //Question A
  /*
  sci0_txStrXY(0, 0, "Nasitem");
  Segs_Clear();
  */
  //Question B
  Segs_Clear();
  lcd_StringXY(xPos, yPos, lastname);
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
    //Question A
    /*
    RTI_Delay_ms(100);

    sci0_txStrXY(36, 12, "\x1b[0J");

    sprintf(buffer, "%02u:%02u:%0u", (unsigned int)floor(totalMS / 600.0), (unsigned int)floor(totalMS / 10.0), (unsigned int)(totalMS % 10));
    sci0_txStrXY(36, 12, buffer);

    Segs_16D(totalMS % 10000, Segs_LineTop);

    totalMS++;
    */

    //Question B
    //Check for up button press only allowing 1 run if held
    if (SWL_Pushed(SWL_UP) && buttonPressed != 0) {
      buttonPressed = 0;
      buttonPressCount++;
      if (yPos > 0)
        yPos--;
    }
    else if (!SWL_Pushed(SWL_UP) && buttonPressed == 0) buttonPressed = -1;

    //Check for down button press only allowing 1 run if held
    if (SWL_Pushed(SWL_DOWN) && buttonPressed != 1) {
      buttonPressed = 1;
      buttonPressCount++;
      if (yPos < 3)
        yPos++;
    }
    else if (!SWL_Pushed(SWL_DOWN) && buttonPressed == 1) buttonPressed = -1;

    //Check for left button press only allowing 1 run if held
    if (SWL_Pushed(SWL_LEFT) && buttonPressed != 2) {
      buttonPressed = 2;
      buttonPressCount++;
      if (xPos > 0)
        xPos--;
    }
    else if (!SWL_Pushed(SWL_LEFT) && buttonPressed == 2) buttonPressed = -1;

    //Check for up button press only allowing 1 run if held
    if (SWL_Pushed(SWL_RIGHT) && buttonPressed != 3) {
      buttonPressed = 3;
      buttonPressCount++;
      if (xPos < 20 - strlen(lastname))
        xPos++;
    }
    else if (!SWL_Pushed(SWL_RIGHT) && buttonPressed == 3) buttonPressed = -1;

    if (oldXPos != xPos || oldYPos != yPos) {
      lcd_Clear();
      lcd_StringXY(xPos, yPos, lastname);
      oldXPos = xPos;
      oldYPos = yPos;
    }

    Segs_16D(buttonPressCount, Segs_LineBottom);
  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
