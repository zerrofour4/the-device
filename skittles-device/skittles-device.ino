

#include <SPI.h>
#include "RF24.h"

// INCLUDE LIBRARY
#include <AlignedJoy.h>


#define PIN_JOY1_X   0  
#define PIN_JOY1_Y   1  
#define PIN_JOY2_X   2  
#define PIN_JOY2_Y   3 

int servo_pos = 0;    // variable to store the servo position


/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(9,10);

AlignedJoy joystick_1(PIN_JOY1_X, PIN_JOY1_Y);
AlignedJoy joystick_2(PIN_JOY2_X, PIN_JOY2_Y);

const byte address[6] = "00001"; 




void setup()
{
  Serial.begin(57600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(address);  
  radio.stopListening();
} // setup()

// Read the current position of the encoder and print out when changed.
void loop()
{

 int xPos1 = joystick_1.read(X);
 int yPos1 = joystick_1.read(Y);
 int pwmY1 = map(yPos1, 0, 1023, 0, 255);
 int pwmX1 = map(xPos1, 0, 1023, 0 ,255);

 int xPos2 = joystick_2.read(X);
 int yPos2 = joystick_2.read(Y);
 int pwmY2 = map(yPos2, 0, 1023, 0, 255);
 int pwmX2 = map(xPos2, 0, 1023, 0 ,255);

 int joy_sticks[] = { pwmY1, pwmX1, pwmY2, pwmX2 } ;

 Serial.println();
 if (!radio.write( &joy_sticks, sizeof(joy_sticks) )){
       Serial.println(F("failed, but trying again"));
       delay(10);
     }
      
} // loop ()
// The End
