#ifndef  CAR_H_
#define  CAR_H_
#include <Arduino.h>
#include <Servo.h>
#include "Motor.h"

#define SERVO_PITCH A3
#define SERVO_ROLL A4

class Car
{
  public:
    Car()
    {
    }
    Car(String name)
    {
      this->name = name;
    }
    void setupDefault()
    {
      this->pitchServo.attach(SERVO_PITCH);  // attaches the servo on D5 to the servo object
      this->rollServo.attach(SERVO_ROLL);  // attaches the servo on pin 9 to the servo object
      this->leftFront.attach(2, 3); // A
      this->rightFront.attach(4, 5); // B
      this->leftBack.attach(7, 6); // C
      this->rightBack.attach(9, 8); // D
    }
    
    void forward();
    void backward();
    void leftTurn(int mode = 0); // mode :  0 centor , 1 front , -1 back
    void rightTurn(int mode = 0);
    
    void stop();
    void setPitchPosition(int pos);
    void setRollPosition(int pos);
    int readPitchPosition();
    int readRollPosition();
    
    Servo pitchServo;  // create servo object to control the pitch servo
    Servo rollServo;  // create servo object to control the roll servo
    Motor leftFront, rightFront, leftBack, rightBack; // A B C D
  private:
    String name = "";
};

#endif
