#include "in_memory_account_repository.hpp"

#include <ranges>
#include <stdexcept>
#include <format>

namespace banking {

    InMemoryAccountRepository::InMemoryAccountRepository(std::unordered_map<IAccountRepository::account_id_t, std::shared_ptr<IAccount>> accounts):
        accounts_(accounts) {}

    std::vector<std::shared_ptr<IAccount>> InMemoryAccountRepository::get_all() {
        auto value_view = std::views::values(accounts_);
        return std::vector<std::shared_ptr<IAccount>>{value_view.begin(), value_view.end()};
    }

    std::shared_ptr<IAccount> InMemoryAccountRepository::get(IAccountRepository::account_id_t id) {
        auto it = accounts_.find(id);
        if (it == accounts_.end()) {
            return nullptr;
        }
        return it->second;
    }

    IAccountRepository::account_id_t InMemoryAccountRepository::add(std::shared_ptr<IAccount> account) {
        auto id = next_id_++;
        accounts_[id] = account;
        return id;
    }

    bool InMemoryAccountRepository::remove(IAccountRepository::account_id_t id) {
        auto it = accounts_.find(id);
        if (it == accounts_.end()) {
            return false;
        }
        accounts_.erase(it);
        return true;
    }
}