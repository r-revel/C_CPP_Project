#pragma once

#include <iostream>

#include <smart_home.hpp>
#include <cli_view.hpp>
#include <iactive_device.hpp>
#include <iactive_device.hpp>
#include <device_controller.hpp>

namespace smart_home {

class SmartHomeCLI {
public:
    SmartHomeCLI(SmartHome& home, CliView& view);
    void run();

private:
    void listAllSpeakers();
    void showRoomDevices();
    void controlDevice();
    void checkSystemStatus();

    SmartHome& home_;
    CliView& view_;
};

} // namespace smart_home