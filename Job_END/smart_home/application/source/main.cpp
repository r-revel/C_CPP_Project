#include "cli_view.hpp"
#include "smart_bulb.hpp"
#include "thermometer.hpp"
#include "smart_kettle.hpp"
#include "leak_sensor.hpp"
#include "air_conditioner.hpp"
#include <cstdlib>
#include <vector>
#include <utility>

namespace smart_home {

// Тестовые данные для демонстрации
std::vector<std::pair<std::string, std::string>> get_test_speakers() {
    return {
        {"123Living Room", "Living"},
        {"Kitchen", "Kitchen"},
        {"Bedroom", "Bedroom"},
        {"Bathroom", "Bathroom"}
    };
}

std::vector<std::tuple<std::string, std::string, std::string, std::string>> get_test_devices() {
    return {
        {"light1", "Main Light", "Online", "Active"},
        {"thermo1", "Thermostat", "Online", "Sensor"},
        {"plug1", "Smart Plug", "Offline", "Active"},
        {"humid1", "Humidifier", "Online", "Hybrid"}
    };
}

void run_demo_application() {
    CliView view;
    view.init();
    
    bool running = true;
    while (running) {
        view.show_menu();
        int choice = view.get_menu_choice();
        
        switch (choice) {
            case 1: // List speakers
                view.show_speakers_list(get_test_speakers());
                view.get_input("123Press Enter to continue..."); // Ждем нажатия Enter
                break;
                
            case 2: // Show devices
                view.show_devices_list(get_test_devices());
                view.get_input("Press Enter to continue...");
                break;
                
            case 3: // Control device
                {
                    std::string device_id = view.get_input("Enter device ID: ");
                    if (!device_id.empty()) {
                        view.show_message("Controlling device: " + device_id);
                        bool confirm = view.get_confirmation("Turn device on?");
                        view.show_message(confirm ? "Device turned ON" : "Device left OFF");
                    }
                }
                break;
                
            case 4: // Check status
                view.show_message("System status: OK\nConnected devices: 4");
                break;
                
            case 5: // Exit
                if (view.get_confirmation("Are you sure you want to exit?")) {
                    running = false;
                }
                break;
                
            default:
                view.show_error("Invalid choice! Please try again.");
                break;
        }
    }
    
    view.show_message("Goodbye! Shutting down...");
    view.cleanup();
}

} // namespace smart_home

int main() {
    // Создаем устройства умного дома с указанием их ID и названия
    smart_home::SmartBulb bulb("bulb1", "Гостиная лампа");
    smart_home::Thermometer thermo("thermo1", "Датчик температуры");
    smart_home::SmartKettle kettle("kettle1", "Чайник Xiaomi");
    smart_home::LeakSensor leakSensor("leak1", "Датчик протечки");
    smart_home::AirConditioner ac("ac1", "Кондиционер");


    // Управление устройствами
    bulb.activate();
    kettle.activate();
    kettle.setTemperature(95.5f);
    leakSensor.setLeakStatus(true);
    ac.activate();
    ac.setTargetTemperature(20.0f);
    
    // Выводим текущее состояние всех устройств
    std::cout << "Лампа " << (bulb.isActive() ? "включена" : "выключена") << "\n";
    std::cout << "Температура: " << thermo.readValue() << "°C\n";
    std::cout << "Чайник " << (kettle.isActive() ? "кипятит" : "выключен") 
              << ", температура: " << kettle.readValue() << "°C\n";
    std::cout << "Протечка: " << (leakSensor.readValue() > 0.5f ? "Обнаружена!" : "Нет") << "\n";
    std::cout << "Кондиционер: " << (ac.isActive() ? "Работает" : "Выключен")
              << ", текущая температура: " << ac.readValue() << "°C\n";
    
    
    // smart_home::run_demo_application();
    return EXIT_SUCCESS;
}