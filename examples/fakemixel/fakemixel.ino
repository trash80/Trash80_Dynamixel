#include <Trash80_Dynamixel.h>

#define SERVO_ID 1
#define BAUDRATE 115200
#define TRANSMIT_ENABLE_PIN 2 // Half duplex transmitter pin

Dynamixel::Stream stream(Serial1);
//Dynamixel::Stream stream(Serial);

Dynamixel::ServoDummy servo;

void setup()
{
    Serial.begin(115200);

    Serial1.begin(BAUDRATE);
    if(TRANSMIT_ENABLE_PIN) {
        Serial1.transmitterEnable(TRANSMIT_ENABLE_PIN);
    }

    stream.begin(BAUDRATE);
    servo.begin(stream, SERVO_ID);
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
