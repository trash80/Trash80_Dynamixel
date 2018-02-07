#include "dynamixelsync.h"

__TRASH80_DYNAMIXEL_NAMESPACE_BEGIN__

void Sync::clear()
{
    uint8_t i = 128;
    Device ** device =&devices[0];
    device_count = 0;

    while(i--) {
        *(device) = NULL;
        device++;
    }
}

void Sync::add(Device & s)
{
    uint8_t i = 128;
    Device ** device = &devices[0];
    if(device_count >= 128) return;

    while(i--) {
        if(*(device) == NULL) {
            *(device) = &s;
            device_count++;
            break;
        }
        device++;
    }
}

void Sync::remove(Device & s)
{
    uint8_t i = 128;
    Device ** device =&devices[0];

    while(i--) {
        if((*device)->id == s.id) {
            *(device) = NULL;
            device_count--;
            break;
        }
        device++;
    }
}

void Sync::beginTransaction()
{
    uint8_t i = 128;
    Device ** device =&devices[0];
    while(i--) {
        if(*(device) != NULL) {
            (*device)->transmitEnable = false;
        }
        device++;
    }
}

void Sync::endTransaction()
{
    uint8_t i = 128;
    Device ** device =&devices[0];
    while(i--) {
        if(*(device) != NULL) {
            (*device)->transmitEnable = true;
        }
        device++;
    }
}

void Sync::read(uint16_t address, uint8_t length)
{
    //@TODO implement this
}

void Sync::write(uint16_t address, uint8_t length)
{
    uint8_t message[((device_count * (length+1)) + 5)];
    uint8_t * m = &message[0];

    *(m++) = SYNC_WRITE;
    *(m++) = (uint8_t) address;
    *(m++) = (uint8_t) (address>>8);
    *(m++) = length;
    *(m++) = 0x00;

    uint8_t i = 128;
    Device ** device =&devices[0];
    while(i--) {
        if(*(device) != NULL && (*device)->id != 0) {
            *(m++) = (*device)->id;
            uint8_t * data = &(*device)->control_table[((uint8_t) address&255)];
            uint8_t l = length;
            while(l--) {
                *(m++) = *(data++);
            }
        }
        device++;
    }

    stream.write(254, message, sizeof(message));
}

__TRASH80_DYNAMIXEL_NAMESPACE_END__
