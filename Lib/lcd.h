/////////////////////////////////////////////////////////////////////////////
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz (Requires Active PLL)
// Author:        Simon Walker
// Details:       LCD Library
// Revision History :
// Created : Unknown
//  Dec 07 2020 - Modified Documentation
//  Dec    2020 - Modified names, modified to use timer for delays
//  Nov 2021, Added PIT Timer for delays, by Carlos
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////
// 8-Bit interface init on LCD
// LCD is wired to PTH for data, PK0:2 for control :
// 2     1     0     PTK 
// A     R/W*  E     LCD 
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// LCD Address Scheme (HEX):
// 00 01 ... 12 13
// 40 41 ... 52 53
// 14 15 ... 26 27
// 54 55 ... 66 67
////////////////////////////////////////////////////
#define LCD_WIDTH 20
#define LCD_ROW0 0
#define LCD_ROW1 64
#define LCD_ROW2 20
#define LCD_ROW3 84

#define null 0

#define SHIFT_CUR 0
#define SHIFT_SCR (1<<3)

#define lcd_MicroDelay { char __x = 10; while (--__x); } // 20MHz Version
#define lcd_Latch {PORTK_PK0 = 1;lcd_MicroDelay;PORTK_PK0 = 0;}

/////////////////////////////////////////////////////////////////////////////
// Library Prototypes
/////////////////////////////////////////////////////////////////////////////

//Initialize the lcd
void lcd_Init (void);

//Send a byte to PTH
void lcd_Ctrl(unsigned char);

//Checks if the lcd is busy
//Requires to be placed in a blocking delay to be useful
unsigned char lcd_Busy (void);

char lcd_GetAddr(void);                     //not created yet

//Send a byte to lcd
void lcd_Data (unsigned char val);

//Set cursor to a given address
void lcd_Addr (unsigned char addr);

//Set cursor to a given row and column 
void lcd_AddrXY (unsigned char iy, unsigned char ix);

//Send a string to the lcd
void lcd_String (char const * straddr);

void lcdSmartString(char const * straddr, unsigned int delay);                     //not created yet

//Send a string starting at a given row and column to lcd
void lcd_StringXY (unsigned char iy, unsigned char ix, char const * const straddr);

//Control cursor and blink
//curon = curson on
//blinkon = blink on
void lcd_DispControl (unsigned char curon, unsigned char blinkon);

//Clear display and set cursor to addr 0
void lcd_Clear (void);

//Return curcos to addr 0
void lcd_Home (void);

/* Use this to help make the following 2 methods
    mode controls (last 3 bits)
    Entry Mode commands
    Inc/Dec: High for increment (to the left)
    Shift: LOW for no display shift
    lcd_Ctrl(0b00000110);
*/
void lcd_ShiftL (char);                     //not created yet
void lcd_ShiftR (char);                     //not created yet



void lcd_CGAddr (unsigned char addr);                     //not created yet
void lcd_CGChar (unsigned char cgAddr, unsigned const char* cgData, int size);                     //not created yet