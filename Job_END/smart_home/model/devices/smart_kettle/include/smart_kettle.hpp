#pragma once

#include <string>
#include <memory>
#include <stdexcept>
#include <idevice.hpp>
#include <device.hpp>
#include <isensor_device.hpp>
#include <iactive_device.hpp>

namespace smart_home {

// Умный чайник (Device + IActiveDevice + ISensorDevice)
class SmartKettle : public Device, public IActiveDevice, public ISensorDevice {
public:
    SmartKettle(const std::string& id, const std::string& name);
    bool isActive() const override;
    void activate() override;
    void deactivate() override;
    float readValue() const override;
    void setTemperature(float temp);

private:
    bool active_;
    float temperature_;
};
} // namespace smart_home
