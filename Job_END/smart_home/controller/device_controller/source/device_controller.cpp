#include "device_controller.hpp"

namespace smart_home {

void DeviceController::toggleDevice(std::shared_ptr<IActiveDevice> device) {
    if (device->isActive()) {
        device->deactivate();
    } else {
        device->activate();
    }
}

float DeviceController::readSensorValue(std::shared_ptr<ISensorDevice> sensor) {
    return sensor->readValue();
}

std::string DeviceController::getDeviceStatus(std::shared_ptr<IDevice> device) {
    std::string status = "Устройство: " + device->getName() + 
                        " (ID: " + device->getId() + ")\n" +
                        "Статус: " + (device->isOnline() ? "Онлайн" : "Оффлайн");
    
    if (auto activeDev = std::dynamic_pointer_cast<IActiveDevice>(device)) {
        status += "\nРежим: " + std::string(activeDev->isActive() ? "Активен" : "Неактивен");
    }
    
    if (auto sensorDev = std::dynamic_pointer_cast<ISensorDevice>(device)) {
        status += "\nПоказание: " + std::to_string(sensorDev->readValue());
    }
    
    return status;
}

void DeviceController::setDeviceOnlineStatus(std::shared_ptr<IDevice> device, bool online) {
    if (!device) {
        throw std::invalid_argument("Устройство не может быть nullptr");
    }
    DeviceStatus newStatus = online ? DeviceStatus::ONLINE : DeviceStatus::OFFLINE;
    if (device->getStatus() == newStatus) {
        return;
    }
    device->setStatus(newStatus);
    if (newStatus == DeviceStatus::OFFLINE) {
        if (auto activeDev = std::dynamic_pointer_cast<IActiveDevice>(device)) {
            activeDev->deactivate();
        }
    }
}

} // namespace device