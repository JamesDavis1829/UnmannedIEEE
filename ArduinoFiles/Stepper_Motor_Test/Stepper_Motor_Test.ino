#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *motor1 = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *motor2 = AFMS.getStepper(200, 1);
void setup(){
  Serial.begin(9600);
  Serial.println("Stepper test!");
  AFMS.begin();
  motor1->setSpeed(200);
  motor2->setSpeed(200);
}
void loop(){
  Serial.println("Should be running");
  for(int x = 0; x < 100; x++)
  {
    motor1->step(1,BACKWARD,DOUBLE);
    motor2->step(1,BACKWARD,DOUBLE);
  }
  delay(1000);
}
