#include "account.h"
#include <iostream>
using namespace std;

int main()
{
	Date date(2008, 11, 1);
	SavingsAccount sa1(date, "S3755217", 0.015);
	SavingsAccount sa2(date, "02342342", 0.015);
	CreditAccount ca(date, "C5392394", 10000, 0.0005, 50);
	//const int n = sizeof(accounts) / sizeof(SavingsAcount); //sum of accounts

	sa1.deposit(Date(2008, 11, 5), 5000, "salary");
	ca.withdraw(Date(2008, 11, 15), 2000, "buy a cell");
	sa2.deposit(Date(2008, 11, 25), 10000, "sell stock 0323");

	ca.settle(Date(2008, 12, 1));

	ca.deposit(Date(2008, 12, 1), 2016, "repay the credit");
	sa1.deposit(Date(2008, 12, 5), 5500, "salary");

	sa1.settle(Date(2009, 1, 1));
	sa2.settle(Date(2009, 1, 1));
	ca.settle(Date(2009, 1, 1));


	cout << endl;
	sa1.show();
	cout << endl;
	sa2.show();
	cout << endl;
	ca.show();
	cout << endl;
	cout << "Total: " << Account::getTotal() << endl;

	system("pause");
	return 0;

}
