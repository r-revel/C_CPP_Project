#pragma once
#include "../smart_speaker/include/smart_speaker.hpp"
#include <map>
#include <vector>
#include <memory>
#include <ostream>

namespace smart_home {

class SmartHome {
public:
    void addSpeaker(std::shared_ptr<SmartSpeaker> speaker);
    std::shared_ptr<SmartSpeaker> getSpeaker(const std::string& roomName);
    const std::map<std::string, std::shared_ptr<SmartSpeaker>>& getAllSpeakers() const;
    
    friend std::ostream& operator<<(std::ostream& os, const SmartHome& smartHome);
    std::shared_ptr<SmartSpeaker> operator[](const std::string& roomName);
    const std::shared_ptr<SmartSpeaker> operator[](const std::string& roomName) const;

private:
    std::map<std::string, std::shared_ptr<SmartSpeaker>> speakers_;
};

} // namespace smart_home