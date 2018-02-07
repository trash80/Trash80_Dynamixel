#ifndef __TRASH80_DYNAMIXEL_DUMMYSERVO__
#define __TRASH80_DYNAMIXEL_DUMMYSERVO__

#include "servo.h"

__TRASH80_DYNAMIXEL_NAMESPACE_BEGIN__
class ServoDummy : public Servo {
    public:
        void begin(Stream & s, uint8_t device_id);
        void update();
    protected:
        Stream * stream;
};
__TRASH80_DYNAMIXEL_NAMESPACE_END__
#endif
