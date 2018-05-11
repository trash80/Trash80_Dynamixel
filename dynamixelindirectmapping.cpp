#include "dynamixelindirectmapping.h"

__TRASH80_DYNAMIXEL_NAMESPACE_BEGIN__

void IndirectMapping::init(uint16_t _start_address, uint16_t _start_data_address)
{
    clear();
    start_address = _start_address;
    start_data_address = _start_data_address;
}


void IndirectMapping::clear()
{
    for(int i=0;i<128;i++) {
        map_address_table[i] = 0;
        buffer[i] = 0;
    }

    for(int i=0;i<64;i++) map_address[i] = 0;
    index = 0;
    size = 0;
    _map_address_table = &map_address_table[0];
}

bool IndirectMapping::add(uint16_t address, uint8_t s)
{
    if(index > 63) return false;

    map_address[index] = address;
    map_address_size[index] = s;
    index += 1;
    size += s;

    uint8_t i = 0;
    while(s--) {
        *(_map_address_table++) = address + (i++);
    }

    return true;
}

__TRASH80_DYNAMIXEL_NAMESPACE_END__
