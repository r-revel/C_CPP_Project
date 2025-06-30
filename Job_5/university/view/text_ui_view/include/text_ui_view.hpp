#pragma once

#include <view.hpp>
#include <ncurses.h>

namespace banking {

class TextUIView : public IView {
public:
    TextUIView();
    ~TextUIView() override;

    void show_balance(IAccount::balance_t balance) override;
    void show_message(const std::string& message) override;
    void show_error(const std::string& error) override;
    void show_account_created(const BankingService::AccountInfo& account_info) override;
    void show_account_closed() override;
    void show_transfer_success() override;
    void show_withdrawal_success() override;
    void show_pin_changed() override;

    void show_menu();
    void clear_screen();
    std::string get_input(const std::string& prompt);
    int get_choice();

private:
    WINDOW* main_win_;
};

} // namespace banking