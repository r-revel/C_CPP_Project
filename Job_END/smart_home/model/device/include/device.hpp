#pragma once
#include <string>
#include <memory>
#include <stdexcept>

namespace smart_home {

enum class DeviceStatus {
    ONLINE,
    OFFLINE
};

class Device {
public:
    Device(std::string id, std::string name, DeviceStatus status = DeviceStatus::ONLINE);
    virtual ~Device() = default;

    // Запрет копирования
    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;

    // Основные методы доступа
    const std::string& getId() const noexcept;
    const std::string& getName() const noexcept;
    DeviceStatus getStatus() const noexcept;
    void setStatus(DeviceStatus status) noexcept;

    // Абстрактные методы для определения типа устройства
    virtual bool isActive() const = 0;
    virtual bool isSensor() const = 0;

    // Виртуальные методы (можно переопределить)
    virtual std::string getType() const;
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