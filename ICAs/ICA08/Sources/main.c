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
//char data;

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

//Setting Baud rate
//Board rate = 20E6 / (16 * 9600)
SCI0BD = 130;

//Enable recieving
SCI0CR2_RE = 1;
//Enable transmitting
SCI0CR2_TE = 1;

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    //Check if register is ready to recieve data
    if(SCI0SR1_TDRE) //Check if transmit data register is empty
    {
      SCI0DRL = 'A';
    }

    /* if(SCI0SR1 & SCI0SR1_RDRF_MASK) //Check if a character has been received
    {
      data = SCI0DRL;

      if (data = 'f') {
        SWL_ON(SWL_RED);
        SCI0DRL = 0;
      }
      else SWL_OFF(SWL_RED);
    } */
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/

