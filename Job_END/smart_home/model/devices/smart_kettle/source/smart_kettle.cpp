#include <algorithm>
#include <sstream>
#include "smart_kettle.hpp"

namespace smart_home {
    
SmartKettle::SmartKettle(const std::string& id, const std::string& name) 
    : Device(id, name), active_(false), temperature_(0.0f) {}

bool SmartKettle::isActive() const { return active_; }
void SmartKettle::activate() { active_ = true; }
void SmartKettle::deactivate() { active_ = false; }
float SmartKettle::readValue() const { return temperature_; }
void SmartKettle::setTemperature(float temp) { temperature_ = temp; }

} // namespace smart_home