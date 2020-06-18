/*
 * This sample sketch allows you to read and display through the serial
 * line the values of the joystick axes without calibration.
*/

// INCLUDE LIBRARY
#include <AlignedJoy.h>


#define PIN_JOY1_X   0  
#define PIN_JOY1_Y   1  

//front
#define enA 9
#define Ain1 6
#define Ain2 7
#define enB 10
#define Bin3 11
#define Bin4 12

//rear
#define enC 3
#define Cin1 13
#define Cin2 2
#define enD 5
#define Din3 8
#define Din4 4 

AlignedJoy joystick_1(PIN_JOY1_X, PIN_JOY1_Y);

void setup() {
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
 int xPos = joystick_1.read(X);
 int yPos = joystick_1.read(Y);

 int pwmY = map(yPos, 0, 1023, 0, 255);
 int pwmX = map(xPos, 0, 1023, 0 ,255);
 //Serial.println();

    
if (130 <= pwmX <= 145) {
  Serial.print(pwmY);
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
 
