#pragma once

#include <map>
#include <vector>
#include <memory>
#include <ostream>

#include <smart_speaker.hpp>

namespace smart_home {

class SmartHome {
public:
    void addSpeaker(const SmartSpeaker& speaker);
    void removeSpeaker(const std::string& speakerName);
    
    SmartSpeaker* findSpeaker(const std::string& name);
    std::vector<SmartSpeaker> getSpeakers() const;

    // Перегрузка оператора << для вывода списка колонок
    friend std::ostream& operator<<(std::ostream& os, const SmartHome& home);
    
    // Перегрузка оператора [] для доступа к колонке по имени
    SmartSpeaker& operator[](const std::string& name);
    const SmartSpeaker& operator[](const std::string& name) const;

private:
    std::vector<SmartSpeaker> speakers_;
};

} // namespace smart_home