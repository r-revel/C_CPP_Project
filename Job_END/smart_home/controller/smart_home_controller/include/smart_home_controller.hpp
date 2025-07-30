#pragma once
#include <memory>
#include <iostream>
#include <iactive_device.hpp>
#include <isensor_device.hpp>
#include <smart_home.hpp>
#include <smart_speaker.hpp>
#include <device_controller.hpp>


namespace smart_home {

class SmartHomeController {
public:
    // Добавление/удаление колонок
    static void addSpeaker(SmartHome& home, const SmartSpeaker& speaker);
    static void removeSpeaker(SmartHome& home, const std::string& speakerName);
    
    // Поиск колонки по имени
    static SmartSpeaker* findSpeaker(SmartHome& home, const std::string& name);
    
    // Управление устройствами через колонку
    static void listAllDevices(const SmartSpeaker& speaker);
    static void controlDeviceInSpeaker(SmartSpeaker& speaker, const std::string& deviceId);
};

} // namespace device