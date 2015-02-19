#include <Adafruit_MotorShield.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#define STEPS 10
#define FOLLOW_LINE 'A'
#define STOP_FOLLOWING 'B'
#define RIGHT_TURN 'C'
#define LEFT_TURN 'D'
#define LINE_TOLERANCE 30

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *motor2 = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *motor1 = AFMS.getStepper(200, 1);

int linePinRight = A3;
int linePinLeft = A2;
int sensorValueRight = 0, sensorValueLeft = 0;

void setup(){
  Serial.begin(9600);
  AFMS.begin();
  motor1->setSpeed(20);
  motor2->setSpeed(20);
}
void loop(){ 
  char input = Serial.read();
  Serial.print(input);
  //If the input from the python script is FOLLOW_LINE or STOP_FOLLOWING do whats obvious
  if(input == FOLLOW_LINE)
  {
    while(1)
    {
      input = Serial.read();
      if(input == STOP_FOLLOWING)
      {  
        break;
      }
      stayOnLine();
    }
  }
  if(input == RIGHT_TURN || input == LEFT_TURN)
  {
    if(input == RIGHT_TURN)
    {
      int x = 0;
      turnRobot(x);
    }
    else if(input == LEFT_TURN)
    {
      int x = 1;
      turnRobot(x);
    }
  }
  /*
  sensorValueLeft = analogRead(linePinLeft);
   sensorValueRight = analogRead(linePinRight);
   Serial.println("This is the left");
   Serial.println(sensorValueLeft);
   Serial.println("This is the right");
   Serial.println(sensorValueRight);
   delay(1000);*/
}


//Moves the robot forward
void stayOnLine(){
  //Gets input from the sensors
  sensorValueLeft = analogRead(linePinLeft);
  sensorValueRight = analogRead(linePinRight); 
  //Moves forward within the tolerance
  if(abs(sensorValueLeft - sensorValueRight) < LINE_TOLERANCE)
  {
    for(int x = 0; x < STEPS; x++)
    {
      motor1->step(1,FORWARD,DOUBLE);
      motor2->step(1,FORWARD,DOUBLE);
    }
  }
  //The next two trun based on which sensor is over the black
  else if(sensorValueLeft > sensorValueRight)
  {
    for(int x = 0; x < STEPS; x++)
    {
      motor1->step(1,BACKWARD,DOUBLE);
      motor2->step(1,FORWARD,DOUBLE);
    }
  }
  else if(sensorValueRight > sensorValueLeft)
  {
    for(int x = 0; x < STEPS; x++)
    {
      motor1->step(1,FORWARD,DOUBLE);
      motor2->step(1,BACKWARD,DOUBLE);
    }
  }
}
void turnRobot(int z)
{
  if(z == 1)
  {
    //Left Turn
    for(int x = -60; x < STEPS; x++)
    {
      motor1->step(1,FORWARD,DOUBLE);
      motor2->step(1,BACKWARD,DOUBLE);
      Serial.println("the robot is turning left");
    }
    sensorValueLeft = analogRead(linePinLeft);
    if(sensorValueLeft > LINE_TOLERANCE)
    {
      int min=1000;
      
     do{

        
         Serial.println(min);
        sensorValueLeft = analogRead(linePinLeft);
        if (sensorValueLeft<min)min=sensorValueLeft;
          
        motor1->step(1,FORWARD,DOUBLE);
        motor2->step(1,FORWARD,DOUBLE);
      }while(sensorValueLeft > LINE_TOLERANCE);
      Serial.println("done turning should have found the new line");
     
      return;
    }
  }
  if(z == 0)
  {
    //Right Turn
    for(int x = -60; x < STEPS; x++)
    {
      motor1->step(1,BACKWARD,DOUBLE);
      motor2->step(1,FORWARD,DOUBLE);
    }
    if(sensorValueRight > 50)
    {
      while(sensorValueRight > 50)
      {
        motor1->step(1,FORWARD,DOUBLE);
        motor2->step(1,FORWARD,DOUBLE);
      } 
      return;
    }
  }
}




