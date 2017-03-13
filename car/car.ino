// car

#include "car.h"

Car theCar;
bool pitch_p;
bool pitch_n;
bool roll_p;
bool roll_n;

void setup()
{
  theCar.setupDefault();
  theCar.setRollPosition(90);
  theCar.setPitchPosition(90);
  pitch_p = false;
  pitch_n = false;
  roll_p = false;
  roll_n = false;
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop()
{
  if (pitch_p)
    theCar.setPitchPosition((theCar.readPitchPosition() + 1));
  else if (pitch_n)
  {
    if(!((theCar.readRollPosition()<50 || theCar.readRollPosition()>122) && theCar.readPitchPosition()< 105) && theCar.readPitchPosition()> 90)
      theCar.setPitchPosition((theCar.readPitchPosition() - 1));
  }

  if (roll_p)
  {
    if(!(theCar.readPitchPosition() < 105 && theCar.readRollPosition() >= 122))
      theCar.setRollPosition(theCar.readRollPosition() + 1);
  }
  else if (roll_n)
  {
    if(!(theCar.readPitchPosition() < 105 && theCar.readRollPosition() <= 50 ))
      theCar.setRollPosition(theCar.readRollPosition() - 1);
  }

  delay(15);                       // waits 15ms for the servo to reach the position
}

void serialEvent() {
  byte cmd = Serial.read();
  switch (cmd & 0x0f)
  {
    case 0x00:
      theCar.stop();
      break;
    case 0x01:
      theCar.forward();
      break;
    case 0x02:
      theCar.backward();
      break;
    case 0x04:
      theCar.leftTurn(0);
      break;
    case 0x08:
      theCar.rightTurn(0);
      break;
    case (0x04 | 0x01):
      theCar.leftTurn(1);
      break;
    case (0x04 | 0x02):
      theCar.leftTurn(-1);
      break;
    case (0x08 | 0x01):
      theCar.rightTurn(1);
      break;
    case (0x08 | 0x02):
      theCar.rightTurn(-1);
      break;
    default:
      theCar.stop();
  }

  switch (cmd & 0xf0)
  {
    case 0x10:
      pitch_p = true;
      break;
    case 0x20:
      pitch_n = true;
      break;
    case 0x40:
      roll_p = true;
      break;
    case 0x80:
      roll_n = true;
      break;
    default:    
      pitch_p = false;
      pitch_n = false;
      roll_p = false;
      roll_n = false;
  }
}
