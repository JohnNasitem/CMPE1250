#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sci.h"
#include "clock.h"
#include <string.h> 
#include <stdio.h>
#include "misc.h"

unsigned long sci0_Init(unsigned long ulBaudRate, int iRDRF_Interrupt)
{ // What does iRDRF_Interrupt do?
    // Setting Baud rate
    // Board rate = 20E6 / (16 * 9600)
    SCI0BD = (unsigned int)(Clock_GetBusSpeed() / (16 * ulBaudRate));

    // Enable recieving
    SCI0CR2_RE = 1;
    // Enable transmitting
    SCI0CR2_TE = 1;
    // Sets if RDRF or OR to generate interupt requests, 0 = disabled, 1 = enabled
    SCI0CR2_RIE = iRDRF_Interrupt;

    // Returning the actual baud
    return SCI0BD;
}

// Blocking receiving
unsigned char sci0_bread(void)
{
    // Wait till a character is received
    while (!(SCI0SR1 & SCI0SR1_RDRF_MASK));

    // Returns byte
    return SCI0DRL;
}

// Non-blocking receiving
unsigned char sci0_rxByte(unsigned char * pData)
{
    // Check if a character has been received
    if (SCI0SR1 & SCI0SR1_RDRF_MASK)
    {
        *pData = SCI0DRL;
        return 1;
    }
    else {
        return 0;
    }
}

//send btye blocking
void sci0_txByte(unsigned char data)
{
    // wait for transmit data register to be empty
    while (!(SCI0SR1 & SCI0SR1_TDRE_MASK));
    
    // Send data
    SCI0DRL = data;
}

void sci0_txStr (char const * straddr) {
    unsigned int stringIndex;                                       //currently iterated index of the char being sent to the SCI
    
    //Loop through each char of the string
    for (stringIndex = 0; stringIndex < strlen(straddr); stringIndex++) {
        //Transmit the char to the SCI
        sci0_txByte(straddr[stringIndex]);
    }

    //Example from pdf -- not allowed to use this form
    /* for (; *straddr; ++straddr)
        sci0_txByte(straddr); */
}

int sci0_Peek (void) {
    if (SCI0SR1 & SCI0SR1_RDRF_MASK) return 1;
    return 0;
}

void sci0_GotoXY (int iCol, int iRow) {
    char buffer[20] = "";
    sprintf(buffer, "\x1b[%d;%dH", iRow, iCol);
    sci0_txStr(buffer);
}

void sci0_txStrXY (int iCol, int iRow, char const * straddr) {
    sci0_GotoXY(iCol, iRow);
    sci0_txStr(straddr);
}

void sci0_ClearScreen (void) {
    sci0_txStr("\x1b[2J");
}

void sci0_ShowBin16 (unsigned int iVal) {
    char reverseBinary[20];
    char binary[20];
    char buffer[20] = "";
    char counter = 0;
    int start = 0;
    int end;

    //Get remainders
    while (iVal != 0) {
        reverseBinary[counter] = iVal % 2;

        iVal = (unsigned int)(iVal / 2);
        counter++;
    }

    end = --counter;

    //Reverse and pad with leading zeros
    while (start < 16) {
        if (start <= end) {
            binary[15 - start] = reverseBinary[start];
        }
        else {
            binary[15 - start] = 0;
        }
        counter--;
        start++;
    }

    start = 0;

    //Display
    while (start < 16) {
        sprintf(buffer, "%d", binary[start++]);
        sci0_txStr(buffer);
    }
}
