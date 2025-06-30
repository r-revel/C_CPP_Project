#include "banking_app.hpp"

// Необходимо подключить
#include <text_ui_controller.hpp>
#include <in_memory_account_repository.hpp>

int main(int argc, char const *argv[])
{
	banking::InMemoryAccountRepository repo;  // Реальная реализация IAccountRepository
	banking::BankingApp app(repo);    // Передаём репозиторий
	app.run();
	return app.run();
}