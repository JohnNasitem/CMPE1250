/* //Enum to hold tera term color values for escape squences
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
} ColorEscapeValues; */

//returns a random number
//inclusively between iLow and iHighEx - 1
int GetRandom (int iLow, int iHighEx);

/* //Sends a string with a sepcified colour and location
void SendString (char const * stringAdress, char forecolor[], char backcolor[], int xPos, int yPos); */