#ifndef __TRASH80_DYNAMIXEL_SYNC__
#define __TRASH80_DYNAMIXEL_SYNC__

#include "dynamixelstream.h"
#include "dynamixeldevice.h"

__TRASH80_DYNAMIXEL_NAMESPACE_BEGIN__
class Sync {
    public:

        typedef enum
        {
            PING           = 1,    // Ping
            READ           = 2,    // Read
            WRITE          = 3,    // Write
            REG_WRITE      = 4,    // Reg Write
            ACTION         = 5,    // Action
            FACTORY_RESET  = 6,    // Factory Reset
            REBOOT         = 8,    // Reboot
            STATUS         = 85,   // Status(Return)
            SYNC_READ      = 130,  // Sync Read
            SYNC_WRITE     = 131,  // Sync Write
            BULK_READ      = 146,  // Bulk Read
            BULK_WRITE     = 147   // Bulk Write
        } INSTRUCTION;

        Sync(Stream & s) : stream(s) {};

        void clear();
        void add(Device & s);
        void remove(Device & s);
        void beginTransaction();
        void endTransaction();

        void read(uint16_t address, uint8_t length);
        void write(uint16_t address, uint8_t length);
    private:
        Stream & stream;
        Device * devices[128];
        uint8_t device_count;
};
__TRASH80_DYNAMIXEL_NAMESPACE_END__

#endif
