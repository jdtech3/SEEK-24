#include <Arduino.h>

// Define the pins connected to the L298N module
int enA = 9;
int in1 = 8;
int in2 = 12;
int enB = 3;
int in3 = 7;
int in4 = 4;

// Define input pins for both IR sensors
const int IR_PIN_1 = 13;
const int IR_PIN_2 = 2;

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

void stop() {
  // Stop both motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // Set speed to 0 to stop the motors
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void rotateMotors(int speedA, int speedB) {
  // Rotate motors in opposite directions to achieve rotation
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // Set speeds for each motor
  analogWrite(enA, speedA);
  analogWrite(enB, speedB);
}

void setup() {
  // Set the motor control pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Enable PWM for Motor A and Motor B
  analogWrite(enA, 200);  // Adjust the speed for Motor A as needed
  analogWrite(enB, 200);  // Adjust the speed for Motor B as needed

  // Set the IR sensor pins as inputs
  pinMode(IR_PIN_1, INPUT);
  pinMode(IR_PIN_2, INPUT);
}

void loop() {
  // Read the value from the IR sensors
  int IR_SEN_1 = digitalRead(IR_PIN_1);
  int IR_SEN_2 = digitalRead(IR_PIN_2);

  // Line-tracking control logic
  if (IR_SEN_1 == 0 && IR_SEN_2 == 0) {
    // We are following the line correctly; move both motors at max speed.
    moveMotors(100);
  } else if (IR_SEN_1 == 0 && IR_SEN_2 == 1) {
    // Turn towards IR sensor 2 for a bit
    rotateMotors(200, 0);
  } else if (IR_SEN_1 == 1 && IR_SEN_2 == 0) {
    // Turn towards IR sensor 1 for a bit
    rotateMotors(0, 200);
  } else if (IR_SEN_1 == 1 && IR_SEN_2 == 1) {
    moveMotors(100);
  } else {
    moveMotors(100);
  }
}