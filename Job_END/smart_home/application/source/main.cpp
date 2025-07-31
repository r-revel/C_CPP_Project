#include <cstdlib>
#include <vector>
#include <utility>

#include "cli_view.hpp"
#include "thermometer.hpp"
#include "smart_bulb.hpp"
#include "smart_kettle.hpp"
#include "leak_sensor.hpp"
#include "air_conditioner.hpp"
#include "room.hpp"
#include "smart_speaker.hpp"
#include "smart_home.hpp"
#include "device_controller.hpp"
#include "smart_home_controller.hpp"
#include "smart_home_cli.hpp"


namespace smart_home {


void run_demo_application() {
    SmartHome home;
    CliView view;
    SmartHomeCLI cli(home, view);

    // Добавляем тестовые данные
    Room kitchen("Кухня", 1, RoomType::KITCHEN);
    Room livingRoom("Гостиная", 2, RoomType::LIVING_ROOM);

    auto bulb = std::make_shared<SmartBulb>("bulb1", "Умная лампа");
    auto thermo = std::make_shared<Thermometer>("thermo1", "Датчик температуры");

    SmartSpeaker kitchenSpeaker("kitchen1", kitchen);
    kitchenSpeaker.addDevice(bulb);
    kitchenSpeaker.addDevice(thermo);

    home.addSpeaker(kitchenSpeaker);
    
    try {
        auto& speaker = home["kitchen1"]; // Доступ по имени
        speaker.checkAndRepairDevices(); // Проверка устройств
    } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    cli.run();
}

} // namespace smart_home

int main() {
    smart_home::run_demo_application();
    // Создаем комнаты
    // smart_home::Room kitchen("Кухня", 1, smart_home::RoomType::KITCHEN);
    // smart_home::Room livingRoom("Гостиная", 2, smart_home::RoomType::LIVING_ROOM);

    // // Создаем устройства
    // auto bulb = std::make_shared<smart_home::SmartBulb>("bulb1", "Умная лампа");
    // auto thermo = std::make_shared<smart_home::Thermometer>("thermo1", "Датчик температуры");

    // // Создаем колонки и добавляем устройства
    // smart_home::SmartSpeaker kitchenSpeaker("Кухонная колонка", kitchen);
    // kitchenSpeaker.addDevice(bulb);
    // kitchenSpeaker.addDevice(thermo);

    // // Управляем умным домом
    // smart_home::SmartHome home;
    // smart_home::SmartHomeController::addSpeaker(home, kitchenSpeaker);

    // // Находим колонку и управляем устройствами
    // smart_home::SmartSpeaker* speaker = smart_home::SmartHomeController::findSpeaker(home, "Кухонная колонка");
    // if (speaker) {
    //     smart_home::SmartHomeController::listAllDevices(*speaker);
    //     smart_home::SmartHomeController::controlDeviceInSpeaker(*speaker, "bulb1"); // Включаем лампу
    //     smart_home::SmartHomeController::controlDeviceInSpeaker(*speaker, "thermo1"); // Читаем датчик
    // }

    // // Проверяем статус устройства
    // std::cout << smart_home::DeviceController::getDeviceStatus(bulb) << "\n";

    // // Создаем устройства умного дома с указанием их ID и названия
    // SmartBulb bulb("bulb1", "Гостиная лампа");
    // Thermometer thermo("thermo1", "Датчик температуры");
    // SmartKettle kettle("kettle1", "Чайник Xiaomi");
    // LeakSensor leakSensor("leak1", "Датчик протечки");
    // AirConditioner ac("ac1", "Кондиционер");


    // // Управление устройствами
    // bulb.activate();
    // kettle.activate();
    // kettle.setTemperature(95.5f);
    // leakSensor.setLeakStatus(true);
    // ac.activate();
    // ac.setTargetTemperature(20.0f);
    
    // // Выводим текущее состояние всех устройств
    // std::cout << "Лампа " << (bulb.isActive() ? "включена" : "выключена") << "\n";
    // std::cout << "Температура: " << thermo.readValue() << "°C\n";
    // std::cout << "Чайник " << (kettle.isActive() ? "кипятит" : "выключен") 
    //           << ", температура: " << kettle.readValue() << "°C\n";
    // std::cout << "Протечка: " << (leakSensor.readValue() > 0.5f ? "Обнаружена!" : "Нет") << "\n";
    // std::cout << "Кондиционер: " << (ac.isActive() ? "Работает" : "Выключен")
    //           << ", текущая температура: " << ac.readValue() << "°C\n";
    
    
    // smart_home::run_demo_application();
    return EXIT_SUCCESS;
}                                                                                                                                                   