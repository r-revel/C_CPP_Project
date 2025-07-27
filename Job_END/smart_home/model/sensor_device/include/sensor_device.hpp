#pragma once
#include "../device/include/device.hpp"
#include <any>

namespace smart_home {

class SensorDevice : public Device {
public:
    SensorDevice(std::string id, std::string name, DeviceStatus status);
    
    bool isActive() const override;
    bool isSensor() const override;
    
    virtual std::any readValue() const = 0;

protected:
    virtual std::string getValueType() const = 0;
};

} // namespace smart_home