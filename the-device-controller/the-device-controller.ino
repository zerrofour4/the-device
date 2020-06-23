/*
 * This sample sketch allows you to read and display through the serial
 * line the values of the joystick axes without calibration.
*/
#include <SPI.h>
#include "RF24.h"


#define Len 3
#define Lin1 4
#define Lin2 5


#define Ren 9
#define Rin1 8
#define Rin2 10



const byte address[6] = "00001"; 

RF24 radio(A0,A1);

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, address);
  radio.startListening();

  
  
  pinMode(Ren, OUTPUT);
  pinMode(Len, OUTPUT);

  
  pinMode(Lin1, OUTPUT);
  pinMode(Lin2, OUTPUT);
  pinMode(Rin1, OUTPUT);
  pinMode(Rin2, OUTPUT);
 
 
 Serial.begin(9600);
 while(!Serial){} 


 
}

void loop() {
  static int pwm = 0 ;

    
  int joy_sticks[] = { 135, 135, 135, 135  };
  if( radio.available()){
    while (radio.available()) {
        radio.read( &joy_sticks, sizeof(joy_sticks));
   }
   }
   int Y = joy_sticks[0];
   int X = joy_sticks[1];
   
   
    
if (Y > 135 || Y < 125) {
  
 if (Y >= 139){
  digitalWrite(Lin1, HIGH );
  digitalWrite(Lin2, LOW );
  
  digitalWrite(Rin1, HIGH );
  digitalWrite(Rin2, LOW );
  pwm = Y ;
 }
 
 else if ( Y <= 125) { 
  digitalWrite(Lin1, LOW );
  digitalWrite(Lin2, HIGH );
  
  digitalWrite(Rin1, LOW );
  digitalWrite(Rin2, HIGH );

  pwm = 255 - Y ; 
  
 }
}


else if (X > 135 || X < 124) {
   Serial.print(X) ;
   Serial.println();
  //right turn
  if (X > 135){
  digitalWrite(Lin1, LOW );
  digitalWrite(Lin2, HIGH );
  
  digitalWrite(Rin1, HIGH );
  digitalWrite(Rin2, LOW );
  pwm = X;
  }
  else if (X <=120 ) {
    digitalWrite(Lin1, HIGH );
    digitalWrite(Lin2, LOW );
  
    digitalWrite(Rin1, LOW );
    digitalWrite(Rin2, HIGH );
    pwm = 255 - X;

  }    
      
  } else {
      
    pwm = 0;

   }
  

  Serial.print(pwm);
  Serial.println();
  analogWrite(Ren, pwm);
  analogWrite(Len , pwm);
  delay(100);
}
 
