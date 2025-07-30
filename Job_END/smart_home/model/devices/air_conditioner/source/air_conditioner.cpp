#include <algorithm>
#include <sstream>
#include "air_conditioner.hpp"

namespace smart_home {
    
AirConditioner::AirConditioner(const std::string& id, const std::string& name) 
    : Device(id, name), active_(false), currentTemp_(22.0f), targetTemp_(22.0f) {}

bool AirConditioner::isActive() const { return active_; }
void AirConditioner::activate() { active_ = true; }
void AirConditioner::deactivate() { active_ = false; }
float AirConditioner::readValue() const { return currentTemp_; }
void AirConditioner::setTargetTemperature(float temp) { targetTemp_ = temp; }

} // namespace smart_home