  #include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
//U8GLIB_ST7920_128X64_1X u8g(11, 10, 13);  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
#define ALLBRIGHTNESS  345 // Brightness used with the light strip.
// int intRedCode = 0;
// int intGreenCode = 0;
// int intBlue = 0;
// Create more than one string that can hold variables
// String inString = "";
// string to hold input

//int intRGBCounter = 1;// Holds the iteration for R G B.
//String strRed = "";
//String strGreen = "";
//String strBlue = "";
unsigned int intRed;
unsigned int intGreen;
unsigned int intBlue;
// bool bolDataGood = false;
// byte bytRed = pgm_read_byte(&gamma8[intRed]);
// byte bytGreen = pgm_read_byte(&gamma8[intGreen]);
// byte bytBlue = pgm_read_byte(&gamma8[intBlue]);
char val = Serial.read();
// extern const uint8_t gamma8[];
void setup()
{
  // pinMode(8, OUTPUT);
  //Initialize serial and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  matrix.begin();
  pinMode(LED_BUILTIN, OUTPUT);


  //uint8_t r = 0, g = 0, b = 0;

}
char bytes[64];
int ndx = 0;
bool goodString = false;
bool inString = false;
bool bolGoodData = false;
void loop()
{
  //unsigned int integerValue=0;  // Max value is 65535
  //char incomingByte;
  

  if (Serial.available() > 0)
  {
    char s = Serial.read();
    if ((inString == false) and (s == 'R')) {
      inString = true;
      ndx = 0;
    }
    if (inString) {
      bytes[ndx++] = s;
    }
    if (s == 'E') {
      goodString = true;
      bytes[ndx] = '\0';
      //lcd.println(strlen(bytes));
      Serial.println(bytes);
      inString = false;
    }
    
    //matrix.fillScreen(matrix.Color333(0, 0, 0));
  }

  if (goodString) {
    //extern const uint8_t gamma8[];
    intRed = (bytes[1] - '0') * 100 + (bytes[2] - '0') * 10 + (bytes[3] - '0');
    intGreen = (bytes[5] - '0') * 100 + (bytes[6] - '0') * 10 + (bytes[7] - '0');
    intBlue = (bytes[9] - '0') * 100 + (bytes[10] - '0') * 10 + (bytes[11] - '0');
    matrix.fillScreen(matrix.Color333(intRed >> 5, intGreen >> 5, intBlue >> 5));
    
    delay(1900);
    goodString = false;
    
    
    // byte bytRed = pgm_read_byte(&gamma8[intRed]);
    //byte bytGreen = pgm_read_byte(&gamma8[intGreen]);
    // byte bytBlue = pgm_read_byte(&gamma8[intBlue]);
    // int intRedPostConversion = int(bytRed);
    // int intGreenPostConversion = int(bytGreen);
    // int intBluePostConversion = int(bytBlue);
    // bolDataGood = true;
    //matrix.drawRect(0, 0, 32, 16, matrix.Color333(intRed, intBlue, intGreen));
    //matrix.fillRect(0, 0, 32, 16, matrix.Color333(intRed, intBlue, intGreen));
    //matrix.fillScreen(matrix.Color333(intRed, intGreen, intBlue));
    //delay(10000);


  }
  //matrix.fillScreen(matrix.Color333(intRed, intGreen, intBlue));
  //digitalWrite(LED_BUILTIN, HIGH);
  //delay(160);
  //digitalWrite(LED_BUILTIN, LOW);
  //delay(200);
  //digitalWrite(LED_BUILTIN, HIGH);
  // matrix.drawRect(0, 0, 32, 16, matrix.Color333(intRed, intBlue, intGreen));
 // matrix.fillRect(0, 0, 32, 16, matrix.Color333(intRed, intBlue, intGreen));
//matrix.fillScreen(matrix.Color333(intRed, intGreen, intBlue));
}
