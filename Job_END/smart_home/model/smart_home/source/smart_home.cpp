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
    return &((*this)[name]);
}

std::vector<SmartSpeaker> SmartHome::getSpeakers() const {
    return speakers_;
}

// TODO Добавил лишь из за правила в техническом задании. 
// TODO Данной функции здесь не место и все лучше вынести в cli классы
// Вывод списка колонок
std::ostream& operator<<(std::ostream& os, const SmartHome& home) {
    // Создаем копию списка колонок для сортировки
    auto speakers = home.speakers_;
    std::sort(speakers.begin(), speakers.end(), 
        [](const SmartSpeaker& a, const SmartSpeaker& b) {
            return a.getName() < b.getName();
        });

    // Заголовок
    os << "\n=== СПИСОК КОЛОНОК ===\n";
    os << "Имя колонки\t\tКомната\t\tТип\n";
        
    // Данные
    for (const auto& speaker : speakers) {
        os << speaker.getName() << "\t\t"
        << speaker.getRoom().getName() << "\t\t"
        << speaker.getRoom().getTypeAsString() << "\n";
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