#include "text_ui_view.hpp"
#include <stdexcept>
#include <cstring>

namespace banking {

TextUIView::TextUIView() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    main_win_ = newwin(LINES, COLS, 0, 0);
    refresh();
}

TextUIView::~TextUIView() {
    delwin(main_win_);
    endwin();
}

void TextUIView::clear_screen() {
    wclear(main_win_);
    wrefresh(main_win_);
}

void TextUIView::show_menu() {
    clear_screen();
    mvwprintw(main_win_, 1, 1, "Banking System Menu:");
    mvwprintw(main_win_, 3, 1, "1. Create Account");
    mvwprintw(main_win_, 4, 1, "2. Close Account");
    mvwprintw(main_win_, 5, 1, "3. Check Balance");
    mvwprintw(main_win_, 6, 1, "4. Transfer Money");
    mvwprintw(main_win_, 7, 1, "5. Withdraw Cash");
    mvwprintw(main_win_, 8, 1, "6. Change PIN");
    mvwprintw(main_win_, 9, 1, "7. Exit");
    mvwprintw(main_win_, 11, 1, "Enter choice: ");
    wrefresh(main_win_);
}

int TextUIView::get_choice() {
    return getch() - '0';
}

std::string TextUIView::get_input(const std::string& prompt) {
    echo();
    char input[256];
    mvwprintw(main_win_, LINES - 2, 1, "%s", prompt.c_str());
    wgetnstr(main_win_, input, sizeof(input) - 1);

    char clear[256];
    auto len = std::max(prompt.size() + strlen(input), 255ul);
    std::fill(clear, clear + len, ' ');
    clear[len] = '\0';
    mvwprintw(main_win_, LINES - 2, 1, "%s", clear);

    noecho();
    return std::string(input);
}

void TextUIView::show_balance(IAccount::balance_t balance) {
    clear_screen();
    mvwprintw(main_win_, 1, 1, "Current balance: %lld", balance);
    mvwprintw(main_win_, 3, 1, "Press any key to continue...");
    wrefresh(main_win_);
    getch();
}

void TextUIView::show_message(const std::string& message) {
    clear_screen();
    mvwprintw(main_win_, 1, 1, "%s", message.c_str());
    mvwprintw(main_win_, 3, 1, "Press any key to continue...");
    wrefresh(main_win_);
    getch();
}

void TextUIView::show_error(const std::string& error) {
    clear_screen();
    wattron(main_win_, A_STANDOUT);
    mvwprintw(main_win_, 1, 1, "ERROR: %s", error.c_str());
    wattroff(main_win_, A_STANDOUT);
    mvwprintw(main_win_, 3, 1, "Press any key to continue...");
    wrefresh(main_win_);
    getch();
}

void TextUIView::show_account_created(const BankingService::AccountInfo& account_info) {
    clear_screen();
    mvwprintw(main_win_, 1, 1, "Account created successfully!");
    mvwprintw(main_win_, 2, 1, "Account ID: %llu", account_info.account_id);
    mvwprintw(main_win_, 3, 1, "PIN: %zu", account_info.pin_code);
    mvwprintw(main_win_, 5, 1, "Press any key to continue...");
    wrefresh(main_win_);
    getch();
}

void TextUIView::show_account_closed() {
    show_message("Account closed successfully!");
}

void TextUIView::show_transfer_success() {
    show_message("Transfer completed successfully!");
}

void TextUIView::show_withdrawal_success() {
    show_message("Cash withdrawn successfully!");
}

void TextUIView::show_pin_changed() {
    show_message("PIN changed successfully!");
}

} // namespace banking