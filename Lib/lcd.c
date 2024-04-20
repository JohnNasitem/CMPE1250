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
//#define lcd_MicroDelay { char __x = 1; while (--__x); } // 20MHz Version

void lcd_Init (void) {
    PTH = 0b00000000;                               //PTH = Port H
    //data bus as outputs for write
    DDRH = 0b11111111;
    //preset RS low (control), R/W low (set to write), EN low (chip not being addressed)
    PORTK &= 0b11111000;
    //active three control lines
    DDRK |= 0b00000111;

    //wait quite a bit longer than 15ms for Vcc to rise to 4.5V
    //2 x 65,536 (16 bit countdown) x 3 cycles (3 clock cycle assembly instruction DBNE) x 125 ns/cycle = 49.152 ms
    //keyword asm means assembly code then ; to end it since its in c
    asm LDD #0;                                 //need a 49.15 ms delay
    asm DBNE D,*;                               //24.576 ms delay
    asm DBNE D,*;                               //done twice to get a 49.15 ms delay

    // 0, 0, 1 (function set of commands), 1 (data: 8-bit (HIGH)), 1 (lines: 2 (High)), 0 (font: 5x8 matrix (LOW)), 0 (dont care), 0 (dont care)
    PTH = 0b00111000;

    //Write a control byte
    PORTK |= 0b00000001;
    //Resting state: first 5 bits are left alone, same as 5 line from start of method
    PORTK &= 0b11111000;

    //11,000 (defined value) x 3 cycles x 125 ns/cycle
    asm LDD #11000;     //need a 4.125 ms delay
    asm DBNE D,*;

    //Strobe control lines again then wait for at least 100us
    //Rs low, R/W low, EB high to write a control
    PORTK |= 0b00000001;
    //Reseting state
    PORTK &= 0b11111000;

    //267 x 3 cycles x 125 ns/cycle = 100 µs
    asm LDD #267;
    asm DBNE D,*;
    
    //Do it again for a third time, flowchart doesnt say to add a delay but microcontroller is faster tha LCD controller so add a delay anyways
    //Rs low, R/W low, EB high to write a control
    PORTK |= 0b00000001;
    //Reseting state
    PORTK &= 0b11111000;

    //267 x 3 cycles x 125 ns/cycle = 100 µs
    asm LDD #267;
    asm DBNE D,*;

    //Same as above but using lcd_Ctrl (Busy is active)
    lcd_Ctrl(0b00111000);

    //Fine tune some settings
    /* Display controls (last 4 bits)
        Display control commands
        Display: HIGH for on
        Cursor: HIGH for on
        Blink: LOW for off
    */
    lcd_Ctrl(0b00001110);

    //Clear display, home position
    lcd_Ctrl(0b00000001);

    /* mode controls (last 3 bits)
        Entry Mode commands
        Inc/Dec: High for increment (to the left)
        Shift: LOW for no display shift
    */
    lcd_Ctrl(0b00000110);
}

void lcd_Ctrl(unsigned char cCommand) {
    //Wait for the Busy Flag to be CLEARED
    while(lcd_Busy() != 0);
    //Put control byte on the bus
    PTH = cCommand;

    //Rs low, R/W low, EB high to write a control
    PORTK |= 0b00000001;
    //Reseting state
    PORTK &= 0b11111000;
}

unsigned char lcd_Busy (void) {
    unsigned char cBusy;

    //data bus as inputs for read;
    DDRH = 0b00000000;

    /* Last 3 bits
        RS: LOW for stats
        R/W: HIGH for read
        EN: HIGH for enable
    */
   PORTK |= 0b00000011;

   //Reseting state
    PORTK &= 0b11111000;

    //Busy Flag is the MSB of the status register
    cBusy = PTH & 0b10000000;

    //data bus returned to outputs for next write
    DDRH = 0b11111111;

    return cBusy;
}

void lcd_Data (unsigned char val) {
    //wait for LCD to not be busy
    while(lcd_Busy() != 0);

    //Writing
    lcd_RWDown
    //Data
    lcd_RSUp

    PTH = val;

    //Rs low, R/W low, EB high to write a control
    PORTK |= 0b0000001;
    //Reseting state
    PORTK &= 0b11111000;
}

void lcd_String (char const * straddr) {
    //Watch for NULL terminator
    while(*straddr != 0)
        //send next character
        lcd_Data(*straddr++);
}

void lcd_Addr (unsigned char addr) {
    //Add a commnand bit for "Set DDRAMM Address"
    addr |= 0b10000000;
    lcd_Ctrl(addr);
}

void lcd_AddrXY (unsigned char iy, unsigned char ix) {
    //Check for invalid pos
    if (ix > 3 || iy > 19) {
        lcd_Addr(0);
    }
    else {
        switch (ix) {
            case 0:
            lcd_Addr(iy);
            break;

            case 1:
            lcd_Addr(iy + 64);
            break;

            case 2:
            lcd_Addr(iy + 20);
            break;

            case 3:
            lcd_Addr(iy + 84);
            break;
        }
    }
}

void lcd_StringXY (unsigned char iy, unsigned char ix, char const * const straddr) {
    lcd_AddrXY(iy, ix);
    lcd_String(straddr);
}

void lcd_DispControl (unsigned char curon, unsigned char blinkon) {
    unsigned char cCommand;
    /* Display controls (last 4 bits)
        Display control commands
        Display: HIGH for on
        Cursor: HIGH for on
        Blink: LOW for off
    */
    cCommand = 0b00001100;

    if (curon) cCommand |= 2;
    if (blinkon) cCommand |= 1;

    lcd_Ctrl(cCommand);
}

void lcd_Clear (void) {\
    //Clear display, home position
    lcd_Ctrl(0b00000001);
}

void lcd_Home (void) {
    lcd_Addr(0);
}