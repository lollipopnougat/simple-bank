#include "account.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;


struct deleter
{
	template<typename T> 
	void operator () (T *p) {delete p;}
};

int main()
{
	int index, day;
	double amount, credit, rate, fee;
	string id, desc;
	char type;
	try
	{
		Date date(2008, 11, 1);
		vector<Account*> accounts;
		Account *account;
		Date date1, date2;
		bool fl = true;
		while (fl)
		{
			cout << "Add_account(A) Deposit(D) Withdraw(W) Show(S) Change_day(C) Next_month(N) Query(Q) Exit(E)" << endl;
			char cmd;
			date.show();
			cout << "\tTotal: " << Account::getTotal() << "\nCommand >>>";
			while (!kbhit());
			cmd = getch();
			cout << cmd << endl;
			switch (cmd)
			{
				case 'A':	cout << "Please select a type('S' for Saving Others for Credit) and Input your ID: " << endl;
							cin >> type >> id;
							if (type == 'S' || type == 's') 
							{
								cout << "Please input rate: ";
								cin >> rate;
								account = new SavingsAccount(date, id, rate);
							}
							else 
							{
								cout << "Please input credit rate and fee: ";
								cin >> credit >> rate >> fee;
								account = new CreditAccount(date, id, credit, rate, fee);
							}
							accounts.push_back(account); break;
				case 'D': 	cout << "Please input your ID number and Amount of money and Info: ";
							cin >> index >> amount;
							if(index >= accounts.size()) throw string("Invalid ID.");
							fflush(stdin); //clear Input Buffer also //cin.clear();cin.sync();
							getline(cin, desc);
							accounts[index]->deposit(date, amount, desc); break;
				case 'W': 	cout << "Please input your ID number and Amount of money and Info: ";
							cin >> index >> amount;
							if(index >= accounts.size()) throw string("Invalid ID.");
							fflush(stdin); //clear Input Buffer also //cin.clear();cin.sync();
							getline(cin, desc);
							accounts[index]->withdraw(date, amount, desc); break;
				case 'S': 	for (int i = 0; i < accounts.size(); i++)
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
							for (auto it = accounts.begin(); it != accounts.end(); it++)
								(*it)->settle(date); break;
				case 'E':	fl = false; break;
				case 'Q':	date1 = Date::read();
							date2 = Date::read();
							Account::query(date1, date2); break;
				default: throw string("Wrong Input.");
			}
		}
		for_each (accounts.begin(), accounts.end(),deleter());
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

