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
Device::Device(std::string id, std::string name)
    : id_(std::move(id)), name_(std::move(name)) {
    validateId(id_);
    validateName(name_);
}

// Геттеры
std::string Device::getId() const {
    return id_;
}

std::string Device::getName() const {
    return name_;
}

bool Device::isOnline() const {
    return status_ == DeviceStatus::ONLINE;
}

DeviceStatus Device::getStatus() const noexcept {
    return status_;
}

void Device::setStatus(DeviceStatus status) {
    status_ = status;
}

std::string Device::toString() const {
    std::ostringstream oss;
    oss << "Device [ID: " << id_
        << ", Name: " << name_
        << ", Status: " << (isOnline() ? "Online" : "Offline") << "]";
        // << ", Type: " << getType() << "]";
    return oss.str();
}

} // namespace smart_home