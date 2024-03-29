/********************************************************************/
// HC12 Program:  Ica 09
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        John N. Nasitem
// Details:       send in a random string of vowels 20 chars long with the sum of hte vowels and run count              
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



/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
char vowels[] = "AEIOUY";
unsigned int counter = 0;
unsigned char currentVowel;
char randomString[22] = "";         //addition 2 char to allow for the \0 to terminate the string
unsigned int sumVowels = 0;
unsigned int totalStringsTransmitted = 0;
unsigned char letter;
char buffer[10] = "";

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

/********************************************************************/
  // main program loop
/********************************************************************/
  //Part C:
  //Start at 0,0
  sci0_txStr("\x1b[0;0H");

  sci0_txStr("John Nasitem");


  for (;;)
  {
    //Measure how long a transmission takes
    SWL_ON(SWL_RED);
    totalStringsTransmitted++;
    counter = 0;
    sumVowels = 0;

    //Iterate 20 times
    while (counter < 20) {
      //Gets a random vowel
      letter = GetRandom(0, strlen(vowels));
      currentVowel = vowels[letter];

      //Uppercase the vowel if center button is pressed and lowercase if not
      if (SWL_Pushed(SWL_CTR)) currentVowel = toupper(currentVowel); //check if toupper works like that
      else currentVowel = tolower(currentVowel);

      //Adds the random vowel to the char array
      randomString[counter] = currentVowel;

      //Gets the sum of the vowels
      sumVowels += currentVowel;

      counter++;
    }

    //Set it to line 3
    sci0_txStr("\x1b[3;0H");
    //Change vowels colour to green
    sci0_txStr("\x1b[32m");
    //Display on the screen
    sci0_txStr(randomString);

    //Part B: adds the sum of the vowels after the vowels with a space before and after
    sprintf(buffer, "%04d", sumVowels);
    sci0_txByte(' ');

    //Change vowels colour to green
    sci0_txStr("\x1b[33m");

    sci0_txStr(buffer);
    sci0_txByte(' ');

    //Set it to line 3
    sci0_txStr("\x1b[5;0H");
    sprintf(buffer, "%d", totalStringsTransmitted);
    //Change vowels colour to default
    sci0_txStr("\x1b[39m");
    //Sends to 
    sci0_txStr(buffer);

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
