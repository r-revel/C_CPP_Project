#pragma once
#include <string>

namespace smart_home {

// Интерфейс для активных устройств (вкл/выкл)
class IActiveDevice {
public:
    virtual ~IActiveDevice() = default;
    virtual bool isActive() const = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
};

} // namespace device