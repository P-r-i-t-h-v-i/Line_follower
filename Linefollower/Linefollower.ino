#include <AFMotor.h>

#define trig_pin 8 
#define echo_pin 9 
#define RSensor A5 
#define LSensor A4 


AF_DCMotor motorL(3);
AF_DCMotor motorR(4);

const int speed = 80 ;

float duration , distance ; 
void setup() {
  // put your setup code here, to run once:
  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  pinMode(RSensor,INPUT);
  pinMode(LSensor,INPUT);

  motorL.setSpeed(speed);
  motorR.setSpeed(speed);

  stop () ;

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trig_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin,LOW);


  duration = pulseIn(echo_pin,HIGH);
  distance = (duration * 0.343) / 2 ;

  
  if (distance <= 25 ) {
    
    int left_v = analogRead(LSensor);
    int right_v = analogRead(RSensor);

    if (left_v == 1 && right_v == 1)  {
      forward () ;
    }

    else if (left_v == 1 && right_v == 0) {
      right () ;

    }
    else if (left_v == 0 && right_v == 1) {

      left () ;
    }
    else {
      stop () ;
    }
   }
  else {
    stop (); 
  }
  
}
void  forward () {
  motorL.run(FORWARD);
  motorR.run(FORWARD);
}

void right () {
  motorL.run(RELEASE);
  motorR.run(FORWARD);
}

void left () {

  motorL.run(FORWARD);
  motorR.run(RELEASE);
}

void stop () {

  motorL.run(RELEASE);
  motorR.run(RELEASE);
}