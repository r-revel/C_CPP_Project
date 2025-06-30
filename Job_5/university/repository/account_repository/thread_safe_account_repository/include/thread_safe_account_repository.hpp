#pragma once

#include <account_repository.hpp>
#include <shared_mutex>

namespace banking {

class ThreadSafeAccountRepository: public IAccountRepository {
public:
	ThreadSafeAccountRepository(std::unique_ptr<IAccountRepository> base);

	std::vector<std::shared_ptr<IAccount>> get_all() override;

	std::shared_ptr<IAccount> get(account_id_t id) override;

	account_id_t add(std::shared_ptr<IAccount> account) override;

	bool remove(account_id_t id) override;

	const std::unique_ptr<IAccountRepository>& get_base() const;

private:
	std::unique_ptr<IAccountRepository> base_;

	std::shared_mutex mutex_;
};


}