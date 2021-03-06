//account.cpp
#include "account.h"
#include <cmath>
#include <iostream>
#include <utility>

using namespace std;

//AccountRecord
AccountRecord::AccountRecord(const Date &date, Account *account, double amount, double balance, std::string &desc):
	date(date), account(account), amount(amount), balance(balance), desc(desc) {}

void AccountRecord::show() const
{
	date.show();
	cout << "\t#" << account->getId() << ends << amount << ends << balance << ends << desc << endl; 
}

double Account::total = 0;
RecordMap Account::recordMap;
//Account
Account::Account(const Date &date, const string &id): id(id), balance(0)
{
	date.show();
	cout << "\t#" << id << " is created." << endl;
	total++;
}

void Account::record(const Date &date, double amount, const string &desc)
{
	amount = floor(amount * 100 + 0.5) / 100;
	balance += amount;
	total += amount;
	date.show();
	cout << "\t#" << id << ends << amount << ends << balance << ends << desc << endl;
}
void Account::show() const {cout << "#" << id << "\tBalance: " << balance;}

void Account::error(const string &msg) const {cout << "Error (#" << id << "):" << msg << endl;}

void Account::query(const Date &begin, const Date &end)
{
	if (begin < end || begin == end )
	{
		auto it1 = recordMap.lower_bound(begin);
		auto it2 = recordMap.upper_bound(end);
		for (auto it = it1; it != it2; it++)
			it->second.show();
	}
}

//SavingsAccount
SavingsAccount::SavingsAccount(const Date &date, const string &id, double rate): Account(date, id), rate(rate), acc(date, 0) {}

void SavingsAccount::deposit(const Date &date, double amount, const string &desc)
{
	record(date, amount, desc);
	acc.change(date, getBalance());
}

void SavingsAccount::withdraw(const Date &date, double amount, const string &desc)
{
	if (amount > getBalance()) error("Error: not enough money!");
	else
	{
		record(date, -amount, desc);
		acc.change(date, getBalance());
	}
}

void SavingsAccount::settle(const Date &date)
{
	if (date.getMonth() == 1)
	{
		double interest = acc.getSum(date) * rate / (date - Date(date.getYear() - 1, 1, 1));
		//interest per year
		if (interest != 0) record(date, interest, "interest");
		acc.reset(date, getBalance());
	}

}

//Credit
CreditAccount::CreditAccount(const Date &date, const std::string &id, double credit, double rate, double fee): Account(date, id),
	credit(credit), rate(rate), fee(fee), acc(date, 0) {}

double CreditAccount::getDebt() const
{
	double balance = getBalance();
	if (balance < 0) return balance;
	else return 0;
}

void CreditAccount::deposit(const Date &date, double amount, const string &desc)
{
	record(date, amount, desc);
	acc.change(date, getDebt());
}

void CreditAccount::withdraw(const Date &date, double amount, const string &desc)
{
	if (amount - getBalance() > credit) error("Error: not enough money!");
	else
	{
		record(date, -amount, desc);
		acc.change(date, getDebt());
	}
}

void CreditAccount::settle(const Date &date) //each month's 1st day run this function
{
	double interest = acc.getSum(date) * rate;
	if (interest != 0) record(date, interest, "interest");
	if (date.getMonth() == 1) record(date, -fee, "annual fee");
	acc.reset(date, getDebt());
}

double CreditAccount::getAvailableCredit() const
{
	if (getBalance() < 0) return credit + getBalance();
	else return credit;
}

void CreditAccount::show() const
{
	Account::show();
	cout << "\tAvailable credit: " << getAvailableCredit();
}
