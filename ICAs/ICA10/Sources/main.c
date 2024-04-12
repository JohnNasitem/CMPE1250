/********************************************************************/
// HC12 Program:  Ica 10
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        John N. Nasitem
// Details:       Messing around with segs
// Date:          Apr 6, 2024
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
int passCounter = 0;                                            //How many times a "pass" has happened
int positionChanges = 0x0;                                     //How many times the position of caret has moved
int counter = 0;                                                //Current index of the frame of the animation
int index = 0;                                                  //Index of the caret position
int hexCounter = 0x0;                                           //Incremented counter in hex
unsigned char AnimationFrames[] = {                             //The animation frames
    0b11000000,
    0b10100000,
    0b10010000,
    0b10000001,
    0b10001000,
    0b10000010
};
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
    //Tier1();
    //Tier2();
    Tier3();
  }
}

/********************************************************************/
// Functions
/********************************************************************/
void Tier1()
{
  //Checks if center button is pressed
  if (SWL_Pushed(SWL_CTR))
  {
    //Creates delay and clears previous frame
    RTI_Delay_ms(100);
    Segs_Clear();

    //Counts up on top line and counts down on bottom line
    Segs_16H(hexCounter, Segs_LineTop);
    Segs_16H(0xFFFF - hexCounter++, Segs_LineBottom);
  }
}

void Tier2() {
  char moved = 0;                                             //if the caret moved postions

  //Creates delay and clears previous frame
  RTI_Delay_ms(100);
  Segs_Clear();

  //Increment pass
  passCounter++;

  //Checks if the passCounter passed over 10 times
  if (passCounter >= 9) {
    //Checks if right/left switch has been pressed and if it can move in that direction
    if (SWL_Pushed(SWL_RIGHT) && index < 3) {
      //Increment index and set moved to true
      index++;
      moved = 1;
    }
    else if (SWL_Pushed(SWL_LEFT) && index > 0) {
      //deincrement index and set moved to true
      index--;
      moved = 1;
    }

    //If the caret has moved then increment positionChanges
    if (moved) {
      positionChanges++;
      moved = 0;
    }

    //Reset passCounter
    passCounter = 0;
  }

  //Display carat and how many times the carat moved
  Segs_Custom(index, AnimationFrames[counter++]);
  Segs_16H(positionChanges, Segs_LineBottom);

  //Reset counter
  if (counter == 6) counter = 0;
}

void Tier3() {
  char moved = 0;                                                   //if the carat has moved
  char beenPressedRight = 0;                                        //if right has been pressed
  char beenPressedLeft = 0;                                         //if left has been pressed

  //Creates delay and clears previous frame
  RTI_Delay_ms(100);
  Segs_Clear();

  //If right is pressed set beenPressedRight
  if (SWL_Pushed(SWL_RIGHT)) {
    //if beenPressedLeft is true then reset passCount and beenPressedLeft
    if (beenPressedLeft) {
      beenPressedLeft = 0;
      passCounter = 0;
    }
    beenPressedRight = 1;
  }
  //if not then unset it
  else {
    beenPressedRight = 0;
  }

  //If left is pressed set beenPressedLeft
  if (SWL_Pushed(SWL_LEFT)) {
    //if beenPressedRight is true then reset passCount and beenPressedRight
    if (beenPressedRight) {
      beenPressedRight = 0;
      passCounter = 0;
    }
    beenPressedLeft = 1;
  }
  //if not then unset it
  else {
    beenPressedLeft = 0;
  }

  //if either is press then increment passCount if not then reset it
  if (beenPressedRight || beenPressedLeft) passCounter++;
  else passCounter = 0;

  //if counter has reached 10 passes attempt to move carat
  if (passCounter >= 9) {

    //Checks if right/left switch has been pressed and if it can move in that direction
    if (beenPressedRight && index < 3) {
      index++;
      moved = 1;
    }
    else if (beenPressedLeft && index > 0) {
      index--;
      moved = 1;
    }

    //If the caret has moved then increment positionChanges
    if (moved) {
      positionChanges++;
      moved = 0;
    }

    //Reset passCounter
    passCounter = 0;
  }

  //Display carat and how many times the carat moved
  Segs_Custom(index, AnimationFrames[counter++]);
  Segs_16H(positionChanges, Segs_LineBottom);

  //Reset counter
  if (counter == 6) counter = 0;
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
