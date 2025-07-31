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
    SmartSpeaker AKitchenSpeaker("a_kitchen1", livingRoom);
    kitchenSpeaker.addDevice(bulb);
    kitchenSpeaker.addDevice(thermo);

    home.addSpeaker(kitchenSpeaker);
    home.addSpeaker(AKitchenSpeaker);

    cli.run();
}

} // namespace smart_home

int main() {
    smart_home::run_demo_application();
    return EXIT_SUCCESS;
}                                                                                                                                                   