#pragma once

#include <banking_service.hpp>
#include <string>

namespace banking {

class IView {
public:
    virtual ~IView() = default;

    virtual void show_balance(IAccount::balance_t balance) = 0;
    virtual void show_message(const std::string& message) = 0;
    virtual void show_error(const std::string& error) = 0;
    virtual void show_account_created(const BankingService::AccountInfo& account_info) = 0;
    virtual void show_account_closed() = 0;
    virtual void show_transfer_success() = 0;
    virtual void show_withdrawal_success() = 0;
    virtual void show_pin_changed() = 0;
};

} // namespace banking