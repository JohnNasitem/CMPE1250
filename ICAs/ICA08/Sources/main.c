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
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";                       //String of the alphabet
char pData;                                                           //Data being received by the SCI;
unsigned int buadRate;

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
Clock_Set20MHZ();
buadRate = sci0_Init(9600, 0);

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
    //sci0_txByte(alphabet[rand() % 26]);


    if (sci0_rxByte(&pData)) {
      if (IsVowel(pData)) {
        SWL_ON(SWL_GREEN);
        SWL_OFF(SWL_YELLOW);
      }
      else {
        SWL_OFF(SWL_GREEN);
        SWL_ON(SWL_YELLOW);
      }
    }
    else {
      //Should turn off if a key isnt being held, potentially not needed
      SWL_OFF(SWL_GREEN);
      SWL_OFF(SWL_YELLOW);
    }
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
unsigned char IsVowel(unsigned char potentialVowel) {
  //potentialVowel = tolower((char)potentialVowel);           //potentially not needed?
  potentialVowel = 97;
  sci0_txByte(potentialVowel);

  if (potentialVowel == 'a' || potentialVowel == 'e' || potentialVowel == 'i' || potentialVowel == 'o' || potentialVowel == 'u' || potentialVowel == 'y') {     //Should y be a vowel?
    return 1;
  }

  return 0;
}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/

