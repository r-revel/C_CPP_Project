#pragma once

#include <account_repository.hpp>
#include <account.hpp>

#include <optional>
#include <random>
#include <limits>


namespace banking {

class BankingService {
public:

    BankingService(IAccountRepository& repository);

    using pin_code_t = std::size_t;
    using account_id_t = IAccountRepository::account_id_t;

    class Card {
    private:
        friend class BankingService;

        Card(account_id_t account_id, pin_code_t pin);

        bool set_password(pin_code_t old_pin, pin_code_t new_pin);

        [[nodiscard]] std::optional<account_id_t> get_account(pin_code_t pin) const;

        std::size_t account_id_;

        std::size_t pin_code_;
    };

    struct AccountInfo {
        Card card;
        account_id_t account_id;
        pin_code_t pin_code;
    };

    enum class operation_status {
        success,
        wrong_pin,
        invalid_source_account,
        invalid_destination_account,
        not_enough_money,
        operation_declined
    };

    struct account_clonning_result {
        std::optional<AccountInfo> account_info;
        operation_status status;
    };

    struct balance_result {
        std::optional<IAccount::balance_t> balance;
        operation_status status;
    };

    AccountInfo open_new_account(std::shared_ptr<IAccount> new_account);

    account_clonning_result open_same_account(const Card& card, pin_code_t pin);

    operation_status close_account(const Card& card, pin_code_t pin);

    static operation_status change_password(Card& card, pin_code_t old_pin, pin_code_t new_pin);

    operation_status get_cash(IAccount::transaction_t amount, const Card& card, pin_code_t pin);

    operation_status transfer_to_account (account_id_t other_account, IAccount::transaction_t amount,
                              const Card& card, pin_code_t pin);

    [[nodiscard]] balance_result get_balance(const Card& card, pin_code_t pin) const;

private:
    static constexpr pin_code_t MIN_PIN = 1000;

    static constexpr pin_code_t MAX_PIN = 9999;

    pin_code_t generate_random_pin();

    IAccountRepository& repository_;

    std::mt19937_64 random_device_ {0};

    std::uniform_int_distribution<pin_code_t> distribution_ {MIN_PIN, MAX_PIN};

};

}