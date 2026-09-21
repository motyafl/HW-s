#include<iostream>
#include<string>

class TaxInspector;
class BankAccount {
friend class TaxInspector;
private:
	double balance;
	enum class status {
		ACTIVE,
		FROZEN,
		CLOSED
	};
	status acc_status;
	struct { std::string name; int id; } acc_owner;
public:
	BankAccount( std::string n, int i ) : balance{0}, acc_status{status::ACTIVE} {
	acc_owner.name=n;
	acc_owner.id=i; };

	void deposit( double amount ) {
		std::cout << "Вы внесли $" << amount << " на ваш счет " << acc_owner.id << std::endl;
		balance += amount;
	}

	void withdraw( double amount ) {
		std::cout << "Вы сняли $" << amount << " с вашего счета " << acc_owner.id << std::endl;
		balance -= amount;
	}

	friend double audit_accounts( const BankAccount*, size_t);
};

double audit_accounts ( const BankAccount* acc, size_t quant) {
	int bank_balance{}, q=quant; const BankAccount* p = acc;
	while (q--) { bank_balance += p++->balance; }
	return bank_balance;
}

class TaxInspector {
public:
    	void inspect_acc(const BankAccount& acc) const {
        	std::cout << "Inspection: Account Owner: " << acc.acc_owner.name << " Balance: $" << acc.balance << "\n";
	}

	void freeze_acc(BankAccount& acc) const {
        	acc.acc_status = BankAccount::status::FROZEN;
		std::cout << "Inspector заморозил аккаунт пользователя " << acc.acc_owner.name << std::endl;
	}

	void unfreeze_acc(BankAccount& acc) const {
		acc.acc_status = BankAccount::status::ACTIVE;
		std::cout << "Inspector разморозил аккаунт пользователя " << acc.acc_owner.name << std::endl;
	}
};

int main()
{
	BankAccount my_acc("Mira", 1243);
	BankAccount new_acc("Igor", 2848);
	my_acc.deposit(300);
	new_acc.deposit(3700);

	BankAccount arr[2] = {my_acc, new_acc};
	std::cout << "Bank audit: $" << audit_accounts( arr, 2 ) << std::endl;

	TaxInspector inspector;
	inspector.inspect_acc(new_acc);
	inspector.freeze_acc(new_acc);
}

