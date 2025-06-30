#pragma once

#include <account.hpp>

#include <vector>
#include <memory>

namespace banking {

class IAccountRepository {
public:

	using account_id_t = unsigned long long;

	virtual ~IAccountRepository() = default;

	virtual std::vector<std::shared_ptr<IAccount>> get_all() = 0;

	virtual std::shared_ptr<IAccount> get(account_id_t id) = 0;

	virtual account_id_t add(std::shared_ptr<IAccount> account) = 0;

	virtual bool remove(account_id_t id) = 0;

};


}