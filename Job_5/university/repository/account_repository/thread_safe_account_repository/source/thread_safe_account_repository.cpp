#include "thread_safe_account_repository.hpp"

#include <mutex>

namespace banking {

    ThreadSafeAccountRepository::ThreadSafeAccountRepository(std::unique_ptr<IAccountRepository> base): base_(std::move(base)) 
    {}

    std::vector<std::shared_ptr<IAccount>> ThreadSafeAccountRepository::get_all() {
        std::shared_lock lock(mutex_);
        return base_->get_all();
    }

    std::shared_ptr<IAccount> ThreadSafeAccountRepository::get(IAccountRepository::account_id_t id) {
        std::shared_lock lock(mutex_);
        return base_->get(id);
    }

    IAccountRepository::account_id_t ThreadSafeAccountRepository::add(std::shared_ptr<IAccount> account) {
        std::shared_lock lock(mutex_);
        return base_->add(account);
    }

    const std::unique_ptr<IAccountRepository>& ThreadSafeAccountRepository::get_base() const {
        return base_;
    }

    bool ThreadSafeAccountRepository::remove(IAccountRepository::account_id_t id) {
        std::scoped_lock lock(mutex_);
        return base_->remove(id);
    }
}