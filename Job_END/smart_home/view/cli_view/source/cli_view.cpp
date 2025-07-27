#include "cli_view.hpp"


namespace smart_home {

CliView::CliView() {}
CliView::~CliView() {}

void CliView::init() {
    std::cout << "\033[2J\033[H"; // Clear screen
}

void CliView::cleanup() {
    std::cout << "\033[2J\033[H"; // Clear screen on exit
}

void CliView::draw_borders() {
    // Simulate borders with text output
    int width = 80; // Default terminal width
    std::cout << "+" << std::string(width-2, '-') << "+\n";
}

void CliView::clear_main() {
    std::cout << "\033[2J\033[H"; // Clear screen
    draw_borders();
}

void CliView::show_menu() {
    clear_main();
    
    std::cout << "\n\tMAIN MENU\n\n";
    std::cout << "1. List all smart speakers\n";
    std::cout << "2. Show room devices\n";
    std::cout << "3. Control device\n";
    std::cout << "4. Check status\n";
    std::cout << "5. Exit\n\n";
}

int CliView::get_menu_choice() {
    std::cout << "Enter choice (1-5): ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    return (choice >= 1 && choice <= 5) ? choice : -1;
}

std::string CliView::get_input(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void CliView::clear_input() {
    // Not needed in simple terminal version
}

void CliView::show_speakers_list(const std::vector<std::pair<std::string, std::string>>& speakers) {
    clear_main();
    
    if (speakers.empty()) {
        show_message("No speakers found");
        return;
    }
    
    std::cout << "\n\tSMART SPEAKERS LIST\n\n";
    std::cout << std::left << std::setw(30) << "Room" << "Type\n";
    std::cout << std::string(50, '-') << "\n";
    
    for (const auto& [room, type] : speakers) {
        std::cout << std::left << std::setw(30) << room << type << "\n";
    }
    std::cout << "\n";
}

void CliView::show_devices_list(const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& devices) {
    clear_main();
    
    if (devices.empty()) {
        show_message("No devices found");
        return;
    }
    
    std::cout << "\n\tDEVICES LIST\n\n";
    std::cout << std::left << std::setw(15) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(15) << "Status" 
              << "Type\n";
    std::cout << std::string(60, '-') << "\n";
    
    for (const auto& [id, name, status, type] : devices) {
        std::cout << std::left << std::setw(15) << id 
                  << std::setw(20) << name;
        
        if (status == "Online") {
            std::cout << "\033[1;36m" << std::setw(15) << status << "\033[0m";
        } else {
            std::cout << "\033[1;31m" << std::setw(15) << status << "\033[0m";
        }
        
        std::cout << type << "\n";
    }
    std::cout << "\n";
}

void CliView::show_message(const std::string& message) {
    clear_main();
    std::cout << "\n\n\t" << message << "\n\n";
    std::cout << "\tPress Enter to continue";
    std::cin.ignore();
}

void CliView::show_error(const std::string& error) {
    std::cout << "\033[1;31mERROR: " << error << "\033[0m\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void CliView::show_warning(const std::string& warning) {
    std::cout << "\033[1;33mWARNING: " << warning << "\033[0m\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

bool CliView::get_confirmation(const std::string& question) {
    std::cout << question << " (y/n): ";
    char answer;
    std::cin >> answer;
    std::cin.ignore();
    return (tolower(answer) == 'y');
}

} // namespace smart_home