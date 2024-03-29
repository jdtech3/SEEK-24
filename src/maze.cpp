#include <Arduino.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;  // variable to store the servo position

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
double duration;
double distance;

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

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // clear any previous input
  digitalWrite(trig, LOW);
  delayMicroseconds(2000);

  // set trig pin to HIGH for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // read from the echo pin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // calculate the distance (in cm)
  distance = duration * 0.034 / 2;

  if (distance <= 20) {
    stop();
    for (pos = 0; pos <= 90;
         pos += 1) {       // turn servo carrying ultrasonic sensor right
      myservo.write(pos);  // tell servo to go to position in variable 'pos'
      delay(5);
    }
    // clear any previous input
    digitalWrite(trig, LOW);
    delayMicroseconds(2000);
    // set trig pin to HIGH for 10 microseconds
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    // read from the echo pin, returns the sound wave travel time in
    // microseconds
    duration = pulseIn(echo, HIGH);
    // calculate the distance (in cm)
    distance = duration * 0.034 / 2;
    if (distance <= 20) {
      for (pos = 90; pos >= 0; pos -= 1) {  // turn servo back to 0
        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(5);
      }
      rotateMotors(50, 150);
    } else {
      // turning right is a good route
      // reset servo
      for (pos = 90; pos >= 0; pos -= 1) {  // turn servo back to 0
        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(5);
      }
      // turn right
      rotateMotors(150, 50);
    }
  } else {  // no obstacles
    moveMotors(150);
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
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // Set speeds for each motor
  analogWrite(enA, speedA);
  analogWrite(enB, speedB);
}