#include <algorithm>
#include <sstream>
#include "leak_sensor.hpp"

namespace smart_home {
    
LeakSensor::LeakSensor(const std::string& id, const std::string& name) 
    : Device(id, name), leakDetected_(false) {}

float LeakSensor::readValue() const { return leakDetected_ ? 1.0f : 0.0f; }
void LeakSensor::setLeakStatus(bool detected) { leakDetected_ = detected; }

} // namespace smart_home