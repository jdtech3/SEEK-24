#include <Arduino.h>

#include "bt.hpp"
#include "pins.hpp"

// Credits: slightly modified version of:
//      https://github.com/rsx-utoronto/SEEK/blob/main/starter_code/basic_driving_w_bt_red/basic_driving_w_bt_red.ino

/* Bluetooth Interfacing with Arduino to drive a rover.


     This code allows users onwindows devices to controll their robots.

     joystick values: abcdefg

     abc are from 0-360 and represent the angle in cartesian coordinates.
     def are from 0-100 and represent how far the stick is from the center
     position. g is the push button with 0 indicating no button pressed and int
     between 1 and 4 indicating that buttons 1-4 are pressed.

     Windows:

     Bellow is linked the app that you must use to controll your robot.
     https://apps.microsoft.com/store/detail/universal-bluetooth-pad/9NBLGGH2PL8B
     It has the same functionallity as the other app only includes an additional
     slider which can be usefull for servo controll.

     A quirk of the Windows app include that the channel wont be sent untill
     either the joystick, or slider have been moved. It is also important to
     select both the "Text" and "Channel" boxes (found on the right hand side)
     before data can be sent.

     ***IMPORTANT NOTES***: When using the Windows app you must give it '/n' as
     its input. You must also unplug the the bluetooth modules TX and RX wires
     from the arduino when uploading code since it wont upload with the bluetooth
     module plugged in (power and ground hoever can stay connected).

*/

//_________________________________________________Your Input Goes
//Below____________________________________________________________________________
// Here the pin values used for motor control are established.

//__________________________________________________Your Input Goes
//Above____________________________________________________________________________

void GetBTCommand(char, float*);  // Outputs a list containing the raw controller inputs.
                                            // This function is given a list pointer, and a character
                                            // teling it which app is being used.
void BluetoothPadTranslateCommand(float*, String);  // Gets used by GetBTCommand() when '\n'
                                                                            // is sent as an input. This function
                                                                            // decodes the string message and fills
                                                                            // the "TranslatedCommand" list.
void SimpleMapInput(float*, float*);  // A pre write function That takes in TransatedCommand
                                                // as an imput. It uses the Angle and Power inputs
                                                // (first 2 indexes of the input list) and output both
                                                // motor speed and direction information for the left
                                                // and right motors.
void ExecuteCommand_L298N(float*);  // Takes in a 4 element list (Left Direction,
                                                            // Right Direction, Left Speed, Right Speed) and
                                                            // applies the correct outputs to the 6 pins used
                                                            // to drive the motors. (these pins are determined
                                                            // by you at the begining of the code)
BT::BT(int rx_pin, int tx_pin) {
    _rx_pin = rx_pin;
    _tx_pin = tx_pin;
}

float ControllerInput[8];  // Angle, speed, slider value, channel 0-3 (Windows)
float MotorOutputs[4];     // Left Direction, Right Direction, Left Speed, Right
                                                     // Speed.

// The setup function variables can be given initial values (although you can do
// that when declaring the variable too) and where pins are given their desired
// type. This function only runs once at the begining and can should be where
// you declare what pins will be used for things like servos and sensors.
void bt_setup() {
    Serial.begin(9600);
}

//___________________________________________________YOUR CODE GOES
//BELOW___________________________________________________________________________

void bt_loop() {
    GetBTCommand('\n', ControllerInput);  // '\n' for Windows
    SimpleMapInput(MotorOutputs, ControllerInput);
    ExecuteCommand_L298N(MotorOutputs);
}

//____________________________________________________YOUR CODE GOES
//ABOVE____________________________________________________________________________
/*
    Using the variables "ControllerInput" and the '\n' (Windows) characters,
    GetBTCommand() should be called first to get the raw controller inputs. The 2
    conficurations you will use are:

    GetBTCommand('\n', ControllerInput); (Windows)

    This fuction bassically fills the "ControllerImput" list. This list has 8
    indexes split up in the followig way:

    Windows: [Joystick Angle, Joystick Distcance from Center, Slider Value,
    Channel 0, Channel 1, Channel 2, Channel 3]

    This list is then used to decide the motor speeds and directions. You have the
    option of using the pre writen function SimpleMapInput() which takes in the
    previously filled list "ControllerInput", and the return list "MotorOutput".
    The function uses the first 2 elements of "ControllerInput" and maps them to
    directio and PWM values for the left and right motors. these 4 values are
    placed in the "MotorOutput" list. An implimentation of this function and a
    breakdown of the output can be seen below:

    SimpleMapInput(MotorOutputs, ControllerInput);

    MotorOutputs = [Left Motor Direction, Right Motor Direction, Left Motor Speed,
    Right Motor Speed]

    If you want the extra challange or want slightly different behaviours, you can
    write your own version of this function but make sure all your hardware is
    working correctly beforehand to avoid complex debugging.

    Once your output has been calculated it is time to apply these states to the
    pins. This is done by the ExecuteCommand_L298N() function which takes in the
    "MotorOutputs" list. using the speed and direction values stored in the imput
    list, this function applies the desired outputs to the 4 direction pins and 2
    PWM pins. Make sure that you dont change the names of these pins when
    declaring them because the ExecuteCommand_L298N() function references them
    directly.

    This series of events must happen every loop and if done correctly you should
    be able to drive your rover after writing only 3 lines of code!!!

    Note that the buttons and or sliders are free for you to use to add additional
    functionality such as controlling servos and switching between manual control,
    autonomous control and standby modes.

*/

void GetBTCommand(char border, float* ans) {
    char data;            // Variable to store the data
    String Command = "";  // variable to be returned
    while (true) {
        if (Serial.available()) {  // Checks the availability of Serial port
            data = Serial.read();    // Read the data and stores it in variable.
            // Serial.write(data);
            if (data == border) {    // Different commands are separated by # or \n
                                                         // characters. If you read in a # or \n it is clear
                                                         // that a command has just ended.
                BluetoothPadTranslateCommand(ans, Command);
                return;
            } else {
                Command =
                        Command +
                        String(
                                data);  // Append the character to the end of the command string
            }
        }
    }
}

void BluetoothPadTranslateCommand(float* ans, String Input) {
    int X;
    int Y;
    int S;
    int C = Input.substring(0, 1).toInt();
    int start = 2;
    int count = 2;
    int i = 0;

    while (i < 2) {
        count++;

        if (Input.substring(count, count + 1) == ",") {
            if (i == 0) {
                X = Input.substring(start, count).toInt();
                start = count + 1;
                i++;
            } else if (i == 1) {
                Y = Input.substring(start, count).toInt();
                start = count + 1;
                i++;
                S = Input.substring(start, Input.length()).toInt();
            }
        }
    }

    float angle = 180.0 * atan2(Y, X) / 3.14;
    if (Y < 0) {
        angle += 360.0;
    }

    float power = sqrt((X * X) + (Y * Y));
    if (power > 100) {
        power = 100.0;
    }
    power = power * 2.55;

    ans[0] = angle;
    ans[1] = power;
    ans[2] = S;
    for (int i = 3; i < 7; i++) {
        if ((C + 3) == i) {
            ans[i] = 1;
        } else {
            ans[i] = 0;
        }
    }
}

void SimpleMapInput(float* ans, float* Input) {
    float angle = Input[0];
    float power = Input[1];
    int L_direction;
    int R_direction;
    float L_speed;
    float R_speed;

    // define direction for L motor (corrasponds with motor A on the motor driver)
    if (angle <= 180 || angle >= 330) {
        L_direction = 1;
    } else {
        L_direction = 0;
    }

    // define direction for R motor (corrasponds with motor B on the motor driver)
    if (angle <= 200) {
        R_direction = 1;
    } else {
        R_direction = 0;
    }

    // define L speed
    if (angle >= 90 && angle <= 270) {
        L_speed =
                abs(((angle - 90.0) / 90.0) - 1.0) *
                power;  // The angle will range from 90 -> 270 and will output a L_Speed
                                // range of 1 -> -1, multiplied by the the power variable.
    } else if (angle < 90) {
        L_speed =
                (0.5 + (angle / 180.0)) *
                power;  // The angle will range from 0 -> 90 and will output a L_Speed
                                // range of 0.5 -> 1, multiplied by the the power variable.
    } else {
        L_speed = abs(0.7 + (((angle - 360.0) / 90.0) * 1.7)) *
                            power;  // The angle will range from 270 -> 360 and will output a
                                            // L_Speed range of -1 -> 0.5, multiplied by the the power
                                            // variable.
    }

    // define R speed
    if (angle <= 90) {
        R_speed = (angle / 90.0) * power;
    } else if (angle >= 270) {
        R_speed = abs((angle - 360) / 90) * power;
    } else if (angle > 90 && angle < 180) {
        R_speed = (1 - ((angle - 90) / 180)) * power;
    } else {
        R_speed = abs(0.7 - (((angle - 180.0) / 90.0) * 1.7)) * power;
    }

    ans[0] = (L_direction);
    ans[1] = (R_direction);
    ans[2] = (L_speed);
    ans[3] = (R_speed);
}

void ExecuteCommand_L298N(float* Command) {
    // robot._l_motor->setSpeed(Command[2]);
    // robot._r_motor->setSpeed(Command[3]);
    // robot._l_motor->setSpeed(255);
    // robot._r_motor->setSpeed(255);

    // if (Command[0] > 0) {
    //     robot._l_motor->forward();
    // } else {
    //     robot._l_motor->backward();
    // }

    // if (Command[1] > 0) {
    //     robot._r_motor->forward();
    // } else {
    //     robot._r_motor->backward();
    // }
      if(Command[0]>0){
    digitalWrite(PIN_MOTOR_L_IN1, HIGH);
    digitalWrite(PIN_MOTOR_L_IN2, LOW);
  }else{
    digitalWrite(PIN_MOTOR_L_IN2, HIGH);
    digitalWrite(PIN_MOTOR_L_IN1, LOW);
  }

  if(Command[1]>0){
    digitalWrite(PIN_MOTOR_R_IN1, HIGH);
    digitalWrite(PIN_MOTOR_R_IN2, LOW);
  }else{
    digitalWrite(PIN_MOTOR_R_IN2, HIGH);
    digitalWrite(PIN_MOTOR_R_IN1, LOW);
  }
  
  // Next set speed:
//   analogWrite(PIN_MOTOR_L_EN, 100);
//   analogWrite(PIN_MOTOR_R_EN, 100);
  
  analogWrite(PIN_MOTOR_L_EN, Command[2]);
  analogWrite(PIN_MOTOR_R_EN, Command[3]);
}

void BT::init() {}
