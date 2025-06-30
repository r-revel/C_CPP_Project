#pragma once

#include <account.hpp>

namespace banking{

class SavingAccount : public IAccount {
public:
    explicit SavingAccount(double bonus_rate, balance_t value = 0);

    SavingAccount(double bonus_rate, balance_t raw_balance, balance_t bonus_balance);

    bool reduce_balance(transaction_t value) override;

    bool increase_balance(transaction_t value) override;

    [[nodiscard]] balance_t get_balance() const override;

    [[nodiscard]] balance_t available_funds() const override;

    [[nodiscard]] std::shared_ptr<IAccount> clone() const override;

    double get_bonus_percent() const;

    balance_t get_raw_balance() const;

    balance_t get_bonus_balance() const;

private:
    const double bonus_percent_;

    balance_t balance_ = 0;

    balance_t bonus_balance_ = 0;
};

}