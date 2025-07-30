#include "smart_home_cli.hpp"


namespace smart_home {

SmartHomeCLI::SmartHomeCLI(SmartHome& home, smart_home::CliView& view) 
: home_(home), view_(view) {}

void SmartHomeCLI::run() {
    bool running = true;
    while (running) {
        view_.show_menu();
        int choice = view_.get_menu_choice();
        
        switch (choice) {
            case 1: listAllSpeakers(); break;
            case 2: showRoomDevices(); break;
            case 3: controlDevice(); break;
            case 4: checkSystemStatus(); break;
            case 5: 
                if (view_.get_confirmation("Are you sure you want to exit?")) {
                    running = false;
                }
                break;
            default:
                view_.show_error("Invalid choice! Please try again.");
                break;
        }
    }
}

void SmartHomeCLI::listAllSpeakers() {
    std::vector<std::pair<std::string, std::string>> speakers;
    for (const auto& speaker : home_.getSpeakers()) {
        speakers.emplace_back(
            speaker.getName(),
            speaker.getRoom().getTypeAsString()
        );
    }
    view_.show_speakers_list(speakers);
    view_.get_input("Press Enter to continue...");
}

void SmartHomeCLI::showRoomDevices() {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> devices;
    
    for (const auto& speaker : home_.getSpeakers()) {
        for (const auto& device : speaker.getDevices()) {
            std::string status = device->isOnline() ? "Online" : "Offline";
            std::string type = "Device";
            
            if (dynamic_cast<IActiveDevice*>(device.get())) {
                type = "Active " + type;
            }
            if (dynamic_cast<ISensorDevice*>(device.get())) {
                type = "Sensor " + type;
            }
            
            devices.emplace_back(
                device->getId(),
                device->getName(),
                status,
                type
            );
        }
    }
    
    view_.show_devices_list(devices);
    view_.get_input("Press Enter to continue...");
}

void SmartHomeCLI::controlDevice() {
    std::string deviceId = view_.get_input("Enter device ID: ");
    if (deviceId.empty()) return;

    for (auto& speaker : home_.getSpeakers()) {
        for (const auto& device : speaker.getDevices()) {
            if (device->getId() == deviceId) {
                if (auto activeDev = std::dynamic_pointer_cast<IActiveDevice>(device)) {
                    bool confirm = view_.get_confirmation(
                        "Turn " + device->getName() + " " + 
                        (activeDev->isActive() ? "OFF?" : "ON?")
                    );
                    if (confirm) {
                        DeviceController::toggleDevice(activeDev);
                        view_.show_message("Device toggled successfully!");
                    }
                } else if (auto sensorDev = std::dynamic_pointer_cast<ISensorDevice>(device)) {
                    float value = DeviceController::readSensorValue(sensorDev);
                    view_.show_message(
                        "Sensor value: " + std::to_string(value)
                    );
                } else {
                    view_.show_error("This device cannot be controlled.");
                }
                return;
            }
        }
    }
    view_.show_error("Device not found!");
}

void SmartHomeCLI::checkSystemStatus() {
    int totalDevices = 0;
    for (const auto& speaker : home_.getSpeakers()) {
        totalDevices += speaker.getDevices().size();
    }
    
    view_.show_message(
        "System status: OK\n"
        "Total speakers: " + std::to_string(home_.getSpeakers().size()) + "\n" +
        "Connected devices: " + std::to_string(totalDevices)
    );
}

} // namespace smart_home