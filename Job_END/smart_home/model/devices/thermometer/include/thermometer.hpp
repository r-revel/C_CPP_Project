#pragma once

#include <string>
#include <memory>
#include <stdexcept>
#include <idevice.hpp>
#include <device.hpp>
#include <isensor_device.hpp>

namespace smart_home {

// Термометр (Device + ISensorDevice)
class Thermometer : public Device, public ISensorDevice {
public:
    Thermometer(const std::string& id, const std::string& name);
    float readValue() const override;
    void setTemperature(float temp);

private:
    float temperature_;
};

} // namespace smart_home
