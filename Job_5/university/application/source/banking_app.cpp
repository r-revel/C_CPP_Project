#include "banking_app.hpp"
#include <iostream>

namespace banking {

BankingApp::BankingApp(IAccountRepository& repository)
    : bank_(repository),
      view_(),
      controller_(bank_, view_) {}

int BankingApp::run() {
    try {
        controller_.run();  // Запуск основного цикла
    } 
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Fatal error: unknown" << std::endl;
        return 1;
    }
    return 0;
}

} // namespace banking