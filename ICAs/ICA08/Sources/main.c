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
#include "clock.h"
#include "sci.h"
#include "rti.h"
#include <ctype.h>

//Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
//Checks if the given char is a vowel
//Returns 1 if true, 0 if false
unsigned char IsVowel(unsigned char potentialVowel);

/********************************************************************/
// Global Variables
/********************************************************************/
char pData;                                                           //Data being received by the SCI;

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
Clock_EnableOutput(ClockOutDiv2);
sci0_Init(9600, 0);
RTI_Init();

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    //Blocking delay of 50 ms
    RTI_Delay_ms(50);
    //Toggle Red LED
    SWL_TOG(SWL_RED);
    //Send a random letter
    sci0_txByte(rand() % 26 + 'A');

    //Check if a input has been recieved
    if (sci0_rxByte(&pData)) {
      //If its a vowel then turn on green and turn of yellow
      if (IsVowel(pData)) {
        SWL_ON(SWL_GREEN);
        SWL_OFF(SWL_YELLOW);
      }
      //If its a vowel then turn off green and turn on yellow
      else {
        SWL_OFF(SWL_GREEN);
        SWL_ON(SWL_YELLOW);
      }
    }
    else {
      //Should turn off if a key isnt being held
      SWL_OFF(SWL_GREEN);
      SWL_OFF(SWL_YELLOW);
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/
unsigned char IsVowel(unsigned char potentialVowel) {
  //Uppercase input
  potentialVowel = toupper((char)potentialVowel);

  if (potentialVowel == 'A' || potentialVowel == 'E' || potentialVowel == 'I' || potentialVowel == 'O' || potentialVowel == 'U' || potentialVowel == 'Y') {     //Should y be a vowel?
    return 1;
  }

  return 0;
}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/

