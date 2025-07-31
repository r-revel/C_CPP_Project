#pragma once
#include <string>

namespace smart_home {

// Интерфейс для активных устройств (вкл/выкл)
class ISensorDevice {
public:
    virtual ~ISensorDevice() = default;
    virtual float readValue() const = 0;
};

} // namespace device