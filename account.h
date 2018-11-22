//account.h
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include "date.h"
#include "accumulator.h"


class Account
{
public:
	//Account(const Date &date, const std::string &id);
	//~Account() {}
	const std::string &getId() {return id;} //account numbers
	double getBalance() const {return balance;} //remain money
	static double getTotal() {return total;}
	void show() const;
private:
	std::string id;
	double balance;
	static double total;
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
