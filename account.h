//account.h
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <map>
#include "date.h"
#include "accumulator.h"

class Account;
class AccountRecord
{
public:
	AccountRecord(const Date &date, Account *account, double amount, double balance, std::string &desc);
	~AccountRecord() {}
	void show() const;
private:
	Date date;
	Account *account;
	double amount;
	double balance;
	std::string desc;
};
typedef std::multimap<Date, AccountRecord> RecordMap;

class Account
{
public:
	//Account(const Date &date, const std::string &id);
	//~Account() {}
	std::string &getId() {return id;} //account numbers
	double getBalance() const {return balance;} //remain money
	static double getTotal() {return total;}
	virtual void deposit(const Date &date, double amount, const std::string &desc) = 0; //put money in
	virtual void withdraw(const Date &date, double amount, const std::string &desc) = 0; //take money back
	virtual void settle(const Date &date) = 0; //calculate interest
	virtual void show() const;
	static void query(const Date &begin, const Date &end);
private:
	std::string id;
	double balance;
	static double total;
	static RecordMap recordMap;
protected:
	Account(const Date &date, const std::string &id); //bulid function for Derived Class
	void record(const Date &date, double amount, const std::string &desc);
	void error(const std::string &msg) const;

};

class SavingsAccount: public Account
{
public:
	SavingsAccount(const Date &date, const std::string &id, double rate);
	~SavingsAccount() {}
	double getRate() const {return rate;}
	void deposit(const Date &date, double amount, const std::string &desc); //put money in
	void withdraw(const Date &date, double amount, const std::string &desc); //take back money
	void settle(const Date &date); //calculate interest
private:
	Accumulator acc;
	double rate;
};

class CreditAccount: public Account
{
public:
	CreditAccount(const Date &date, const std::string &id, double credit, double rate, double fee);
	~CreditAccount() {}
	double getCredit() {return credit;}
	double getRate() const {return rate;}
	double getFee() const {return fee;}
	double getAvailableCredit() const;
	void deposit(const Date &date, double amount, const std::string &desc); //put money in
	void withdraw(const Date &date, double amount, const std::string &desc); //take back money
	void settle(const Date &date); //calculate interest and fee per year
	void show() const;
private:
	Accumulator acc;
	double credit;
	double rate;
	double fee;
	double getDebt() const;
};

#endif
