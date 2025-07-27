#include "active_device.hpp"

namespace smart_home {

ActiveDevice::ActiveDevice(std::string id, std::string name, DeviceStatus status, bool isActive)
    : Device(id, name, status), isActive_(isActive) {}

bool ActiveDevice::isActive() const {
    return true; // Это активное устройство
}

bool ActiveDevice::isSensor() const {
    return false; // Не является сенсором
}

bool ActiveDevice::getActiveState() const {
    return isActive_;
}

void ActiveDevice::setActiveState(bool active) {
    if (getStatus() == DeviceStatus::ONLINE) {
        isActive_ = active;
    }
}

void ActiveDevice::toggleState() {
    if (getStatus() == DeviceStatus::ONLINE) {
        isActive_ = !isActive_;
    }
}

std::string ActiveDevice::toString() const {
    std::string statusStr = (getStatus() == DeviceStatus::ONLINE) ? "Online" : "Offline";
    std::string activeStr = isActive_ ? "Active" : "Inactive";
    
    return "ActiveDevice [ID: " + getId() + 
           ", Name: " + getName() + 
           ", Status: " + statusStr + 
           ", State: " + activeStr + "]";
}

} // namespace smart_home