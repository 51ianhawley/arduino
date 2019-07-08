#include <Adafruit_NeoPixel.h>
#include "IRremote.h"
#include <LiquidCrystal.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(5, 3, 8, 7, 4, 6);
 //* LCD RS pin to digital pin 5//
 //* LCD Enable pin to digital pin 3//
 //* LCD D4 pin to digital pin 8//
 //* LCD D5 pin to digital pin 7//
 //* LCD D6 pin to digital pin 4//
 //* LCD D7 pin to digital pin 6//
 //* LCD R/W pin to ground
 //* LCD VSS pin to ground
 //* LCD VCC pin to 5V
#define PINONE         12
#define PINTWO         2
int receiver = 9; // Signal Pin of IR receiver to Arduino Digital Pin 11
#ifdef __AVR__
  #include <avr/power.h>
#endif

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
//#define PIN            12
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      120
#define ALLBRIGHTNESS  85
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PINONE, NEO_GRB + NEO_KHZ800);
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PINTWO, // change this to 8 x 8 pixels wide
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  + NEO_MATRIX_PROGRESSIVE + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
int delayval = 0.0000000000001; // delay for half a second
/// The Byte is incorrect as a value.
#define CHANGE (20) // Variable that changes the color for each of the RGB codes red integer, green integer, and blue integer.
//int r = 128, g = 128, b = 128;
int r = 128; // Red RGB initial integer
int g = 128; // Green RGB initial integer
int b = 128; // Blue RGB initial integer
int s = 85; // Light Brightness initial integer
//color = r=128, 128, b=128;



void setup() {
  const uint16_t colors[] = {
  matrix.Color(32, 32, 223), matrix.Color(0, 191, 255), matrix.Color(0, 163, 204) };
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  irrecv.enableIRIn(); // Start the receiver
  pixels.begin();
  matrix.begin();
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Red");
  lcd.print("Green");
  lcd.print("Blue");
  lcd.print("Bright");
}

void loop() {
  //int r = 128;
  //int g = 128;
  //int b = 128;
  //int r = 128, g = 128, b = 128;
  
    
  
  if (irrecv.decode(&results)) { // have we received an IR signal?
    //Serial.println(results.value,HEX);
    //Serial.println(r);
    //Serial.println(b);
    //Serial.println(g);
    //Serial.println(s);
    
    
  switch(results.value) {
  
      case 0xFF30CF: // Red RGB code integer + 20
        Serial.println("1");
        
        r = r+CHANGE;
        
        break;
      case 0xFF42BD: 
        Serial.println("7");    // Red RGB code integer - 20
        
        r = r-CHANGE;
        
        break;
      case 0xFF18E7: 
        Serial.println("2");    // Green RGB code integer + 20
        
        g = g+CHANGE;
        break;
      case 0xFF4AB5: 
        Serial.println("8");   // Green RGB code integer - 20
        g = g-CHANGE;
        
        break;
      case 0xFF7A85: 
        Serial.println("3");   // Blue RGB code integer + 20
        b = b+CHANGE;
        
        break;
      case 0xFF52AD: 
        Serial.println("9");   // Blue RGB code integer - 20
        b = b-CHANGE;
        
        break;
      
      case 0xFF906F:    
        Serial.println("UP");    // Brightness integer + 20
        s = s+CHANGE;
        
        break;
      case 0xFFE01F: 
        Serial.println("DOWN");    // Brightness integer - 20
        s = s-CHANGE;
        
        break;
      
      //case 0xFFA25D:
        //Serial.println("POWER");
        //pixels.
        
 
                
    }

    for(int i=0;i<NUMPIXELS;i++){

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.setBrightness(s);
      matrix.fillScreen(matrix.Color(r, g, b));
      matrix.setBrightness(s);
      delay(delayval); // Delay for a period of time (in milliseconds).
      pixels.show();
      matrix.show();
    }

    
    //delay(500);                  
    irrecv.resume(); // receive the next value
      // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(millis() / 1000);
    lcd.setCursor(0, 1);
    lcd.setCursor(0, 2);
    lcd.setCursor(0, 3);
    lcd.setCursor(1, 1);
    lcd.print(r);
    lcd.setCursor(1, 5);
    lcd.print(g);
    lcd.setCursor(1, 10);
    lcd.print(b);
    lcd.setCursor(1, 13);
    lcd.print(s);
    
     
  }
  
}
