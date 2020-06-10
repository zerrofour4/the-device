// -----
// SimplePollRotator.ino - Example for the RotaryEncoder library.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// More information on: http://www.mathertel.de/Arduino
// -----
// 18.01.2014 created by Matthias Hertel
// -----

// This example checks the state of the rotary encoder in the loop() function.
// The current position is printed on output when changed.

// Hardware setup:
// Attach a rotary encoder with output pins to A2 and A3.
// The common contact should be attached to ground.

#include <RotaryEncoder.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int servo_pos = 0;    // variable to store the servo position

// Setup a RoraryEncoder for pins A2 and A3:
RotaryEncoder encoder(A2, A3);

void setup()
{
  Serial.begin(57600);
  Serial.println("SimplePollRotator example for the RotaryEncoder library.");
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

} // setup()



// Read the current position of the encoder and print out when changed.
void loop()
{
  static int enc_pos = 0;
  encoder.tick();

  int newEncPos = encoder.getPosition();
  if (enc_pos != newEncPos) {
    
    Serial.print(newEncPos);
    enc_pos = newEncPos ;
    Serial.println();
    servo_pos = enc_pos ;  
    if ( newEncPos > 160) {
      servo_pos = 160 ; 
    }
    else if (newEncPos < 0) {
      servo_pos = 0 ;
    }
    myservo.write(servo_pos);
    delay(20);
  } // if
} // loop ()
// The End
