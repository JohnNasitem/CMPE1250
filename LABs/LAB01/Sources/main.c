/********************************************************************/
// HC12 Program:  LAB01
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        John N. Nasitem
// Details:       Simple binary calculator
// Date:          29/03/2024
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "clock.h"
#include "sci.h"
#include "rti.h"
#include "misc.h"

// Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/********************************************************************/
// Defines
/********************************************************************/
typedef enum Operation_Typedef__
{
  OP_AND = 0,
  OP_OR = 1
} Operation;

/********************************************************************/
// Local Prototypes
/********************************************************************/
// draw the entire portion of the output that changes
// with a change in operands or operator
void DrawState(unsigned char * cOPA, unsigned char * cOPB, Operation op);

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
  unsigned char pData;                                        //Holds the character being recieved
  Operation op;                                               //Current operation being used
  int iXEditPos = 0, iYEditPos = 0;                           //Current cursor position
  unsigned char OPA[6] = "0000";                              //Value of operand a
  unsigned char OPB[6] = "0000";                              //Value of operand b

  // main entry point
  _DISABLE_COP();
  // EnableInterrupts;

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  Clock_EnableOutput(ClockOutDiv2);
  sci0_Init(38400, 0);
  RTI_Init();

  /********************************************************************/
  // main program loop
  /********************************************************************/

  //Display the static parts
  sci0_txStrXY(0, 1, "John Nasitem");
  sci0_txStrXY(0, 2, "Simple Binary Calculator");
  DrawState(OPA, OPB, op);
  sci0_GotoXY(13 + iXEditPos, 5 + iYEditPos);

  for (;;)
  {
    //Check if a character has been recieved
    if (sci0_rxByte(&pData))
    {
      //Changes the operation being used
      if (pData == '&') op = OP_AND;
      else if (pData == '|') op = OP_OR;

      //Checks if tab has been pressed
      if (pData == '\x09')
      {
        //Swaps which operand is selected
        if (iYEditPos) iYEditPos = 0;
        else iYEditPos = 1;

        //Set cursor to the start of the newly selected operand
        iXEditPos = 0;
        sci0_GotoXY(13 + iXEditPos, 5 + iYEditPos);
      }

      //Uppercases the character
      pData = toupper(pData);

      //Checks if a valid hex value has been recieved
      if ((pData >= 0 + 48 && pData <= 9 + 48) || (pData >= 'A' && pData <= 'F'))
      {
        //Changes the value in the correct operand array
        if (!iYEditPos) OPA[iXEditPos] = pData;
        else OPB[iXEditPos] = pData;

        //Increments iXEditPos
        iXEditPos++;
        if (iXEditPos >= 4) iXEditPos = 0;
      }

      //Draws the new state
      DrawState(OPA, OPB, op);
      sci0_GotoXY(13 + iXEditPos, 5 + iYEditPos);
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/
void DrawState(unsigned char * cOPA, unsigned char * cOPB, Operation op)
{
  unsigned int iOPA = HexArrayToUInt16(cOPA);                                 //Decimal value of operand A
  unsigned int iOPB = HexArrayToUInt16(cOPB);                                 //Decimal value of operand B
  char buffer[100];                                                           //Buffer

  //Clearing non static parts
  sci0_txStrXY(5, 5, "\x1b[0J");

  //Display Operands
  sprintf(buffer, "OP A: 0x%s (%05u)", cOPA, iOPA);
  sci0_txStrXY(5,5, buffer);
  sprintf(buffer, "OP B: 0x%s (%05u)", cOPB, iOPB);
  sci0_txStrXY(5,6, buffer);

  //Display binary conversions of operands in an equation
  sci0_GotoXY(11, 8);
  sci0_ShowBin16(iOPA);

  //Which operation is being used
  if (op == OP_AND) sci0_txStrXY(9 , 9, "& ");
  else sci0_txStrXY(9 , 9, "| ");

  //Display binary conversions of operands in an equation
  sci0_ShowBin16(iOPB);
  sci0_txStrXY(9 , 10, "------------------");

  //Display results
  sci0_GotoXY(11, 11);
  if (op == OP_AND) sci0_ShowBin16(iOPA & iOPB);
  else sci0_ShowBin16(iOPA | iOPB);
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
