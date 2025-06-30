#pragma once

#include <account_repository.hpp>

#include <vector>
#include <memory>
#include <unordered_map>

namespace banking {

class InMemoryAccountRepository: public IAccountRepository {
public:
	InMemoryAccountRepository() = default;

	explicit InMemoryAccountRepository(std::unordered_map<account_id_t, std::shared_ptr<IAccount>> accounts);

	std::vector<std::shared_ptr<IAccount>> get_all() override;

	std::shared_ptr<IAccount> get(account_id_t id) override;

	account_id_t add(std::shared_ptr<IAccount> account) override;

	bool remove(account_id_t id) override;

private:
	std::unordered_map<account_id_t, std::shared_ptr<IAccount>> accounts_;
	account_id_t next_id_ = 0;

};


}