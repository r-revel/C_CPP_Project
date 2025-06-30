#pragma once

#include <text_ui_controller.hpp>
#include <banking_service.hpp>
#include <text_ui_view.hpp>

namespace banking {

class BankingApp {
public:
    explicit BankingApp(IAccountRepository& repository);
    int run();  
private:
    BankingService bank_;   
    TextUIView view_;         
    TextUIController controller_;  
};

} // namespace banking

// #pragma once

// #include <controller.hpp>
// #include <memory>
// #include <json/json.h>
// #include <filesystem>


// namespace banking {

// class BankingApp {
// public:
//     int run(int argc, char const *argv[]);

// private:

//     static std::unique_ptr<IAppBuilder> load(int argc, char const *argv[]);

//     static Json::Value read_config(const std::filesystem::path& path);

//     static Json::Value init_config(const std::filesystem::path& path);

//     static constexpr std::string default_config = "./config.json";

// };

// } // namespace banking
