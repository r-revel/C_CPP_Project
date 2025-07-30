#pragma once

#include <string>
#include <memory>
#include <stdexcept>
#include <idevice.hpp>
#include <device.hpp>
#include <isensor_device.hpp>

namespace smart_home {

// Датчик протечки (Device + ISensorDevice)
class LeakSensor : public Device, public ISensorDevice {
public:
    LeakSensor(const std::string& id, const std::string& name);
    float readValue() const override;
    void setLeakStatus(bool detected);

private:
    bool leakDetected_;
};

} // namespace smart_home
