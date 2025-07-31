#include <algorithm>
#include <sstream>
#include "thermometer.hpp"

namespace smart_home {
    
Thermometer::Thermometer(const std::string& id, const std::string& name) 
    : Device(id, name), temperature_(23.5f) {}

float Thermometer::readValue() const { return temperature_; }
void Thermometer::setTemperature(float temp) { temperature_ = temp; }

} // namespace smart_home