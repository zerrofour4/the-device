
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
#include <Servo.h>


/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
Servo myservo;


const byte address[6] = "00001"; 


void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  myservo.attach(9);
  
  Serial.begin(57600);
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, address);
  radio.startListening();
}


void loop() {
   static int joy_sticks[4];
      
    radio.startListening();
    if( radio.available()){
      while (radio.available()) {
          radio.read( &joy_sticks, sizeof(joy_sticks));
      }
    }

    
    
} 
