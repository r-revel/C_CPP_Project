#pragma once
#include <string>

namespace smart_home {

enum class RoomType {
    LIVING,
    BEDROOM,
    KITCHEN,
    BATHROOM,
    HALLWAY,
    BALCONY
};

class Room {
public:
    Room(std::string name, int number, RoomType type);
    
    std::string getName() const;
    int getNumber() const;
    RoomType getType() const;
    std::string getTypeString() const;

private:
    std::string name_;
    int number_;
    RoomType type_;
};

} // namespace smart_home