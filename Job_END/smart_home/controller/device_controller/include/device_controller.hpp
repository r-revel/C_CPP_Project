#pragma once
#include <memory>
#include <iactive_device.hpp>
#include <isensor_device.hpp>
#include <idevice.hpp>


namespace smart_home {

class DeviceController {
public:
    // Управление активными устройствами (вкл/выкл)
    static void toggleDevice(std::shared_ptr<IActiveDevice> device);
    
    // Получение данных с датчиков
    static float readSensorValue(std::shared_ptr<ISensorDevice> sensor);
    
    // Проверка состояния устройства
    static std::string getDeviceStatus(std::shared_ptr<IDevice> device);
};

} // namespace device

