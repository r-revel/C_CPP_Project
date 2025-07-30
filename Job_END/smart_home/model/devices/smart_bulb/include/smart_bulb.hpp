#pragma once

#include <string>
#include <memory>
#include <stdexcept>
#include <idevice.hpp>
#include <device.hpp>
#include <iactive_device.hpp>

namespace smart_home {

// Умная лампочка (Device + IActiveDevice)
class SmartBulb : public Device, public IActiveDevice {
public:
    SmartBulb(const std::string& id, const std::string& name); 
    
    // IActiveDevice
    bool isActive() const override;
    void activate() override;
    void deactivate() override;

private:
    bool active_;
};

} // namespace smart_home
