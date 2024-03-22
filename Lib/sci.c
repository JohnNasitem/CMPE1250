#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sci.h"
#include "clock.h"
#include <string.h> 

unsigned long sci0_Init(unsigned long ulBaudRate, int iRDRF_Interrupt)
{ // What does iRDRF_Interrupt do?
    // Setting Baud rate
    // Board rate = 20E6 / (16 * 9600)
    /* SCI0BD = (unsigned int)(Clock_GetBusSpeed() / (16 * ulBaudRate));

    // Enable recieving
    SCI0CR2_RE = 1;
    // Enable transmitting
    SCI0CR2_TE = 1;
    // Sets if RDRF or OR to generate interupt requests, 0 = disabled, 1 = enabled
    SCI0CR2_RIE = iRDRF_Interrupt; */

    SCI0BD = 130;
    SCI0CR2 = 0b00001100;

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