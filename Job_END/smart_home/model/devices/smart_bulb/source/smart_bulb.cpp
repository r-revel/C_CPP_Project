#include <algorithm>
#include <sstream>
#include "smart_bulb.hpp"

namespace smart_home {
    
SmartBulb::SmartBulb(const std::string& id, const std::string& name) 
    : Device(id, name), active_(false) {}

bool SmartBulb::isActive() const { return active_; }
void SmartBulb::activate() { active_ = true; }
void SmartBulb::deactivate() { active_ = false; }

} // namespace smart_home