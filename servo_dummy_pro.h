#ifndef __TRASH80_DYNAMIXEL_DUMMYSERVOPRO__
#define __TRASH80_DYNAMIXEL_DUMMYSERVOPRO__

#include "servo_pro.h"

__TRASH80_DYNAMIXEL_NAMESPACE_BEGIN__
class ServoDummyPro : public ServoPro {
    public:
        void begin(Stream & s, uint8_t device_id);
        void update();
    protected:
        Stream * stream;
};
__TRASH80_DYNAMIXEL_NAMESPACE_END__
#endif
