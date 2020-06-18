/*
 * This sample sketch allows you to read and display through the serial
 * line the values of the joystick axes without calibration.
*/
#include <SPI.h>
#include "RF24.h"


// INCLUDE LIBRARY
#include <AlignedJoy.h>


#define PIN_JOY1_X   0  
#define PIN_JOY1_Y   1  

//front
#define enA 9
#define Ain1 6
#define Ain2 7
#define enB 10
#define Bin3 A2
#define Bin4 A3

//rear
#define enC 3
#define Cin1 A4
#define Cin2 2
#define enD 5
#define Din3 8
#define Din4 4 


const byte address[6] = "00001"; 

AlignedJoy joystick_1(PIN_JOY1_X, PIN_JOY1_Y);
RF24 radio(A0,A1);

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, address);
  radio.startListening();

  
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(enD, OUTPUT);
  
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Bin3, OUTPUT);
  pinMode(Bin4, OUTPUT);
  pinMode(Cin1, OUTPUT);
  pinMode(Cin2, OUTPUT);
  pinMode(Din3, OUTPUT);
  pinMode(Din4, OUTPUT);
 
 
 Serial.begin(9600);
 while(!Serial){} 
}

void loop() {

  int joy_sticks[] = { 125, 125, 125, 125 };
      
  radio.startListening();
  if( radio.available()){
    while (radio.available()) {
        radio.read( &joy_sticks, sizeof(joy_sticks));
   }
   }
   int pwmY = joy_sticks[0];
   int pwmX = joy_sticks[1];
   
    
if (130 <= pwmX <= 145) {
  Serial.print(pwmY);
  Serial.println();
  
 if (pwmY >= 139){
  digitalWrite(Ain1, LOW );
  digitalWrite(Ain2, HIGH );
  digitalWrite(Bin3, LOW );
  digitalWrite(Bin4, HIGH );

  digitalWrite(Cin1, LOW );
  digitalWrite(Cin2, HIGH );
  digitalWrite(Din3, LOW );
  digitalWrite(Din4, HIGH );


 }
 else if ( pwmY <= 125) { 
  digitalWrite(Ain1, HIGH );
  digitalWrite(Ain2, LOW );
  digitalWrite(Bin3, HIGH );
  digitalWrite(Bin4, LOW );

  digitalWrite(Cin1, HIGH );
  digitalWrite(Cin2, LOW );
  digitalWrite(Din3, HIGH );
  digitalWrite(Din4, LOW );
  
  
  pwmY = 255 - pwmY ; 
  
 }
   else if (130 < pwmX > 145) {

  if (pwmX > 145){
    digitalWrite(Ain1, HIGH );
    digitalWrite(Ain2, LOW );
    digitalWrite(Cin1, HIGH );
    digitalWrite(Cin2, LOW );

    digitalWrite(Bin3, HIGH );
    digitalWrite(Bin4, LOW );
    digitalWrite(Din3, HIGH );
    digitalWrite(Din4, LOW );


  }
   } 
   
   
   else {
     
    digitalWrite(Ain1, LOW );
    digitalWrite(Ain2, LOW );
    digitalWrite(Cin1, LOW );
    digitalWrite(Cin2, LOW );

    digitalWrite(Bin3, LOW );
    digitalWrite(Bin4, LOW );
    digitalWrite(Din3, LOW );
    digitalWrite(Din4, LOW );
   

    
  }
 }

  analogWrite(enA, pwmY);
  analogWrite(enB , pwmY);
  analogWrite(enC, pwmY);
  analogWrite(enD , pwmY);

}
 
