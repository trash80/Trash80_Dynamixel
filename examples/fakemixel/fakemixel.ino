#include <Trash80_Dynamixel.h>

#define SERVO_ID 1
#define BAUDRATE 115200

Dynamixel::Stream stream(Serial1);
//Dynamixel::Stream stream(Serial);

Dynamixel::DummyServo servo;

void setup()
{
    Serial.begin(115200);

    Serial1.begin(BAUDRATE);
    stream.begin(BAUDRATE);
    servo.begin(stream, SERVO_ID);

    if(!servo.getId()) {
        //Servo is not found
        Serial.println("Servo not detected. Check connection, baudrate, and ID.");
    }
}

void loop()
{
    stream.update();
    if(stream.available()) { // A dynamixel packet has been received
        servo.update(); // parse stream, perform read or writes to our fake dynamixel from the stream
        Serial.print("Fake servo's LED: ");
        Serial.println(servo.getLed());

        // empty the stream since we are done with it.
        stream.empty();
    }
}
