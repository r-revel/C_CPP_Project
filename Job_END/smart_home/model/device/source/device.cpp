#include "device.hpp"
#include <algorithm>
#include <sstream>

namespace smart_home {

// Валидаторы
void Device::validateId(const std::string& id) const {
    if (id.empty()) {
        throw std::invalid_argument("Device ID cannot be empty");
    }
    
    if (id.find_first_of(" \t\n") != std::string::npos) {
        throw std::invalid_argument("Device ID cannot contain whitespace");
    }
}

void Device::validateName(const std::string& name) const {
    if (name.empty()) {
        throw std::invalid_argument("Device name cannot be empty");
    }
}

// Конструктор
Device::Device(std::string id, std::string name, DeviceStatus status)
    : id_(std::move(id)), name_(std::move(name)), status_(status) {
    validateId(id_);
    validateName(name_);
}

// Геттеры
const std::string& Device::getId() const noexcept {
    return id_;
}

const std::string& Device::getName() const noexcept {
    return name_;
}

DeviceStatus Device::getStatus() const noexcept {
    return status_;
}

void Device::setStatus(DeviceStatus status) noexcept {
    status_ = status;
}

// Методы по умолчанию
std::string Device::getType() const {
    if (isActive() && isSensor()) {
        return "Hybrid";
    } else if (isActive()) {
        return "Active";
    } else if (isSensor()) {
        return "Sensor";
    }
    return "Unknown";
}

std::string Device::toString() const {
    std::ostringstream oss;
    oss << "Device [ID: " << id_
        << ", Name: " << name_
        << ", Status: " << (status_ == DeviceStatus::ONLINE ? "Online" : "Offline")
        << ", Type: " << getType() << "]";
    return oss.str();
}

} // namespace smart_home