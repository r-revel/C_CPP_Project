#pragma once
#include "device.hpp"

namespace smart_home {

class ActiveDevice : public Device {
public:
    ActiveDevice(std::string id, std::string name, DeviceStatus status, bool isActive = false);
    virtual ~ActiveDevice() = default;

    // Реализация абстрактных методов Device
    bool isActive() const override;
    bool isSensor() const override;
    
    // Специфичные методы для активных устройств
    bool getActiveState() const;
    void setActiveState(bool active);
    void toggleState();

    // Сериализация/десериализация
    virtual std::string toString() const;

private:
    bool isActive_;
};

} // namespace smart_home