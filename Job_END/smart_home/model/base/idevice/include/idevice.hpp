#pragma once
#include <string>

namespace smart_home {
 
enum class DeviceStatus {
    ONLINE,
    OFFLINE
};   
    
// Базовый интерфейс устройства
class IDevice {
public:
    virtual ~IDevice() = default;
    virtual std::string getId() const = 0;
    virtual std::string getName() const = 0;
    virtual bool isOnline() const = 0;
    virtual void setStatus(DeviceStatus online) = 0;
    virtual DeviceStatus getStatus() const = 0;
};

} // namespace device