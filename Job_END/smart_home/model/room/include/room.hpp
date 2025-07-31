#pragma once
#include <string>

namespace smart_home {

enum class RoomType {
    LIVING_ROOM,  // Жилая комната
    KITCHEN,      // Кухня
    BATHROOM,     // Санузел
    HALLWAY,      // Коридор
    BALCONY       // Балкон
};

class Room {
public:
    Room(const std::string& name, int number, RoomType type);
    
    std::string getName() const;
    int getNumber() const;
    RoomType getType() const;
    std::string getTypeAsString() const;

private:
    std::string name_;
    int number_;
    RoomType type_;
};

} // namespace smart_home