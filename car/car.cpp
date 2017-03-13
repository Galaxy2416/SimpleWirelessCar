#include <Arduino.h>

#include "car.h"

void Car::forward()
{
  this->leftFront.forward();
  this->rightFront.forward();
  this->leftBack.forward();
  this->rightBack.forward();
}


void Car::backward()
{
  this->leftFront.backward();
  this->rightFront.backward();
  this->leftBack.backward();
  this->rightBack.backward();
}

void Car::stop()
{
  this->leftFront.stop();
  this->rightFront.stop();
  this->leftBack.stop();
  this->rightBack.stop();
}

void Car::leftTurn(int mode = 0)
{
  if (mode == 0)
  {
    this->leftFront.backward();
    this->rightFront.forward();
    this->leftBack.stop();
    this->rightBack.stop();
  }
  else if(mode == 1)
  {
    this->leftFront.forward();
    this->rightFront.forward();
    this->leftBack.backward();
    this->rightBack.forward();
  }
    else if(mode == -1)
  {
    this->leftFront.backward();
    this->rightFront.backward();
    this->leftBack.backward();
    this->rightBack.forward();
  }
}


void Car::rightTurn(int mode = 0)
{
  if (mode == 0)
  {
    this->leftFront.forward();
    this->rightFront.backward();
    this->leftBack.stop();
    this->rightBack.stop();
  }
  else if (mode == 1)
  {
    this->leftFront.forward();
    this->rightFront.forward();
    this->leftBack.forward();
    this->rightBack.backward();
  }
  else if (mode == -1)
  {
    this->leftFront.backward();
    this->rightFront.backward();
    this->leftBack.forward();
    this->rightBack.backward();
  }
}

void Car::setPitchPosition(int pos)
{
  this->pitchServo.write(pos);
}

void Car::setRollPosition(int pos)
{
  this->rollServo.write(pos);
}

int Car::readPitchPosition()
{
  return this->pitchServo.read();
}

int Car::readRollPosition()
{
  return this->rollServo.read();
}
