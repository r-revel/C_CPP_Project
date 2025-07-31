#pragma once

#include <string>
#include <memory>
#include <stdexcept>
#include <idevice.hpp>

namespace smart_home {

class Device : public IDevice {
public:
    Device(std::string id, std::string name);
    virtual ~Device() = default;
    
    // Основные методы доступа
    std::string getId() const override;
    std::string getName() const override;
    void setStatus(DeviceStatus online) override;
    DeviceStatus getStatus() const noexcept;


    bool isOnline() const override;
    
    // Виртуальные методы (можно переопределить)
    virtual std::string toString() const;

protected:
    // Валидация входных данных
    void validateId(const std::string& id) const;
    void validateName(const std::string& name) const;

private:
    std::string id_;
    std::string name_;
    DeviceStatus status_;
};

} // namespace smart_home