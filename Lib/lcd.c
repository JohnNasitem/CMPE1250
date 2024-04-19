#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "lcd.h"

// macros only apply to library, not for public consumption
// gotta be inputs, set R/W* high
#define lcd_RWUp DDRH = 0; PORTK |= 2;

// set R/W* low, // gotta be outputs
#define lcd_RWDown PORTK &= (~2); DDRH = 0xFF;

// this is *snug*, datasheet says PW_EH must be at least 450ns. (P49 + P58)
// but &= probably implemented as a BCLR instruction (@ 50ns bus, 4 cycles, around 200ns per instruction)
// measured on scope at ~300ns (which would make sense (6 cycles up/down instructions),
// not exactly sure when pin changes state in instruction pair)
// this is actually too short, but appears to work. Either the device is better than expected, or does not match datasheet!
// other LCDs may require a small delay be added to E strobe operations, or data setup time during read.
#define lcd_EUp PORTK |= 1;
#define lcd_EDown PORTK &= (~1);
#define lcd_RSUp PORTK |= 4;
#define lcd_RSDown PORTK &= (~4);

// small delay required on read. LCD timing seems to vary on different devices
// if issues are discovered, increasing __x below should be tested first
#define lcd_MicroDelay { char __x = 1; while (--__x); } // 20MHz Version

// wait for the LCD to be not busy (blocking)
// service function, private
unsigned char lcd_Busy (void) {
    unsigned char inVal = 0;

    lcd_RSDown;
    lcd_RWUp;

    dp {
        lcd_EUp;
        lcd_MicroDelay;

        inVal = PTH;
        lcd_EDown
    }
    while (inVal & 0x80);

    return inVal;
}