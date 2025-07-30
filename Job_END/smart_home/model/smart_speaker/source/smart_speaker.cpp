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

} // namespace smart_home