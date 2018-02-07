#include "dynamixelstream.h"

__TRASH80_DYNAMIXEL_NAMESPACE_BEGIN__

const uint8_t Stream::PROTOCOL_HEADER_SIZE = 4;
const uint8_t Stream::PROTOCOL_HEADER[4] = {
    255,255,253,0
};

void Stream::begin(uint32_t baud_rate)
{
    serial->flush();
    while(serial->available() && serial->read()) {};
    //if(baud != baud_rate) {
    //    serial->begin(baud_rate);
    //}
    baud = baud_rate;
}

int Stream::available()
{
    return completed;
}

void Stream::reset()
{
    stream_state = STREAM_START;
    completed = false;
}

bool Stream::isActive()
{
    return stream_state != STREAM_START;
}

void Stream::readBytes(uint8_t * buffer, uint8_t length)
{
    memcpy(buffer, &message[STREAM_STATE_MESSAGE+2], length);
    reset();
}

uint8_t Stream::read()
{
    if(!read_counter) return 0;
    read_counter--;
    return *(_read++);
}

uint16_t Stream::read16()
{
    uint16_t d = (uint16_t) read();
    d |= ((uint16_t) read())<<8;
    return d;
}

uint32_t Stream::read32()
{
    uint32_t d = (uint32_t) read();
    d |= ((uint32_t) read())<<8;
    d |= ((uint32_t) read())<<16;
    d |= ((uint32_t) read())<<24;
    return d;
}


uint8_t Stream::getId()
{
    if(!completed) return 0;
    return id;
}

uint16_t Stream::getSize()
{
    if(!completed) return 0;
    return length - 3;
}

bool Stream::update()
{
    if(!serial->available()) return false;
    update(serial->read());
    return true;
}

void Stream::update(uint8_t data)
{
    completed = false;

    if(last_data_time < millis()) {
        stream_state = STREAM_START;
    }
    last_data_time = millis()+5;

    switch(stream_state) {
        case STREAM_START:
            if(data == 255) {
                _message = &message[0];
                *(_message++) = data;
                stream_state = STREAM_HEADER;
            }
            break;
        case STREAM_HEADER:
            if(data == 255) {
                *(_message++) = data;
                stream_state = STREAM_HEADER_ID;
            } else {
                stream_state = STREAM_START;
            }
            break;
        case STREAM_HEADER_ID:
            if(data == 253) {
                *(_message++) = data;
                stream_state = STREAM_HEADER_RESERVE;
            } else if(data == 255) {
                stream_state = STREAM_HEADER;
            } else {
                stream_state = STREAM_START;
            }
            break;
        case STREAM_HEADER_RESERVE:
            if(data == 0) {
                *(_message++) = data;
                stream_state = STREAM_ID;
            } else if(data == 255) {
                stream_state = STREAM_HEADER;
            } else {
                stream_state = STREAM_START;
            }
            break;
        case STREAM_ID:
            if(data < 255) {
                id = data;
                *(_message++) = data;
                stream_state = STREAM_LENGTH1;
            } else {
                stream_state = STREAM_HEADER;
            }
            break;
        case STREAM_LENGTH1:
            *(_message++) = data;
            length = data;
            stream_state = STREAM_LENGTH2;
            break;
        case STREAM_LENGTH2:
            *(_message++) = data;
            length |= (((uint16_t)data)<<8);
            if(length > 250 || !length) {
                stream_state = STREAM_START;
            } else {
                message_counter = length;
                stream_state = STREAM_STATE_MESSAGE;
            }
            break;
        case STREAM_STATE_MESSAGE:
            *(_message++) = data;
            message_counter--;

            if(message_counter == 1) {
                message_crc = data;
            } else if(!message_counter) {
                stream_state = STREAM_START;
                message_crc |= (((uint16_t)data)<<8);
                if(message_crc == getCRC(0, message, length + STREAM_LENGTH1)) {
                    instruction = message[STREAM_STATE_MESSAGE];
                    if(instruction == STATUS) {
                        error    = message[STREAM_STATE_MESSAGE + 1];
                        _read    = &message[STREAM_STATE_MESSAGE + 2];
                        read_counter = length - 4;
                    } else {
                        error    = 0;
                        _read    = &message[STREAM_STATE_MESSAGE + 1];
                        read_counter = length - 3;
                    }
                    completed = true;
                }
            } else if(message_counter == (length - 1)) {
                // instruction
                instruction = data;
            }
    }
}

void Stream::write(const uint8_t * message, size_t length)
{
    uint16_t crc = getCRC(0, PROTOCOL_HEADER, PROTOCOL_HEADER_SIZE);
    crc = getCRC(crc, message, length);

    serial->write(PROTOCOL_HEADER, PROTOCOL_HEADER_SIZE);
    serial->write(message, length);
    serial->write((uint8_t)(crc & 255));
    serial->write((uint8_t)(crc>>8));

    /*
    for(int i=0;i<PROTOCOL_HEADER_SIZE;i++) {
      Serial.print((int) PROTOCOL_HEADER[i]);
      Serial.print(" ");
    }
    for(int i=0;i<length;i++) {
      Serial.print((int) message[i]);
      Serial.print(" ");
    }
    Serial.print((int)(uint8_t)(crc & 255));
    Serial.print(" ");
    Serial.println((int)(uint8_t)(crc>>8));*/
}

void Stream::write(uint8_t id, const uint8_t * message, size_t length)
{
    length += 3;
    uint8_t writeMessage[length];
    uint8_t * wp = &writeMessage[0];

    *(wp++) = id;
    *(wp++) = (uint8_t)((length - 1) & 255);
    *(wp++) = (uint8_t)((length - 1) >> 8);

    memcpy(wp, message, length - 3);
    wp -= 3;

    write(wp, length);
}

void Stream::write(uint8_t id, uint16_t address, const uint8_t * message, size_t length)
{
    length += 6;
    uint8_t writeMessage[length];
    uint8_t * wp = &writeMessage[0];

    *(wp++) = id;
    *(wp++) = (uint8_t)((length - 1) & 255);
    *(wp++) = (uint8_t)((length - 1) >> 8);
    *(wp++) = WRITE;
    *(wp++) = (uint8_t)address;
    *(wp++) = (uint8_t)(address >> 8);
    memcpy(wp, message, length - 6);
    wp -= 6;

    write(wp, length);
}


void Stream::write(uint8_t id, uint16_t address, uint8_t value)
{
    write(id, address, &value, 1);
}

void Stream::write(uint8_t id, uint16_t address, uint16_t value)
{
    uint8_t writeMessage[2];
    uint8_t * wp = &writeMessage[0];
    *(wp++) = (uint8_t)(value & 255);
    *(wp--) = (uint8_t)((value>>8) & 255);
    write(id, address, wp, 2);
}

void Stream::write(uint8_t id, uint16_t address, uint32_t value)
{
    uint8_t writeMessage[4];
    uint8_t * wp = &writeMessage[0];
    *(wp++) = (uint8_t)(value & 255);
    *(wp++) = (uint8_t)((value>>8) & 255);
    *(wp++) = (uint8_t)((value>>16) & 255);
    *(wp) = (uint8_t)((value>>24) & 255);
    wp -= 3;
    write(id, address, wp, 4);
}

uint16_t Stream::getCRC(uint16_t crc, const uint8_t * message, uint8_t length)
{
    while(length--) {
        crc = (crc << 8) ^ crcIndex((((crc >> 8) ^ *(message++)) & 0xFF));
    }
    return crc;
}

__TRASH80_DYNAMIXEL_NAMESPACE_END__
