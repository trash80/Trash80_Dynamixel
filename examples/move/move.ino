#include <Trash80_Dynamixel.h>

#define SERVO_ID 1
#define BAUDRATE 115200
#define TRANSMIT_ENABLE_PIN 2 // Half duplex transmitter pin 

Dynamixel::Stream stream(Serial1);
//Dynamixel::Stream stream(Serial);

Dynamixel::Servo servo;

/**
* !!!Warning!!! This script will drive a dynamixel, be sure that either the range is within tolerance or the servo is machanically disconnected
*/

int32_t startPosition = 2095;
int32_t maxMovement = 500;
int direction = -1;
int32_t position;

void setup()
{
    Serial.begin(115200);
    Serial1.begin(BAUDRATE);
    if(TRANSMIT_ENABLE_PIN) {
        Serial1.transmitterEnable(TRANSMIT_ENABLE_PIN);
    }
    
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
        position = startPosition;
    }
}

void loop()
{
    position += (direction * 2);
    direction = (position < (startPosition - maxMovement) ) ? 1 : (position > (startPosition + maxMovement) ) ? -1 : direction;
    
    servo.setGoalPosition(position);

    Serial.println(position);

    // set a value
    servo.setLed((direction + 1) / 2);
    delay(10);
}
