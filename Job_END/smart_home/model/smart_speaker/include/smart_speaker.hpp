#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "room.hpp"
#include "device.hpp"
#include "isensor_device.hpp"
#include "iactive_device.hpp"

namespace smart_home {

class SmartSpeaker {
public:
    SmartSpeaker(const std::string& name, const Room& room);
    
    std::string getName() const;
    Room getRoom() const;
    
    void addDevice(std::shared_ptr<IDevice> device);
    void removeDevice(const std::string& deviceId);
    std::vector<std::shared_ptr<IDevice>> getDevices() const;
    // Обход включенных устройств и их опрос
    void checkAndRepairDevices();
    
    // Добавление устройства с проверкой типа
    template <typename T, typename... Args>
    void addNewDevice(Args&&... args) {
        static_assert(std::is_base_of<IDevice, T>::value, 
                     "T должен наследовать от IDevice");
        devices_.push_back(std::make_shared<T>(std::forward<Args>(args)...));
    }
private:
    std::string name_;
    Room room_;
    std::vector<std::shared_ptr<IDevice>> devices_;
};

} // namespace smart_home