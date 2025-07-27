#pragma once
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <thread>

namespace smart_home {

class CliView {
public:
    CliView();
    ~CliView();

    // Инициализация/очистка экрана
    void init();
    void cleanup();

    // Основное меню
    void show_menu();
    int get_menu_choice();

    // Ввод данных
    std::string get_input(const std::string& prompt);
    void clear_input();

    // Отображение информации
    void show_speakers_list(const std::vector<std::pair<std::string, std::string>>& speakers);
    void show_devices_list(const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& devices);
    
    // Сообщения
    void show_message(const std::string& message);
    void show_error(const std::string& error);
    void show_warning(const std::string& warning);
    
    // Подтверждения
    bool get_confirmation(const std::string& question);

private:
    void init_colors();
    void draw_borders();
    void clear_main();
};

} // namespace smart_home