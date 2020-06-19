/*
 * This sample sketch allows you to read and display through the serial
 * line the values of the joystick axes without calibration.
*/
#include <SPI.h>
#include "RF24.h"


//right
#define BRen 6
#define BRin1 5
#define BRin2 4
#define FRen 9
#define FRin1 8
#define FRin2 7 

//left
#define FLen 3
#define FLin1 A3
#define FLin2 A2
 
#define BLen 10
#define BLin1 A4
#define BLin2 A5


const byte address[6] = "00001"; 

RF24 radio(A0,A1);

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, address);
  radio.startListening();

  
  
  pinMode(BRen, OUTPUT);
  pinMode(BLen, OUTPUT);
  pinMode(FRen, OUTPUT);
  pinMode(FLen, OUTPUT);
  
  pinMode(BRin1, OUTPUT);
  pinMode(BRin2, OUTPUT);
  pinMode(FRin1, OUTPUT);
  pinMode(FRin2, OUTPUT);
  
  pinMode(FLin1, OUTPUT);
  pinMode(FLin2, OUTPUT);
  pinMode(BLin1, OUTPUT);
  pinMode(BLin2, OUTPUT);
 
 
 Serial.begin(9600);
 while(!Serial){} 


 
}

void loop() {

    
  int joy_sticks[] = { 135, 135, 135, 135  };
      
  if( radio.available()){
    while (radio.available()) {
        radio.read( &joy_sticks, sizeof(joy_sticks));
   }
   }
   int pwmY = joy_sticks[0];
   int pwmX = joy_sticks[1];
   
    
if (pwmY > 135 || pwmY < 125) {
  Serial.println();
  
 if (pwmY >= 139){
  digitalWrite(FLin1, LOW );
  digitalWrite(FLin2, HIGH );
  
  digitalWrite(FRin1, LOW );
  digitalWrite(FRin2, HIGH );

  digitalWrite(BLin1, LOW );
  digitalWrite(BLin2, HIGH );
  
  digitalWrite(BRin1, LOW );
  digitalWrite(BRin2, HIGH );


 }
 else if ( pwmY <= 125) { 
  digitalWrite(FLin1, HIGH );
  digitalWrite(FLin2, LOW );
  
  digitalWrite(FRin1, HIGH );
  digitalWrite(FRin2, LOW );

  digitalWrite(BLin1, HIGH );
  digitalWrite(BLin2, LOW );
  
  digitalWrite(BRin1, HIGH );
  digitalWrite(BRin2 ,LOW );
  
  
  pwmY = 255 - pwmY ; 
  
 }
}


else if (pwmX > 135 || pwmX < 124) {
   Serial.print(pwmX) ;
   Serial.println();
  //right turn
  if (pwmX > 135){
  digitalWrite(FLin1, LOW );
  digitalWrite(FLin2, HIGH );
  
  digitalWrite(FRin1, HIGH );
  digitalWrite(FRin2, LOW );

  digitalWrite(BLin1, LOW );
  digitalWrite(BLin2, HIGH );
  
  digitalWrite(BRin1, HIGH );
  digitalWrite(BRin2, LOW );
  }
  else if (pwmX <=120 ) {
    digitalWrite(FLin1, HIGH );
    digitalWrite(FLin2, LOW );
  
    digitalWrite(FRin1, LOW );
    digitalWrite(FRin2, HIGH );

    digitalWrite(BLin1, HIGH );
    digitalWrite(BLin2, LOW );
  
    digitalWrite(BRin1, LOW );
    digitalWrite(BRin2, HIGH );
  }    
      
  } else {
      
  digitalWrite(FLin1, LOW );
  digitalWrite(FLin2, LOW );
  
  digitalWrite(FRin1, LOW );
  digitalWrite(FRin2, LOW );

  digitalWrite(BLin1, LOW );
  digitalWrite(BLin2, LOW );
  
  digitalWrite(BRin1, LOW );
  digitalWrite(BRin2, LOW );
    
   }
  

   
 

  analogWrite(BRen, pwmY);
  analogWrite(BLen , pwmY);
  analogWrite(FLen, pwmY);
  analogWrite(FRen , pwmY);

}
 
