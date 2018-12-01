#include "account.h"
#include <iostream>
#include <conio.h>
using namespace std;



int main()
{
	try
	{
		int index, day, amount;
		string desc;
		Date date(2008, 11, 1);
		SavingsAccount sa1(date, "S3755217", 0.015);
		SavingsAccount sa2(date, "02342342", 0.015);
		CreditAccount ca(date, "C5392394", 10000, 0.0005, 50);
		Account *accounts[] = {&sa1, &sa2, &ca};
		const int n = sizeof(accounts) / sizeof(Account*); //sum of accounts
		bool fl = true;
		while (fl)
		{
			cout << "Deposit(D) Withdraw(W) Show(S) Change_day(C) Next_month(N) Exit(E)" << endl;
			char cmd;
			date.show();
			cout << "\tTotal: " << Account::getTotal() << "\nCommand >>>";
			while (!kbhit());
			cmd = getch();
			cout << cmd << endl;
			switch (cmd)
			{
				case 'D': 	cout << "Please input your ID number and Amount of money and Info: ";
							cin >> index >> amount;
							if(index >= n) throw string("Invalid ID.");
							fflush(stdin); //clear Input Buffer also //cin.clear();cin.sync();
							getline(cin, desc);
							accounts[index]->deposit(date, amount, desc); break;
				case 'W': 	cout << "Please input your ID number and Amount of money and Info: ";
							cin >> index >> amount;
							if(index >= n) throw string("Invalid ID.");
							fflush(stdin); //clear Input Buffer also //cin.clear();cin.sync();
							getline(cin, desc);
							accounts[index]->withdraw(date, amount, desc); break;
				case 'S': 	for (int i = 0; i < n; i++)
							{
								cout << "[" << i << "]";
								accounts[i]->show();
								cout << endl;
							} break;
				case 'C': 	cout << "Please input a date number(<=31): ";
							cin >> day;
							if (day < date.getDay()) throw string("You cannot specify a previous day.");
							else if (day > date.getMaxDay()) throw string("Invalid Date.");
							else date = Date(date.getYear(), date.getMonth(), day); break;
				case 'N': 	if (date.getMonth() == 12) date = Date(date.getYear() + 1, 1, 1);
							else date = Date(date.getYear(), date.getMonth() + 1, 1);
							for (int i = 0; i < n; i++)
								accounts[i]->settle(date); break;
				case 'E': fl = false; break;
				default: throw string("Wrong Input.");
			}
		}
	}
	catch (string &st)
	{
		cout << "Error!" << st << endl;
	}

	// sa1.deposit(Date(2008, 11, 5), 5000, "salary");
	// ca.withdraw(Date(2008, 11, 15), 2000, "buy a cell");
	// sa2.deposit(Date(2008, 11, 25), 10000, "sell stock 0323");

	// ca.settle(Date(2008, 12, 1));

	// ca.deposit(Date(2008, 12, 1), 2016, "repay the credit");
	// sa1.deposit(Date(2008, 12, 5), 5500, "salary");

	// sa1.settle(Date(2009, 1, 1));
	// sa2.settle(Date(2009, 1, 1));
	// ca.settle(Date(2009, 1, 1));


	// cout << endl;
	// sa1.show();
	// cout << endl;
	// sa2.show();
	// cout << endl;
	// ca.show();
	// cout << endl;
	// cout << "Total: " << Account::getTotal() << endl;

	//system("pause");
	return 0;
}

