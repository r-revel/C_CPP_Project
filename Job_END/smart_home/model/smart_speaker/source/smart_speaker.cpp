#include "smart_speaker.hpp"

namespace smart_home {

SmartSpeaker::SmartSpeaker(const std::string& name, const Room& room) 
    : name_(name), room_(room) {}

std::string SmartSpeaker::getName() const { return name_; }
Room SmartSpeaker::getRoom() const { return room_; }

void SmartSpeaker::addDevice(std::shared_ptr<IDevice> device) {
    devices_.push_back(device);
}

void SmartSpeaker::removeDevice(const std::string& deviceId) {
    devices_.erase(
        std::remove_if(devices_.begin(), devices_.end(),
            [&deviceId](const auto& device) { return device->getId() == deviceId; }
        ),
        devices_.end()
    );
}

std::vector<std::shared_ptr<IDevice>> SmartSpeaker::getDevices() const {
    return devices_;
}

void SmartSpeaker::checkAndRepairDevices() {
    std::cout << "Проверка устройств в колонке '" << name_ << "':\n";
    
    for (const auto& device : devices_) {
        if (!device->isOnline()) {
            std::cout << "⚠ Устройство " << device->getName() << " (ID: " << device->getId() 
                      << ") отключено. Попытка восстановить...\n";    
        }
        
        if (auto sensorDev = std::dynamic_pointer_cast<ISensorDevice>(device)) {
            std::cout << "Датчик " << device->getName() << ": " 
                      << sensorDev->readValue() << "\n";
        }
    }
}

} // namespace smart_home