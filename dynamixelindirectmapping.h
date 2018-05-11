#include "Trash80_Dynamixel.h"

#ifndef __TRASH80_DYNAMIXEL_INDIRECTMAP__
#define __TRASH80_DYNAMIXEL_INDIRECTMAP__

__TRASH80_DYNAMIXEL_NAMESPACE_BEGIN__
class IndirectMapping {
    public:
        void init(uint16_t _start_address, uint16_t _start_data_address);
        bool add(uint16_t address, uint8_t size);
        void clear();

        uint16_t map_address[64];
        uint8_t map_address_size[64];
        uint16_t map_address_table[128];
        uint8_t buffer[128];
        uint8_t index;
        uint8_t size;
        uint16_t start_address;
        uint16_t start_data_address;

    private:
        uint16_t * _map_address_table;
};
__TRASH80_DYNAMIXEL_NAMESPACE_END__

#endif
