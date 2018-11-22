//4.9.cpp
#include <iostream>
#include <cmath>
using namespace std;

class SavingsAcount
{
public:
	SavingsAcount(int date, int id, double rate);
	~SavingsAcount() {}
	int getId() {return id;} //account numbers
	double getRate() {return rate;} //rate per year
	double getBalance() {return balance;} //remain money
	void deposit(int date, double amount); //put money in
	void withdraw(int date, double amount); //take back money
	void settle(int date); //calculate interest
	void show();
private:
	int id;
	double balance;
	double rate;
	int lastDate; //last interest change
	double accumulation; //sum of balance per day
	void record(int date, double amount);
	double accumulate(int date) const {return accumulation + balance * (date - lastDate);}
};


SavingsAcount::SavingsAcount(int date, int id, double rate): id(id), balance(0), lastDate(0), accumulation(0)
{
	cout << "Date " << date << "\t#" << id << " is created." << endl;
}

void SavingsAcount::record(int date, double amount)
{
	accumulation = accumulate(date);
	lastDate = date;
	amount = floor(amount * 100 + 0.5) / 100;
	balance += amount;
	cout << "Date " << date << "\t#" << id << ends << amount << ends << balance << endl;
}

void SavingsAcount::deposit(int date, double amount)
{
	record(date, amount);
}

void SavingsAcount::withdraw(int date, double amount)
{
	if (amount > getBalance()) cout << "Error: not enough money!" << endl;
	else record(date, -amount);
}

void SavingsAcount::settle(int date)
{
	double interest = accumulate(date) * rate / 365;
	if (interest != 0) record(date, interest);
	accumulation = 0;
}

void SavingsAcount::show()
{
	cout << "#" << id << "\tBalance: " << balance << endl;
}

int main()
{
	SavingsAcount sa0(1, 21325302, 0.015);
	SavingsAcount sa1(1, 58320212, 0.015);

	sa0.deposit(5, 5000);
	sa1.deposit(25, 10000);
	sa0.deposit(45, 5500);
	sa1.withdraw(60, 4000);

	sa0.settle(90);
	sa1.settle(90);

	sa0.show();
	sa1.show();

	system("pause");
	return 0;

}
