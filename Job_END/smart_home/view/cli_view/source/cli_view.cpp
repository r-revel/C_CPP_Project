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
    
    std::cout << "\n\tГЛАВНОЕ МЕНЮ\n\n";
    std::cout << "1. Список всех колонок\n";
    std::cout << "2. Устройства в комнате\n";
    std::cout << "3. Управление устройством\n";
    std::cout << "4. Добавить устройство\n";
    std::cout << "5. Статус системы\n";
    std::cout << "6. Включения и отключения устройства\n";
    std::cout << "7. Проверить устройства в колонке\n";
    std::cout << "8. Выход\n\n";
}

int CliView::get_menu_choice() {
    std::cout << "Введите (1-8): ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    return (choice >= 1 && choice <= 8) ? choice : -1;
}

std::string CliView::get_input(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}


void CliView::show_speakers_list(const SmartHome& speakers) {
    clear_main();
    
    std::cout << speakers;
    std::cout << "\n";
}

void CliView::show_devices_list(const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& devices) {
    clear_main();
    
    if (devices.empty()) {
        show_message("Устройства не найдены");
        return;
    }

    // Заголовок
    std::cout << "\n\t=== СПИСОК УСТРОЙСТВ ===\n\n";
    std::cout << "ID\tИмя устройства\t\tСтатус\t\tТип устройства\n";
    std::cout << std::string(70, '-') << "\n";

    // Рассчитываем необходимое количество табов для выравнивания
    auto calculate_tabs = [](const std::string& str, int reference_len) {
        int tabs_needed = (reference_len - str.length()) / 8 + 1;
        return std::max(1, tabs_needed);
    };

    // Выводим данные
    for (const auto& [id, name, status, type] : devices) {
        std::cout << id;
        std::cout << std::string(calculate_tabs(id, 8), '\t');

        std::cout << name;
        std::cout << std::string(calculate_tabs(name, 18), '\t');

        // Статус с цветом
        if (status == "Онлайн") {
            std::cout << "\033[1;32m" << status << "\t" << "\033[0m";
        } else {
            std::cout << "\033[1;31m" << status << "\t" << "\033[0m";
        }
        std::cout << std::string(calculate_tabs(status, 7), '\t');

        // Тип устройства
        std::cout << type << "\n";
    }
    std::cout << "\n";
}

void CliView::show_message(const std::string& message) {
    clear_main();
    std::cout << "\n\n\t" << message << "\n\n";
    std::cout << "\tНажмите Enter для продолжения";
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