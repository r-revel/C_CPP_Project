#include <sstream>
#include "room.hpp"


namespace smart_home {

Room::Room(const std::string& name, int number, RoomType type) 
    : name_(name), number_(number), type_(type) {}

std::string Room::getName() const { return name_; }
int Room::getNumber() const { return number_; }
RoomType Room::getType() const { return type_; }

std::string Room::getTypeAsString() const {
    switch (type_) {
        case RoomType::LIVING_ROOM: return "Жилая комната";
        case RoomType::KITCHEN:     return "Кухня";
        case RoomType::BATHROOM:    return "Санузел";
        case RoomType::HALLWAY:     return "Коридор";
        case RoomType::BALCONY:     return "Балкон";
        default:                    return "Неизвестно";
    }
}

} // namespace smart_home