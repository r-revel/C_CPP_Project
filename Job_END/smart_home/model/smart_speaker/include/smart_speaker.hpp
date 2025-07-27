#pragma once
#include "../room/include/room.hpp"
#include "../device/include/device.hpp"
#include <vector>
#include <memory>
#include <algorithm>

namespace smart_home {

class SmartSpeaker {
public:
    SmartSpeaker(std::shared_ptr<Room> room);
    
    std::shared_ptr<Room> getRoom() const;
    const std::vector<std::shared_ptr<Device>>& getDevices() const;
    
    void addDevice(std::shared_ptr<Device> device);
    void checkAndUpdateDevices();
    
private:
    std::shared_ptr<Room> room_;
    std::vector<std::shared_ptr<Device>> devices_;
};

} // namespace smart_home