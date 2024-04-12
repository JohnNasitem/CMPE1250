#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "segs.h"

/********************************************************************/
// Local Helpers
/********************************************************************/
//Pull Down strobe
#define Segs_WLATCH PORTA &= (~0x01); PORTA |= 0x01;

#define Segs_ML PORTA &= (~0x02);
#define Segs_MH PORTA |= 0x02;

void Segs_Init (void) {
    // ensure port pins are high
    PORTA |= 0x03;

    // set port pins as outputs
    DDRA |= 0x03;
    DDRB = 0xff;
}

// normal decode, 8-bit value, to address, w or w/o decimal point
void Segs_Normal (unsigned char Addr, unsigned char Value, Segs_DPOption dp) {
    // trim address to range
    Addr &= 0x07;

    //Bank A, Normal Op, Decode, Hex, No Data Coming
    Addr |= 0b01011000;

    //Check if show decimal point
    if (dp)
        Value &= (~0x80);
    else
        Value |= 0x80;

    //set the location
    PORTB = Addr;
    //Present command with mode high
    Segs_MH

    //latch command
    Segs_WLATCH

    //set data
    PORTB = Value;
    //Present command with mode low
    Segs_ML

    //latch data / update
    Segs_WLATCH
}

void Segs_Custom (unsigned char Addr, unsigned char Value) {
    // trim address to range
    Addr &= 0x07;

    //Bank A, Normal Op, No Decode, Hex, No Data Coming
    Addr |= 0b01111000;

    //set the location
    PORTB = Addr;
    
    //Present command with mode high
    Segs_MH

    //latch command
    Segs_WLATCH

    //set data
    PORTB = Value;
    //Present command with mode low
    Segs_ML

    //latch data / update
    Segs_WLATCH
}

void Segs_Clear(void) {
    int incr;

    for(incr = 0; incr < 8; incr++) {
        Segs_Custom(incr, 0b10000000);
    }
}

void Segs_8H (unsigned char addr, unsigned char value) {
    //Sanitizing address
    addr %= 8;

    //Bit shift by 4 to isolate the first digit
    Segs_Normal(addr, value >> 4, Segs_DP_OFF);
    //Send second digit with sanitized address
    Segs_Normal((addr + 1) % 8, value % 0x10, Segs_DP_OFF);
}

void Segs_16H (unsigned int value, Segs_LineOption line) {
    int startAddr = 4 * line;
    int incr;

    //Iterate through each nibble
    for (incr = 0; incr < 4; incr++) {
        //Send nibbles
        //(value >> (4 * (3 - incr))) bit shifts the value in the order of 12,8,4,0
        //(16 * (4 - incr)) gets the modulo of the bit shifted in the order of 16,32,48,64
        Segs_Normal(startAddr + incr, (value >> (4 * (3 - incr))) % (16 * (4 - incr)), Segs_DP_OFF);
    }
}