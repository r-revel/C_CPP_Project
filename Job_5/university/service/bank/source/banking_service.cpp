#include "banking_service.hpp"

namespace banking {

    BankingService::BankingService(IAccountRepository& repository): repository_(repository) {}

    BankingService::Card::Card(BankingService::account_id_t account_id, BankingService::pin_code_t pin) : account_id_(account_id),
                                                                            pin_code_(pin) {}

    bool BankingService::Card::set_password(BankingService::pin_code_t old_pin, BankingService::pin_code_t new_pin) {
        bool success = pin_code_ == old_pin;
        if(success)
            pin_code_ = new_pin;
        return success;
    }

    std::optional<BankingService::account_id_t> BankingService::Card::get_account(BankingService::pin_code_t pin) const {
        if(pin_code_ == pin)
            return account_id_;
        else
            return std::nullopt;
    }


    BankingService::AccountInfo BankingService::open_new_account(std::shared_ptr<IAccount> new_account) {
        auto id = repository_.add(new_account);
        pin_code_t pin = generate_random_pin();
        AccountInfo result {
            .card = Card(id, pin),
            .account_id = id,
            .pin_code = pin
        };
        return result;
    }

    BankingService::pin_code_t BankingService::generate_random_pin() {
        return distribution_(random_device_);
    }

    BankingService::account_clonning_result BankingService::open_same_account(const BankingService::Card &card, BankingService::pin_code_t pin) {
        auto account_id = card.get_account(pin);
        if(!account_id)
            return { std::nullopt, operation_status::wrong_pin };
        auto account = repository_.get(*account_id);
        if(!account)
            return { std::nullopt, operation_status::invalid_source_account };
        return { open_new_account(account->clone()), operation_status::success };
    }

    BankingService::operation_status BankingService::close_account(const BankingService::Card &card, BankingService::pin_code_t pin) {
        auto account_id = card.get_account(pin);
        if(!account_id)
            return operation_status::wrong_pin;
        auto account = repository_.get(*account_id);
        if (!account)
            return operation_status::invalid_source_account;
        repository_.remove(*account_id);
        return operation_status::success;
    }

    BankingService::operation_status BankingService::change_password(BankingService::Card &card, BankingService::pin_code_t old_pin, BankingService::pin_code_t new_pin) {
        return card.set_password(old_pin, new_pin) ? operation_status::success :
                                                     operation_status::wrong_pin;
    }

    BankingService::operation_status BankingService::get_cash(IAccount::transaction_t amount, const BankingService::Card &card, BankingService::pin_code_t pin) {
        auto account_id = card.get_account(pin);
        if(!account_id)
            return operation_status::wrong_pin;
        auto account = repository_.get(*account_id);
        if(!account)
            return operation_status::invalid_source_account;
        return account->reduce_balance(amount) ? operation_status::success : operation_status::not_enough_money;
    }

    BankingService::balance_result BankingService::get_balance(const BankingService::Card &card, BankingService::pin_code_t pin) const {
        auto account_id = card.get_account(pin);
        if(!account_id)
            return { std::nullopt, operation_status::wrong_pin };
        auto account = repository_.get(*account_id);
        if(!account)
            return { std::nullopt, operation_status::invalid_source_account };
        return { account->get_balance(), operation_status::success };
    }

    BankingService::operation_status BankingService::transfer_to_account(BankingService::account_id_t other_account, IAccount::transaction_t amount,
                                                     const BankingService::Card &card, BankingService::pin_code_t pin) {
        auto account_id = card.get_account(pin);
        if(!account_id)
            return  operation_status::wrong_pin;

        auto account_src = repository_.get(*account_id);
        if(!account_src)
            return operation_status::invalid_source_account;

        if(account_src->available_funds() < amount)
            return operation_status::not_enough_money;

        auto account_dst = repository_.get(other_account);
        if(!account_dst)
            return operation_status::invalid_destination_account;

        if(!account_dst->increase_balance(amount))
            return operation_status::operation_declined;

        account_src->reduce_balance(amount);
        return operation_status::success;
    }

}