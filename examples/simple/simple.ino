#include <Trash80_Dynamixel.h>

#define SERVO_ID 1
#define BAUDRATE 115200
#define TRANSMIT_ENABLE_PIN 2 // Half duplex transmitter pin 

Dynamixel::Stream stream(Serial1);
//Dynamixel::Stream stream(Serial);

Dynamixel::Servo servo;

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
    }
}

void loop()
{
    // get a value
    int32_t position = servo.getPresentPosition();
    Serial.println(position);

    // set a value
    servo.setLed(1);
    delay(100);
    servo.setLed(0);
    delay(100);
}
