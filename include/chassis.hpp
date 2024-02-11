#ifndef __CHASSIS_H
#define __CHASSIS_H

#include <Arduino.h>
#include <L298N.h>

#define DEFAULT_SPEED   255

class Chassis {
    public:
        Chassis(int l_in1_pin, int l_in2_pin, int l_en_pin, int r_in1_pin, int r_in2_pin, int r_en_pin);
        void forward();
        void forward(unsigned short speed);
        void backward();
        void backward(unsigned short speed);
        void turnLeft();
        void turnLeft(unsigned short speed);
        void turnRight();
        void turnRight(unsigned short speed);
        void stop();
    // private:
        int _l_in1_pin, _l_in2_pin, _l_en_pin;
        int _r_in1_pin, _r_in2_pin, _r_en_pin;
        L298N* _l_motor;
        L298N* _r_motor;
};

#endif  // __CHASSIS_H
