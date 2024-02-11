#include "chassis.hpp"

Chassis::Chassis(int l_in1_pin, int l_in2_pin, int l_en_pin, int r_in1_pin, int r_in2_pin, int r_en_pin) {
    _l_in1_pin = l_in1_pin;
    _l_in2_pin = l_in2_pin;
    _l_en_pin = l_en_pin;
    _r_in1_pin = r_in1_pin;
    _r_in2_pin = r_in2_pin;
    _r_en_pin = r_en_pin;

    pinMode(_l_in1_pin, OUTPUT);
    pinMode(_l_in2_pin, OUTPUT);
    pinMode(_l_en_pin, OUTPUT);
    pinMode(_r_in1_pin, OUTPUT);
    pinMode(_r_in2_pin, OUTPUT);
    pinMode(_r_en_pin, OUTPUT);

    _l_motor = new L298N(_l_en_pin, _l_in1_pin, _l_in2_pin);
    _r_motor = new L298N(_r_en_pin, _r_in1_pin, _r_in2_pin);
}

void Chassis::forward() {
    forward(DEFAULT_SPEED);
}

void Chassis::forward(unsigned short speed) {
    _l_motor->setSpeed(speed);
    _r_motor->setSpeed(speed);
    _l_motor->forward();
    _r_motor->forward();
}

void Chassis::backward() {
    backward(DEFAULT_SPEED);
}

void Chassis::backward(unsigned short speed) {
    _l_motor->setSpeed(speed);
    _r_motor->setSpeed(speed);
    _l_motor->backward();
    _r_motor->backward();
}

void Chassis::turnLeft() {
    turnLeft(DEFAULT_SPEED);
}

void Chassis::turnLeft(unsigned short speed) {
    _l_motor->setSpeed(speed);
    _r_motor->setSpeed(speed);
    _l_motor->backward();
    _r_motor->forward();
}

void Chassis::turnRight() {
    turnRight(DEFAULT_SPEED);
}

void Chassis::turnRight(unsigned short speed) {
    _l_motor->setSpeed(speed);
    _r_motor->setSpeed(speed);
    _l_motor->forward();
    _r_motor->backward();
}

void Chassis::stop() {
    _l_motor->stop();
    _r_motor->stop();
}

/*

// Define the pins connected to the L298N module
int enA = 9;
int in1 = 8;
int in2 = 12;
int enB = 3;
int in3 = 7;
int in4 = 4;

// Defining input pins from the ultrasonic sensor
const int trig = 10;
const int echo = 11;

// Defining variables for distance calculation
long duration;
int distance;

// declare a boolean variable
boolean hitWallAlr = false;

void setup() {
    // Set the motor control pins as outputs
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    pinMode(trig, OUTPUT);  // sets the trig pin as output
    pinMode(echo, INPUT);   // sets the echo pin as input
    Serial.begin(9600);     // starts the serial communication
}

void loop() {
    // clear any previous input
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    // set trig pin to HIGH for 10 microseconds
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // read from the echo pin, returns the sound wave travel time in microseconds
    duration = pulseIn(echo, HIGH);
    // calculate the distance (in cm)
    distance = duration * 0.034 / 2;

    if (distance <= 20 && !hitWallAlr) {
        stop();
        rotateMotors(250, 100);
        hitWallAlr = !hitWallAlr;
    } else if (distance <= 30 && hitWallAlr) {
        stop();
        rotateMotors(100, 250);
        hitWallAlr = !hitWallAlr;
    } else {
        moveMotors(200);
    }
}

void moveMotors(int speed) {
    // Move both motors forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Set the speed for both motors
    analogWrite(enA, speed);
    analogWrite(enB, speed);
}



void rotateMotors(int speedA, int speedB) {
    // Rotate motors in opposite directions to achieve rotation
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Set speeds for each motor
    analogWrite(enA, speedA);
    analogWrite(enB, speedB);
}
*/
