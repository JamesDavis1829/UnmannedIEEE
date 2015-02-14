#include <Adafruit_MotorShield.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#define STEPS 10

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *motor1 = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *motor2 = AFMS.getStepper(200, 1);
void setup(){
  Serial.begin(9600);
  Serial.println("Ready");
  AFMS.begin();
  motor1->setSpeed(20);
  motor2->setSpeed(20);
}
void loop(){
  char input = Serial.read();
  if(input == 'F')
  {
    for(int x = 0; x < STEPS; x++)
    {
      motor1->step(1,BACKWARD,DOUBLE);
      motor2->step(1,BACKWARD,DOUBLE);
    }
  }
  else if(input == 'B')
  {
    for(int x = 0; x < STEPS; x++)
    { 
      motor1->step(1,FORWARD,DOUBLE);
      motor2->step(1,FORWARD,DOUBLE);
    }
  }
  else if(input == 'L')
  {
    for(int x = 0; x < STEPS; x++)
    {
      motor1->step(1,FORWARD,DOUBLE);
      motor2->step(1,BACKWARD,DOUBLE);
    }  
  }
  else if(input == 'R')
  {
    for(int x = 0; x < STEPS; x++)
    {
      motor1->step(1,BACKWARD,DOUBLE);
      motor2->step(1,FORWARD,DOUBLE);
    }
  }  
}

