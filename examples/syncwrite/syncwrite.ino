#include <Trash80_Dynamixel.h>

#define BAUDRATE 115200
#define NUM_SERVOS 2
uint8_t id[NUM_SERVOS] = {1,2};

Dynamixel::Stream stream(Serial1);
//Dynamixel::Stream stream(Serial);

Dynamixel::Sync sync(stream);

Dynamixel::Servo servo[NUM_SERVOS];

void setup()
{
    Serial.begin(115200);
    Serial1.begin(BAUDRATE);
    stream.begin(BAUDRATE);
    for(uint8_t i=0; i != NUM_SERVOS; i++) {
        servo[i].begin(stream, id[i]);
        sync.add(servo[i]);
        if(!servo[i].getId()) {
            //Servo is not found
            Serial.println("Servo not detected. Check connection, baudrate, and ID.");
        }
    }
}

void loop()
{
    sync.beginTransaction();

    for(uint8_t i=0; i != NUM_SERVOS; i++) {
        servo[i].setLed(1);
    }

    sync.write(Dynamixel::Servo::LED);
    delay(100);

    for(uint8_t i=0; i != NUM_SERVOS; i++) {
        servo[i].setLed(0);
    }

    sync.write(Dynamixel::Servo::LED);
    delay(100);

    sync.endTransaction();
}
