#include "smart_home.hpp"

namespace smart_home {

void SmartHome::addSpeaker(const SmartSpeaker& speaker) {
    speakers_.push_back(speaker);
    // Сортируем колонки по имени
    std::sort(speakers_.begin(), speakers_.end(),
        [](const SmartSpeaker& a, const SmartSpeaker& b) {
            return a.getName() < b.getName();
        }
    );
}

void SmartHome::removeSpeaker(const std::string& speakerName) {
    speakers_.erase(
        std::remove_if(speakers_.begin(), speakers_.end(),
            [&speakerName](const SmartSpeaker& s) { return s.getName() == speakerName; }
        ),
        speakers_.end()
    );
}

SmartSpeaker* SmartHome::findSpeaker(const std::string& name) {
    auto it = std::find_if(speakers_.begin(), speakers_.end(),
        [&name](const SmartSpeaker& s) { return s.getName() == name; }
    );
    return (it != speakers_.end()) ? &(*it) : nullptr;
}

std::vector<SmartSpeaker> SmartHome::getSpeakers() const {
    return speakers_;
}

// Вывод списка колонок
std::ostream& operator<<(std::ostream& os, const SmartHome& home) {
    os << "Список колонок (всего: " << home.speakers_.size() << "):\n";
    for (const auto& speaker : home.speakers_) {
        os << "- " << speaker.getName() 
           << " (Комната: " << speaker.getRoom().getName() 
           << ", Тип: " << speaker.getRoom().getTypeAsString() << ")\n";
    }
    return os;
}

// Доступ к колонке по имени (неконстантная версия)
SmartSpeaker& SmartHome::operator[](const std::string& name) {
    auto it = std::find_if(speakers_.begin(), speakers_.end(),
        [&name](const SmartSpeaker& s) { return s.getName() == name; }
    );
    if (it == speakers_.end()) {
        throw std::out_of_range("Колонка с именем '" + name + "' не найдена!");
    }
    return *it;
}

// Доступ к колонке по имени (константная версия)
const SmartSpeaker& SmartHome::operator[](const std::string& name) const {
    return const_cast<SmartHome*>(this)->operator[](name);
}

} // namespace smart_home