#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sci.h"
#include "clock.h"
#include <string.h> 

unsigned long sci0_Init(unsigned long ulBaudRate, int iRDRF_Interrupt)
{ // What does iRDRF_Interrupt do?
    // Setting Baud rate
    // Board rate = 20E6 / (16 * 9600)
    SCI0BD = (unsigned long)(Clock_GetBusSpeed() / (16 * ulBaudRate));

    // Enable recieving
    SCI0CR2_RE = 1;
    // Enable transmitting
    SCI0CR2_TE = 1;
    // Sets if RDRF or OR to generate interupt requests, 0 = disabled, 1 = enabled
    SCI0CR2_RIE = iRDRF_Interrupt;

    // Returning the actual baud
    return SCI0BD;
}

unsigned char sci0_bread(void)
{
    // Wait till a character is received
    while (!(SCI0SR1 & SCI0SR1_RDRF_MASK))
        ;

    // Returns byte
    return = SCI0DRL;
}

unsigned char sci0_rxByte(unsigned char * pData)
{
    // Non-blocking receiving
    if (SCI0SR1 & SCI0SR1_RDRF_MASK) // Check if a character has been received
    {
        pData = SCI0DRL;
        return 1;
    }
    else {
        return 0;
    }
}

void sci0_txByte(unsigned char data)
{
    // Check if transmit data register is empty
    if (SCI0SR1 & SCI0SR1_TDRE_MASK)
    {
        // Send data
        SCI0DRL = data;
    }
}

void sci0_txStr (char const * straddr) {
    unsigned int stringIndex;                                       //currently iterated index of the char being sent to the SCI
    
    //Loop through each char of the string
    for (stringIndex = 0; stringIndex < strlen(straddr); stringIndex++) {
        //Transmit the char to the SCI
        sci0_txByte(straddr[stringIndex]);
    }
}