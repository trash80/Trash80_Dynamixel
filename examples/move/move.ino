#include <Trash80_Dynamixel.h>

#define SERVO_ID 1
#define BAUDRATE 115200

Dynamixel::Stream stream(Serial1);
//Dynamixel::Stream stream(Serial);

Dynamixel::Servo servo;

/**
* !!!Warning!!! This script will drive a dynamixel, be sure that either the range is within tolerance or the servo is machanically disconnected
*/

int32_t startPosition = 2095;
int32_t maxMovement = 500;
int direction = -1;

void setup()
{
    Serial.begin(115200);
    Serial1.begin(BAUDRATE);
    stream.begin(BAUDRATE);
    servo.begin(stream, SERVO_ID);

    if(!servo.getId()) {
        //Servo is not found
        Serial.println("Servo not detected. Check connection, baudrate, and ID.");
    } else {
        //Enable torque mode
        servo.setTorqueEnable(1);
        servo.setLed(1);
        servo.setGoalPosition(startPosition);
    }
}

void loop()
{
    direction = (position < (startPosition - maxMovement) ) ? 1 : (position > (startPosition + maxMovement) ) ? -1 : direction;

    servo.setGoalPosition(position + (direction * 16));

    // get a value
    int32_t position = servo.getPresentPosition();
    Serial.println(position);

    // set a value
    servo.setLed(1);
    delay(100);
    servo.setLed(0);
    delay(100);
}
