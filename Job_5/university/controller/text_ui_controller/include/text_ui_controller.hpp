#pragma once

#include <text_ui_view.hpp>
#include <controller.hpp>
#include <banking_service.hpp>
#include <unordered_map>
#include <memory>
#include <string>
#include <functional>

namespace banking {

class TextUIController : public IController {
public:
    TextUIController(BankingService& bank, TextUIView& view);
    void run() override;

    void on_create_account() override;
    void on_close_account() override;
    void on_check_balance() override;
    void on_transfer() override;
    void on_withdraw() override;
    void on_change_pin() override;

private:
    BankingService& bank_;
    TextUIView& view_;

    std::unordered_map<BankingService::account_id_t, BankingService::Card> cards_;

    std::shared_ptr<IAccount> create_debit();
    std::shared_ptr<IAccount> create_credit();
    std::shared_ptr<IAccount> create_saving();

    static const std::unordered_map<std::string, std::function<std::shared_ptr<IAccount>(TextUIController&)>> account_types;
};

} // namespace banking