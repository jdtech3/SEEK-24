#include <Arduino.h>
#include <SoftwareSerial.h>

#include "pins.hpp"
#include "chassis.hpp"
#include "bt.hpp"

// Chassis robot(PIN_MOTOR_L_IN1, PIN_MOTOR_L_IN2, PIN_MOTOR_L_EN, PIN_MOTOR_R_IN1, PIN_MOTOR_R_IN2, PIN_MOTOR_R_EN);
// SoftwareSerial bt(7, 8);    // RX, TX

void setup() {
    bt_setup();
    // Serial.begin(9600);
    // bt.begin(9600);
}

void loop() {
    bt_loop();
    // if (Serial.available()) bt.write(Serial.read());
    // if (bt.available()) {
    //     char c = bt.read();
    //     Serial.write(c);
        
    //     switch (c) {
    //         case 'w':
    //             robot.forward(200);
    //             break;
    //         case 's':
    //             robot.backward(200);
    //             break;
    //         case 'a':
    //             robot.turnLeft(200);
    //             break;
    //         case 'd':
    //             robot.turnRight(200);
    //             break;
    //         default:
    //             robot.stop();
    //     }
    // }
}
