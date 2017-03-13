#include <Arduino.h>

#include "Motor.h"

void Motor::attach(int pin1, int pin2)
{
  this->pin1 = pin1;
  this->pin2 = pin2;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  this->stop();
}

void Motor::detach()
{
  this->pin1 = -1;
  this->pin2 = -1;
}

void Motor::forward()
{
  digitalWrite(this->pin1, HIGH);
  digitalWrite(this->pin2, LOW);
}

void Motor::backward()
{
  digitalWrite(this->pin1, LOW);
  digitalWrite(this->pin2, HIGH);
}
void Motor::stop()
{
  digitalWrite(this->pin1, HIGH);
  digitalWrite(this->pin2, HIGH);
}
void Motor::revertDirection()
{
  int tmp = this->pin1;
  this->pin1 = this->pin2;
  this->pin2 = tmp;
}
