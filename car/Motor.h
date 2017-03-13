#ifndef  MOTOR_H_
#define  MOTOR_H_
#include <Arduino.h>
class Motor
{
  public:
    Motor()
    {
      pin1 = -1;
      pin2 = -1;
    }
    Motor(String name)
    {
      this->name = name;
      pin1 = -1;
      pin2 = -1;
    }
    void attach(int pin1, int pin2); //attach the two pin
    void detach();
    void forward();
    void backward();
    void stop();
    void revertDirection();
  private:
    String name="";
    int pin1;
    int pin2;
};

#endif
