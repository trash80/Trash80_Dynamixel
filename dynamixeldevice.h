
#include "Trash80_Dynamixel.h"
#include "dynamixelstream.h"
#include "dynamixelindirectmapping.h"

#ifndef __TRASH80_DYNAMIXEL_DEVICE__
#define __TRASH80_DYNAMIXEL_DEVICE__

__TRASH80_DYNAMIXEL_NAMESPACE_BEGIN__

class Device {
    public:
        uint8_t id;
        uint8_t control_table[147];
        bool connected;
        bool transmitEnable;

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

        virtual uint16_t getModelNumber() { return 0; };
        virtual uint32_t getModelInformation() { return 0; };
        virtual uint8_t getVersionOfFirmware() { return 0; };
        virtual uint8_t getId() { return 0; };
        virtual uint8_t getBaudRate() { return 0; };
        virtual uint8_t getReturnDelayTime() { return 0; };
        virtual uint8_t getDriveMode() { return 0; };
        virtual uint8_t getOperatingMode() { return 0; };
        virtual uint8_t getSecondaryId() { return 0; };
        virtual uint8_t getProtocolVersion() { return 0; };
        virtual uint32_t getHomingOffset() { return 0; };
        virtual uint32_t getMovingThreshold() { return 0; };
        virtual uint8_t getTemperatureLimit() { return 0; };
        virtual uint16_t getMaxVoltageLimit() { return 0; };
        virtual uint16_t getMinVoltageLimit() { return 0; };
        virtual uint16_t getPwmLimit() { return 0; };
        virtual uint16_t getCurrentLimit() { return 0; };
        virtual uint32_t getAccelerationLimit() { return 0; };
        virtual uint32_t getVelocityLimit() { return 0; };
        virtual uint32_t getMaxPositionLimit() { return 0; };
        virtual uint32_t getMinPositionLimit() { return 0; };
        virtual uint8_t getShutdown() { return 0; };
        virtual uint8_t getTorqueEnable() { return 0; };
        virtual uint8_t getLed() { return 0; };
        virtual uint8_t getStatusReturnLevel() { return 0; };
        virtual uint8_t getRegisteredInstruction() { return 0; };
        virtual uint8_t getHardwareErrorStatus() { return 0; };
        virtual uint16_t getVelocityIGain() { return 0; };
        virtual uint16_t getVelocityPGain() { return 0; };
        virtual uint16_t getPositionDGain() { return 0; };
        virtual uint16_t getPositionIGain() { return 0; };
        virtual uint16_t getPositionPGain() { return 0; };
        virtual uint16_t getFeedforward2ndGain() { return 0; };
        virtual uint16_t getFeedforward1stGain() { return 0; };
        virtual uint8_t getBusWatchdog() { return 0; };
        virtual uint16_t getGoalPwm() { return 0; };
        virtual uint16_t getGoalCurrent() { return 0; };
        virtual uint32_t getGoalVelocity() { return 0; };
        virtual uint32_t getProfileAcceleration() { return 0; };
        virtual uint32_t getProfileVelocity() { return 0; };
        virtual uint32_t getGoalPosition() { return 0; };
        virtual uint16_t getRealtimeTick() { return 0; };
        virtual uint8_t getMoving() { return 0; };
        virtual uint8_t getMovingStatus() { return 0; };
        virtual uint16_t getPresentPwm() { return 0; };
        virtual uint16_t getPresentCurrent() { return 0; };
        virtual uint32_t getPresentVelocity() { return 0; };
        virtual uint32_t getPresentPosition() { return 0; };
        virtual uint32_t getVelocityTrajectory() { return 0; };
        virtual uint32_t getPositionTrajectory() { return 0; };
        virtual uint16_t getPresentInputVoltage() { return 0; };
        virtual uint8_t getPresentTemperature() { return 0; };

        virtual bool setModelNumber(uint16_t value) { return false; };
        virtual bool setModelInformation(uint32_t value) { return false; };
        virtual bool setVersionOfFirmware(uint8_t value) { return false; };
        virtual bool setId(uint8_t value) { return false; };
        virtual bool setBaudRate(uint8_t value) { return false; };
        virtual bool setReturnDelayTime(uint8_t value) { return false; };
        virtual bool setDriveMode(uint8_t value) { return false; };
        virtual bool setOperatingMode(uint8_t value) { return false; };
        virtual bool setSecondaryId(uint8_t value) { return false; };
        virtual bool setProtocolVersion(uint8_t value) { return false; };
        virtual bool setHomingOffset(uint32_t value) { return false; };
        virtual bool setMovingThreshold(uint32_t value) { return false; };
        virtual bool setTemperatureLimit(uint8_t value) { return false; };
        virtual bool setMaxVoltageLimit(uint16_t value) { return false; };
        virtual bool setMinVoltageLimit(uint16_t value) { return false; };
        virtual bool setPwmLimit(uint16_t value) { return false; };
        virtual bool setCurrentLimit(uint16_t value) { return false; };
        virtual bool setAccelerationLimit(uint32_t value) { return false; };
        virtual bool setVelocityLimit(uint32_t value) { return false; };
        virtual bool setMaxPositionLimit(uint32_t value) { return false; };
        virtual bool setMinPositionLimit(uint32_t value) { return false; };
        virtual bool setShutdown(uint8_t value) { return false; };
        virtual bool setTorqueEnable(uint8_t value) { return false; };
        virtual bool setLed(uint8_t value) { return false; };
        virtual bool setStatusReturnLevel(uint8_t value) { return false; };
        virtual bool setRegisteredInstruction(uint8_t value) { return false; };
        virtual bool setHardwareErrorStatus(uint8_t value) { return false; };
        virtual bool setVelocityIGain(uint16_t value) { return false; };
        virtual bool setVelocityPGain(uint16_t value) { return false; };
        virtual bool setPositionDGain(uint16_t value) { return false; };
        virtual bool setPositionIGain(uint16_t value) { return false; };
        virtual bool setPositionPGain(uint16_t value) { return false; };
        virtual bool setFeedforward2ndGain(uint16_t value) { return false; };
        virtual bool setFeedforward1stGain(uint16_t value) { return false; };
        virtual bool setBusWatchdog(uint8_t value) { return false; };
        virtual bool setGoalPwm(uint16_t value) { return false; };
        virtual bool setGoalCurrent(uint16_t value) { return false; };
        virtual bool setGoalVelocity(uint32_t value) { return false; };
        virtual bool setProfileAcceleration(uint32_t value) { return false; };
        virtual bool setProfileVelocity(uint32_t value) { return false; };
        virtual bool setGoalPosition(uint32_t value) { return false; };
        virtual bool setRealtimeTick(uint16_t value) { return false; };
        virtual bool setMoving(uint8_t value) { return false; };
        virtual bool setMovingStatus(uint8_t value) { return false; };
        virtual bool setPresentPwm(uint16_t value) { return false; };
        virtual bool setPresentCurrent(uint16_t value) { return false; };
        virtual bool setPresentVelocity(uint32_t value) { return false; };
        virtual bool setPresentPosition(uint32_t value) { return false; };
        virtual bool setVelocityTrajectory(uint32_t value) { return false; };
        virtual bool setPositionTrajectory(uint32_t value) { return false; };
        virtual bool setPresentInputVoltage(uint16_t value) { return false; };
        virtual bool setPresentTemperature(uint8_t value) { return false; };

        Device(){};

        void begin(Stream & s, uint8_t device_id);
        void update();

        void enableTransmit()
        {
            transmitEnable = true;
        };

        void disableTransmit()
        {
            transmitEnable = false;
        };

        uint32_t getValue(uint16_t i) { return getValue(i,1); };
        uint32_t getValue(uint16_t, uint8_t);
        bool setValue(uint16_t,uint8_t);
        bool setValue(uint16_t,uint16_t);
        bool setValue(uint16_t,uint32_t);

        bool getTableData(uint16_t address, uint8_t * buffer, uint16_t size);
        bool setTableData(uint16_t address, uint8_t * buffer, uint16_t size);
        void setInternalTableData(uint16_t address, uint8_t * buffer, uint16_t size);

        bool setIndirectMapping(IndirectMapping * map);
        bool getIndirectData();
        
        bool isConnected() { return connected; };

        uint8_t addressSize(uint16_t address) {
          return 0;
        };
    protected:
        Stream * stream;
        IndirectMapping * indirectMap;
        bool confirmWrite();
        uint32_t getMessageTimeout(uint32_t baud, uint8_t length);

};

__TRASH80_DYNAMIXEL_NAMESPACE_END__
#endif
