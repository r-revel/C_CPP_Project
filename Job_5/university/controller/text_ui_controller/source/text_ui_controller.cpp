#include "text_ui_controller.hpp"
#include <banking_service.hpp>

#include <debit_account.hpp>
#include <credit_account.hpp>
#include <saving_account.hpp>

#include <sstream>
#include <stdexcept>

namespace banking {

const std::unordered_map<std::string, std::function<std::shared_ptr<IAccount>(TextUIController&)>> TextUIController::account_types {
    std::pair{std::string{"debit"},  std::function{[](TextUIController& obj){ return obj.create_debit(); }}},
    std::pair{std::string{"credit"}, std::function{[](TextUIController& obj){ return obj.create_credit(); }}},
    std::pair{std::string{"saving"}, std::function{[](TextUIController& obj){ return obj.create_saving(); }}}
};

TextUIController::TextUIController(BankingService& bank, TextUIView& view)
    : bank_(bank), view_(view) {}

void TextUIController::run() {
    while (true) {
        view_.show_menu();
        int choice = view_.get_choice();

        switch (choice) {
            case 1: on_create_account(); break;
            case 2: on_close_account(); break;
            case 3: on_check_balance(); break;
            case 4: on_transfer(); break;
            case 5: on_withdraw(); break;
            case 6: on_change_pin(); break;
            case 7: return;
            default: view_.show_error("Invalid choice"); break;
        }
    }
}

void TextUIController::on_create_account() {
    try {
        auto account_type = view_.get_input("Enter account type: ");
        
        auto account = account_types.at(account_type)(*this);
        auto account_info = bank_.open_new_account(account);
        cards_.emplace(account_info.account_id, account_info.card);
        view_.show_account_created(account_info);
    } catch (const std::exception& e) {
        view_.show_error("Invalid input: " + std::string(e.what()));
    }
}

void TextUIController::on_close_account() {
    try {
        auto card_id_str = view_.get_input("Enter card ID: ");
        BankingService::account_id_t card_id = std::stoull(card_id_str);
        
        auto pin_str = view_.get_input("Enter PIN: ");
        BankingService::pin_code_t pin = std::stoull(pin_str);
        
        auto& card = cards_.at(card_id);
        auto status = bank_.close_account(card, pin);
        
        if (status == BankingService::operation_status::success) {
            view_.show_account_closed();
        } else {
            view_.show_error("Failed to close account");
        }
    } catch (const std::exception& e) {
        view_.show_error("Invalid input: " + std::string(e.what()));
    }
}

void TextUIController::on_check_balance() {
    try {
        auto card_id_str = view_.get_input("Enter card ID: ");
        BankingService::account_id_t card_id = std::stoull(card_id_str);
        
        auto pin_str = view_.get_input("Enter PIN: ");
        BankingService::pin_code_t pin = std::stoull(pin_str);
        
        auto& card = cards_.at(card_id);
        auto result = bank_.get_balance(card, pin);
        
        if (result.status == BankingService::operation_status::success && result.balance) {
            view_.show_balance(*result.balance);
        } else {
            view_.show_error("Failed to get balance");
        }
    } catch (const std::exception& e) {
        view_.show_error("Invalid input: " + std::string(e.what()));
    }
}

void TextUIController::on_transfer() {
    try {
        auto src_card_str = view_.get_input("Enter your card ID: ");
        BankingService::account_id_t src_card_id = std::stoull(src_card_str);
        
        auto pin_str = view_.get_input("Enter PIN: ");
        BankingService::pin_code_t pin = std::stoull(pin_str);
        
        auto dest_account_str = view_.get_input("Enter destination account ID: ");
        BankingService::account_id_t dest_account_id = std::stoull(dest_account_str);
        
        auto amount_str = view_.get_input("Enter amount to transfer: ");
        IAccount::transaction_t amount = std::stoll(amount_str);
        
        auto& card = cards_.at(src_card_id);
        auto status = bank_.transfer_to_account(dest_account_id, amount, card, pin);
        
        if (status == BankingService::operation_status::success) {
            view_.show_transfer_success();
        } else {
            view_.show_error("Transfer failed");
        }
    } catch (const std::exception& e) {
        view_.show_error("Invalid input: " + std::string(e.what()));
    }
}

void TextUIController::on_withdraw() {
    try {
        auto card_id_str = view_.get_input("Enter card ID: ");
        BankingService::account_id_t card_id = std::stoull(card_id_str);
        
        auto pin_str = view_.get_input("Enter PIN: ");
        BankingService::pin_code_t pin = std::stoull(pin_str);
        
        auto amount_str = view_.get_input("Enter amount to withdraw: ");
        IAccount::transaction_t amount = std::stoll(amount_str);
        
        auto& card = cards_.at(card_id);
        auto status = bank_.get_cash(amount, card, pin);
        
        if (status == BankingService::operation_status::success) {
            view_.show_withdrawal_success();
        } else {
            view_.show_error("Withdrawal failed");
        }
    } catch (const std::exception& e) {
        view_.show_error("Invalid input: " + std::string(e.what()));
    }
}

void TextUIController::on_change_pin() {
    try {
        auto card_id_str = view_.get_input("Enter card ID: ");
        BankingService::account_id_t card_id = std::stoull(card_id_str);
        
        auto old_pin_str = view_.get_input("Enter current PIN: ");
        BankingService::pin_code_t old_pin = std::stoull(old_pin_str);
        
        auto new_pin_str = view_.get_input("Enter new PIN: ");
        BankingService::pin_code_t new_pin = std::stoull(new_pin_str);
        
        auto& card = cards_.at(card_id);
        auto status = BankingService::change_password(card, old_pin, new_pin);
        
        if (status == BankingService::operation_status::success) {
            view_.show_pin_changed();
        } else {
            view_.show_error("Failed to change PIN");
        }
    } catch (const std::exception& e) {
        view_.show_error("Invalid input: " + std::string(e.what()));
    }
}


std::shared_ptr<IAccount> TextUIController::create_debit() {
    auto balance = view_.get_input("Enter starting balance: ");
    return std::make_shared<DebitAccount>(std::stoll(balance));
}

std::shared_ptr<IAccount> TextUIController::create_credit() {
    auto limit = view_.get_input("Enter limit: ");
    auto rate = view_.get_input("Enter comission_rate: ");
    return std::make_shared<CreditAccount>(std::stoll(limit), std::stold(rate));
}

std::shared_ptr<IAccount> TextUIController::create_saving() {
    auto balance = view_.get_input("Enter starting balance: ");
    auto rate = view_.get_input("Enter bonus rate: ");
    return std::make_shared<SavingAccount>(std::stold(rate), std::stoll(balance));
}

} // namespace banking