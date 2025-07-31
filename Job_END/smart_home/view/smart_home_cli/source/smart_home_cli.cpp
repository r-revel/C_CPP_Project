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
            case 4: addNewDevice(); break;
            case 5: checkSystemStatus(); break;
            case 6: toggleDeviceOnlineStatus(); break;
            case 7: checkAndRepairDevices(); break;
            case 8: 
                if (view_.get_confirmation("Выйти из системы?")) {
                    running = false;
                }
                break;
            default:
                view_.show_error("Неверный выбор!");
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
    view_.show_speakers_list(home_);
    view_.get_input("Press Enter to continue...");
}

void SmartHomeCLI::showRoomDevices() {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> devices;
    
    for (const auto& speaker : home_.getSpeakers()) {
        for (const auto& device : speaker.getDevices()) {
            std::string status = device->isOnline() ? "Онлайн" : "Оффлайн";
            std::string type = "Устройство";
            
            if (dynamic_cast<IActiveDevice*>(device.get())) {
                type = "Активное " + type;
            }
            if (dynamic_cast<ISensorDevice*>(device.get())) {
                type = "Сенсорное " + type;
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
    view_.get_input("Нажмите Enter чтобы продолжить...");
}

void SmartHomeCLI::toggleDeviceOnlineStatus() {
    std::string deviceId = view_.get_input("Введите ID устройства: ");
    if (deviceId.empty()) return;

    for (auto& speaker : home_.getSpeakers()) {
        for (const auto& device : speaker.getDevices()) {
            if (device->getId() == deviceId) {
                bool confirm = view_.get_confirmation(
                    "Перевести устройство " + device->getName() + 
                    " в " + (device->isOnline() ? "оффлайн?" : "онлайн?")
                );
                if (confirm) {
                    DeviceController::setDeviceOnlineStatus(device, !device->isOnline());
                    view_.show_message(
                        "Устройство " + device->getName() + " теперь " + 
                        (device->isOnline() ? "онлайн" : "оффлайн")
                    );
                }
                return;
            }
        }
    }
    view_.show_error("Устройство не найдено!");
}

void SmartHomeCLI::controlDevice() {
    std::string deviceId = view_.get_input("Введите ID устройства: ");
    if (deviceId.empty()) return;

    for (auto& speaker : home_.getSpeakers()) {
    for (const auto& device : speaker.getDevices()) {
        if (device->getId() == deviceId) {
            if (auto activeDev = std::dynamic_pointer_cast<IActiveDevice>(device)) {
                bool confirm = view_.get_confirmation(
                    "Переключить " + device->getName() + " в состояние " + 
                    (activeDev->isActive() ? "ВЫКЛ?" : "ВКЛ?")
                );
                if (confirm) {
                    DeviceController::toggleDevice(activeDev);
                    view_.show_message("Устройство успешно переключено!");
                }
            } else if (auto sensorDev = std::dynamic_pointer_cast<ISensorDevice>(device)) {
                float value = DeviceController::readSensorValue(sensorDev);
                view_.show_message(
                    "Показание датчика: " + std::to_string(value)
                );
            } else {
                view_.show_error("Это устройство нельзя контролировать.");
            }
            return;
        }
    }
    }
    view_.show_error("Устройство не найдено!");
}

void SmartHomeCLI::checkSystemStatus() {
    int totalDevices = 0;
    for (const auto& speaker : home_.getSpeakers()) {
        totalDevices += speaker.getDevices().size();
    }
    
    view_.show_message(
        "Статус системы: OK\n"
        "Всего колонок: " + std::to_string(home_.getSpeakers().size()) + "\n" +
        "Подключенных устройств: " + std::to_string(totalDevices)
    );
}
void с {
    view_.clear_main();
    
    // 1. Выбор колонки
    std::string speakerName = view_.get_input("Введите имя колонки: ");
    auto* speaker = SmartHomeController::findSpeaker(home_, speakerName);

    if (!speaker) {
        view_.show_error("Колонка не найдена!");
        return;
    }

    // 2. Выбор типа устройства
    view_.show_message("Выберите тип устройства:\n"
                    "1. Умная лампа\n"
                    "2. Термометр\n"
                    "3. Умный чайник\n"
                    "4. Датчик протечки\n"
                    "5. Кондиционер");

    int choice;
    std::string input = view_.get_input("Ваш выбор (1-5): ");
    try {
        choice = std::stoi(input);
    } catch (const std::invalid_argument&) {
        view_.show_error("Неверный ввод! Пожалуйста, введите число от 1 до 5.");
        return;
    } catch (const std::out_of_range&) {
        view_.show_error("Введенное число слишком большое или слишком маленькое.");
        return;
    }

    if (choice < 1 || choice > 5) {
        view_.show_error("Неверный выбор типа! Пожалуйста, введите число от 1 до 5.");
        return;
    }

    // 3. Ввод параметров
    std::string id = view_.get_input("Введите ID устройства: ");
    std::string name = view_.get_input("Введите имя устройства: ");

    // 4. Создание устройства
    switch (choice) {
        case 1:
            speaker->addNewDevice<SmartBulb>(id, name);
            break;
        case 2:
            speaker->addNewDevice<Thermometer>(id, name);
            break;
        case 3:
            speaker->addNewDevice<SmartKettle>(id, name);
            break;
        case 4:
            speaker->addNewDevice<LeakSensor>(id, name);
            break;
        case 5:
            speaker->addNewDevice<AirConditioner>(id, name);
            break;
        default:
            // Эта ветка теперь теоретически недостижима, но оставлена для перестраховки
            view_.show_error("Неверный выбор типа!");
            return;
    }

    view_.show_message("Устройство успешно добавлено!");

}
void SmartHomeCLI::checkAndRepairDevices() {
    std::string speakerName = view_.get_input("Введите имя колонки: ");
    if (speakerName.empty()) return;

    auto* speaker = SmartHomeController::findSpeaker(home_, speakerName);
    if (!speaker) {
        view_.show_error("Колонка '" + speakerName + "' не найдена!");
        return;
    }

    // 3. Запускаем проверку и восстановление
    try {
        view_.show_message("🔍 Проверяю устройства в колонке '" + speakerName + "'...");
        speaker->checkAndRepairDevices();
    } catch (const std::exception& e) {
        view_.show_error("Ошибка: " + std::string(e.what()));
    }

    view_.get_input("Нажмите Enter чтобы продолжить...");
}

} // namespace smart_home