

#include <RotaryEncoder.h>
#include <SPI.h>
#include "RF24.h"

int servo_pos = 0;    // variable to store the servo position


/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);

// Setup a RoraryEncoder for pins A2 and A3:
RotaryEncoder encoder(A2, A3);
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
  static int enc_pos = 0;

  encoder.tick();

  int newEncPos = encoder.getPosition();
  if (enc_pos != newEncPos) {
    enc_pos = newEncPos ;
    Serial.println();
    servo_pos = enc_pos ;  
    if ( newEncPos > 160) {
      servo_pos = 160 ; 
    }
    else if (newEncPos < 0) {
      servo_pos = 0 ;
    }
    Serial.print(servo_pos);
    if (!radio.write( &enc_pos, sizeof(int) )){
       Serial.println(F("failed, but trying again"));
       delay(10);
     }
     
    //myservo.write(servo_pos);
    delay(10);
  } // if

} // loop ()
// The End
