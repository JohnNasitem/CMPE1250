//Enum to hold tera term color values for escape squences
typedef enum ColorEscapeValuesTypedef__
{
  CEV_Default   = 39,
  CEV_Black     = 30,
  CEV_Red       = 31,
  CEV_Green     = 32,
  CEV_Yellow    = 33,
  CEV_Blue      = 34,
  CEV_Magenta   = 35,
  CEV_Cyan      = 36,
  CEV_White     = 37
} ColorEscapeValues;

//returns a random number
//inclusively between iLow and iHighEx - 1
int GetRandom (int iLow, int iHighEx);

//Sends a string with a sepcified colour and location
void SendString (char const * stringAdress, ColorEscapeValues forecolor, ColorEscapeValues backcolor, int row, int column);

// take a single ASCII character that looks like HEX and
// convert it to the numerical equivalent
// valid characters are '0'-'9', 'a'-'f', 'A'-'F'
// all other ASCII codes return 0
int ToDigitVal (char digit);

// convert the 4 character ASCII array representation
// into a single 16-bit value
// uses ToDigitVal to convert each position
unsigned int HexArrayToUInt16 (char * pArray);