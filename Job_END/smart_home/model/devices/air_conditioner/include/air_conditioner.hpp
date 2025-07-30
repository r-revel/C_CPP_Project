#pragma once

#include <string>
#include <memory>
#include <stdexcept>
#include <idevice.hpp>
#include <device.hpp>
#include <isensor_device.hpp>
#include <iactive_device.hpp>

namespace smart_home {

// Кондиционер (Device + IActiveDevice + ISensorDevice)
class AirConditioner : public Device, public IActiveDevice, public ISensorDevice {
public:
    AirConditioner(const std::string& id, const std::string& name);
    bool isActive() const override;
    void activate() override;
    void deactivate() override;
    float readValue() const override;
    void setTargetTemperature(float temp);

private:
    bool active_;
    float currentTemp_;
    float targetTemp_;
};

} // namespace smart_home
