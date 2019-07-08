#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>
//#include 
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif
#define PINONE         12 // pin for the NeoPixel Strip
#define PINTWO         2 // pin for the NeoMatrix
LiquidCrystal lcd(5, 3, 8, 7, 4, 6);//Initializes the LCD module.
 //* LCD RS pin to digital pin 5//
 //* LCD Enable pin to digital pin 3//
 //* LCD D4 pin to digital pin 8//
 //* LCD D5 pin to digital pin 7//
 //* LCD D6 pin to digital pin 4//
 //* LCD D7 pin to digital pin 6//
 //* LCD R/W pin to ground
 //* LCD VSS pin to ground
 //* LCD VCC pin to 

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
#define theDelay  100 // The global delay used throughout this sketch/program.
#define NUMPIXELS      120 // Total number of Neopixels of the light strip only.

#define ALLBRIGHTNESS  85 // Brightness used with the light strip.
int delayval = 100; // delay for a tenth of a second for the Light strip.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PINTWO, // change this to 8 x 8 pixels wide
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  + NEO_MATRIX_PROGRESSIVE + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PINONE, NEO_GRB + NEO_KHZ800); // Initializes the NeoPixel Library.
 
void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  const uint16_t colors[] = {
  matrix.Color(32, 32, 223), matrix.Color(0, 191, 255), matrix.Color(0, 163, 204) };
  lcd.begin(20, 4); // Starts the LCD library.
  // Print a message to the LCD
  pixels.begin(); // This initializes the NeoPixel library.
  lcd.print("Random");
  lcd.setCursor(0, 1);
  lcd.print("Combined");
  lcd.setCursor(0, 2);
  lcd.print("Light");  
  matrix.begin(); //Starts the NeoMatrix.
  pixels.begin(); //Starts the NeoPixel Strip.
  matrix.setTextWrap(true);
  matrix.setBrightness(35);
  matrix.setTextColor(colors[0]);
  pinMode(LED_BUILTIN, OUTPUT); //Adjusts the Pinmode to allowing me to know the Arduino is sending commands.
}

//Main Loop that repeats choosing the integer that will be displayed for each red, blue, and green
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1);
  int  randRed = random(0, 255); //Choses random number from 0 to 255 for Red to be put on the light strip/Matrix.
  int  randGreen = random(0, 255); // Choses random number from 0 to 255 for Green to be put on the light strip/Matrix.
  int  randBlue = random(0, 255); // choses random nmber from 0 to 255 for Blue to be put on the light strip/Matrix.
  matrix.fillScreen(matrix.Color(randRed, randGreen, randBlue)); //Fills the entire Neomatrix with a random color.
  matrix.show(); // shows the color on the NeoMatrix.
  delay(theDelay);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1);
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(randRed, randGreen, randBlue)); //Sets the NeoPixel Strip to a color.
    pixels.setBrightness(ALLBRIGHTNESS);
    delay(delayval); // Delay for a period of time (in milliseconds).
    pixels.show();
  
  }
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1);
  
}
