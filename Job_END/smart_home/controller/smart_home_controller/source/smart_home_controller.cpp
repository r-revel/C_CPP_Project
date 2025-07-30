#include "smart_home_controller.hpp"

namespace smart_home {

void SmartHomeController::addSpeaker(SmartHome& home, const SmartSpeaker& speaker) {
    home.addSpeaker(speaker);
}

void SmartHomeController::removeSpeaker(SmartHome& home, const std::string& speakerName) {
    home.removeSpeaker(speakerName);
}

SmartSpeaker* SmartHomeController::findSpeaker(SmartHome& home, const std::string& name) {
    return home.findSpeaker(name);
}

void SmartHomeController::listAllDevices(const SmartSpeaker& speaker) {
    std::cout << "Устройства в колонке '" << speaker.getName() << "':\n";
    for (const auto& device : speaker.getDevices()) {
        std::cout << "- " << device->getName() << " (ID: " << device->getId() << ")\n";
    }
}

void SmartHomeController::controlDeviceInSpeaker(SmartSpeaker& speaker, const std::string& deviceId) {
    for (const auto& device : speaker.getDevices()) {
        if (device->getId() == deviceId) {
            if (auto activeDev = std::dynamic_pointer_cast<IActiveDevice>(device)) {
                DeviceController::toggleDevice(activeDev);
                std::cout << "Устройство " << device->getName() << " переключено.\n";
            } else if (auto sensorDev = std::dynamic_pointer_cast<ISensorDevice>(device)) {
                float value = DeviceController::readSensorValue(sensorDev);
                std::cout << "Показание датчика: " << value << "\n";
            }
            return;
        }
    }
    std::cout << "Устройство с ID " << deviceId << " не найдено.\n";
}

} // namespace device