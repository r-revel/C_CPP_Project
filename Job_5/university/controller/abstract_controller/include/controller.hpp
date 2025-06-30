#pragma once

#include <memory>

namespace banking {

class IController {
public:
    virtual ~IController() = default;

    virtual void run() = 0;
    virtual void on_create_account() = 0;
    virtual void on_close_account() = 0;
    virtual void on_check_balance() = 0;
    virtual void on_transfer() = 0;
    virtual void on_withdraw() = 0;
    virtual void on_change_pin() = 0;
};

} // namespace banking