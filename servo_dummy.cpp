#include "servo_dummy.h"

__TRASH80_DYNAMIXEL_NAMESPACE_BEGIN__

void ServoDummy::begin(Stream & s, uint8_t device_id) {
    stream = &s;
    id = device_id;
    transmitEnable = false;
}

void ServoDummy::update()
{
    if(stream->available()) {
        if(stream->isSyncWrite()) {
            int16_t totalsize = (stream->getSize() - 4);
            uint8_t * d = &stream->message[stream->STREAM_STATE_MESSAGE + 1];
            uint16_t address = *(d++);
            address |= *(d++)<<8;
            uint16_t len = *(d++);
            len |= ((uint16_t)*(d++))<<8;

            while( (totalsize-= (len+1)) >= 0 ) {
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

            if(stream->getId() == id) {
                //write ack
                uint8_t message[2];
                message[0] = 0x55;
                message[1] = 0x00;
                stream->write(id, message, sizeof(message));
            }

        } else if(stream->isRead() && (stream->getId() == id)) {
            uint8_t * d = &stream->message[stream->STREAM_STATE_MESSAGE + 1];
            uint8_t address = *(d++);
            d++;
            uint16_t l = *(d++);
            l |= *(d++);
            uint8_t * tab = &control_table[((uint8_t) address&255)];

            uint8_t message[l+2];
            message[0] = 0x55;
            message[1] = 0x00;
            uint8_t * mes = &message[2];
            while(l--) *(mes++) = *(tab++);

            stream->write(id, message, sizeof(message));
        }
    }
}

__TRASH80_DYNAMIXEL_NAMESPACE_END__
