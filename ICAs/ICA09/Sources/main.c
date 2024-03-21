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
#include <string.h> 

//Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
char[] vowels = ["AEIOUY"]

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
sci0_Init(19200, 0);
RTI_Init();
unsigned int counter = 0;
unsigned char currentVowel;
char[] randomString;
unsigned int sumVowels = 0;
unsigned int totalStringsTransmitted = 0;

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    //Measure how long a transmission takes
    SWL_ON(SWL_RED);
    totalStringsTransmitted++;
    counter = 0;

    //Iterate 20 times
    while (counter < 20) {
      //Gets a random vowel
      currentVowel = vowels[GetRandom(0, strlen(vowels))];

      //Uppercase the vowel if center button is pressed and lowercase if not
      if (SWL_Pushed(SWL_CTR)) currentVowel = touppper(currentVowel); //check if toupper works like that
      else currentVowel = tolower(currentVowel);

      randomString[counter] = currentVowel;

      sumVowels += currentVowel; //Check to make sure this adds the vowels instead of concatinate

      counter++;
    }

    //Part B: adds the sum of the vowels after the vowels with a space before and after
    randomString[counter] " %04d ", sumVowels;

    //Display on the screen
    sci0_txStr(&randomString);


    SWL_OFF(SWL_RED);

    //Delay by 250ms
    RTI_Delay_ms(250);
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
