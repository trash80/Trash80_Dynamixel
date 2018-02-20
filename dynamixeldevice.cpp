#include "dynamixeldevice.h"

__TRASH80_DYNAMIXEL_NAMESPACE_BEGIN__

void Device::begin(Stream & s, uint8_t device_id) {
    stream = &s;
    id = device_id;
    transmitEnable = true;
}

void Device::update()
{
    if(stream->available()) {
        if(stream->isSyncWrite()) {
            uint16_t totalsize = (stream->getSize() - 4) * 2;
            uint8_t * d = &stream->message[stream->STREAM_STATE_MESSAGE + 1];
            uint16_t address = *(d++);
            address |= *(d++)<<8;
            uint16_t len = *(d++);
            len |= ((uint16_t)*(d++))<<8;

            while( totalsize-= (len+1) ) {
                if( *(d) == id ) {
                    d++;
                    uint8_t * tab = &control_table[((uint8_t) address&255)];
                    uint16_t l = len;
                    while(l--) *(tab++) = *(d++);
                    break;
                } else {
                    d += len+1;
                }
            }

        } else if(stream->isWrite() && (stream->getId() == id || stream->getId() == 254)) {
            uint16_t l = stream->getSize() - 2;
            uint8_t * d = &stream->message[stream->STREAM_STATE_MESSAGE + 1];
            uint8_t address = *(d++);
            d++;
            uint8_t * tab = &control_table[((uint8_t) address&255)];
            while(l--) *(tab++) = *(d++);

        }
    }
}

uint32_t Device::getValue(uint16_t address, uint8_t size)
{
    if(transmitEnable == false) {
        uint8_t * cp = &control_table[((uint8_t) address&255)];
        if(size == 1) {
            return *(cp);
        } else if(size == 2) {
            uint16_t v = *(cp++);
            return (v | (((uint16_t)*(cp))<<8));
        } else {
            uint32_t v = *(cp++);
            v |= (((uint16_t)*(cp++))<<8);
            v |= (((uint32_t)*(cp++))<<16);
            return (v | (((uint32_t)*(cp))<<24));
        }
    }

    uint8_t tries = 3;
    uint8_t message[5] = {READ, (uint8_t) address, (uint8_t) (address>>8), size, 0x00};
    uint32_t timeout = getMessageTimeout(stream->baud, 5);
    uint32_t currentTime;

    while(tries--) {
        stream->write(id, message, sizeof(message));
        currentTime = micros();
        while((micros() - currentTime) < timeout) {
            while(stream->update()) {
                if(stream->available()) {
                    if(stream->isReturn() && stream->getId() == id) {
                        stream->readBytes(&control_table[((uint8_t) address&255)],size);
                        uint8_t * cp = &control_table[((uint8_t) address&255)];
                        stream->reset();
                        connected = true;
                        if(size == 1) {
                            return *(cp);
                        } else if(size == 2) {
                            uint16_t v = *(cp++);
                            return (v | (((uint16_t)*(cp))<<8));
                        } else {
                            uint32_t v = *(cp++);
                            v |= (((uint16_t)*(cp++))<<8);
                            v |= (((uint32_t)*(cp++))<<16);
                            return (v | (((uint32_t)*(cp))<<24));
                        }
                    }
                    stream->reset();
                }
            }
        }
    }
    connected = false;
    return 0;
}

bool Device::confirmWrite()
{
    if(transmitEnable == false) return true;

    uint8_t tries = 3;
    uint32_t timeout = getMessageTimeout(stream->baud, 5);
    uint32_t currentTime;

    while(tries--) {
        currentTime = micros();
        while((micros() - currentTime) < timeout) {
            while(stream->update()) {
                if(stream->available()) {
                    if(stream->isReturn() && stream->getId() == id) {
                        return (connected = true);
                    }
                }
            }
        }
    }

    return (connected = false);
}

uint32_t Device::getMessageTimeout(uint32_t baud, uint8_t length)
{
    // 9 extra bytes to message (id byte + 16bit length + 4 byte header + 2 byte crc)
    // 10 bits per byte at 1 start bit, 1 stop bit, none parity
    // Servo's responseDelayTime is 250 microseconds by default
    // Added an extra 1000us for processing
    return (((10000000L/baud) + 1) * (length + 9)) + 250 + 4000;
}

bool Device::setValue(uint16_t address, uint8_t value)
{
    uint8_t * cp = &control_table[((uint8_t) address&255)];

    *(cp++) = (uint8_t) value;

    if(transmitEnable == false) return true;

    stream->write(id, address, (uint8_t) value);
    return confirmWrite();
}

bool Device::setValue(uint16_t address, uint16_t value)
{
    uint8_t * cp = &control_table[((uint8_t) address&255)];

    *(cp++) = (uint8_t) value;
    *(cp++) = (uint8_t) (value>>8);

    if(transmitEnable == false) return true;

    stream->write(id, address,  (uint16_t) value);
    return confirmWrite();
}

bool Device::setValue(uint16_t address, uint32_t value)
{
    uint8_t * cp = &control_table[((uint8_t) address&255)];

    *(cp++) = (uint8_t) value;
    *(cp++) = (uint8_t) (value>>8);
    *(cp++) = (uint8_t) (value>>16);
    *(cp) = (uint8_t) (value>>24);

    if(transmitEnable == false) return true;

    stream->write(id, address,  (uint32_t) value);
    return confirmWrite();
}

__TRASH80_DYNAMIXEL_NAMESPACE_END__
