#pragma once

#include <iostream>

#include <smart_home.hpp>
#include <cli_view.hpp>
#include <iactive_device.hpp>
#include <iactive_device.hpp>
#include <device_controller.hpp>
#include <smart_home_controller.hpp>
#include <thermometer.hpp>
#include <smart_bulb.hpp>
#include <smart_kettle.hpp>
#include <leak_sensor.hpp>
#include <air_conditioner.hpp>

namespace smart_home {

class SmartHomeCLI {
public:
    SmartHomeCLI(SmartHome& home, CliView& view);
    void addNewDevice();
    void run();

private:
    void listAllSpeakers();
    void showRoomDevices();
    void controlDevice();
    void checkSystemStatus();
    void toggleDeviceOnlineStatus();
    void checkAndRepairDevices();

    SmartHome& home_;
    CliView& view_;
};

} // namespace smart_home