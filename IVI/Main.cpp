#include <iostream>
#include <conio.h>
#include <string>

#include "Videoo.h"   
#include "Account.h" 
#include "Crypt.h"   
#include "Store.h"   

using namespace std;
using namespace VideoStore;

namespace VideoStore
{
	void load(Store& store);
	void save(Store& store);
	bool accountExists(string name);
	void addAccount(Account* account);

	map<string, Account*> _users = map<string, Account*>();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	system("cls");
	Store store;

	load(store);

	Account::setStore(&store);

	unique_ptr<Account*> account;

	cout << "1. - ������������������\n2. - ����� � �������\n3. - ����� ��� �����\nEsc. - �����";
	while (true)
	{
		account = 0;
		char ch = _getch();
		switch (ch)
		{
		case '1':
		{
			system("cls");
			cout << "1. - ������������������ ��� ����������\n2. - ������������������ ��� �������������\nEsc. - ��������� � ������� ����\n";
			while (true)
			{
				ch = _getch();
				switch (ch)
				{
				case '1': case '2':
				{
					system("cls");
					cout << "\t����������� ������������" << endl;
					delete account.release();
					if (ch == '1')
					{
						account = make_unique<Account*>(new Customer());
					}
					else
					{
						account = make_unique<Account*>(new Admin());
					}
					account = make_unique<Account*>(move(*account)->signUp());
					if (*account)
					{
						cout << "\n����������� ������ �������" << endl;
						system("pause");
						(*account)->menu();
					}
					system("pause");
					delete account.release();
					break;
				}
				case 27:
					break;
				default:
					continue;
				}
				break;
			}
			break;
		}
		case '2':
		{
			system("cls");
			cout << "\t���� � �������" << endl;
			string name = enterString("������� ��� ������������: ");
			if (accountExists(name))
			{
				string password = enterPassword("������� ������: ");
				account = make_unique<Account*>(Account::login(name, password));
				if (*account)
				{
					cout << "\n����������� ������ �������" << endl;
					system("pause");
					(*account)->menu();
				}
				delete account.release();
			}
			else
			{
				cout << "������������ �� ������" << endl;
			}
			system("pause");
			break;
		}
		case '3':
		{
			account = make_unique<Account*>(new Guest());
			(*account)->menu();
			delete account.release();
			break;
		}
		case 27:
			system("cls");
			save(store);
			cout << "�� �������!!!" << endl;
			system("pause");
			return 0;
		default:
			continue;
		}
		system("cls");
		cout << "1. - ������������������\n2. - ����� � �������\n3. - ����� ��� �����\nEsc. - �����";
	}
}

namespace VideoStore
{
	void load(Store& store)
	{
		ifstream fin;
		fin.open("Admins.txt");
		while (fin && !fin.eof())
		{
			try
			{
				Admin* admin = new Admin();
				fin >> *admin;
				addAccount(admin);
				if (fin.peek() == ' ')
				{
					break;
				}
			}
			catch (...)
			{
				continue;
			}
		}
		fin.close();
		fin.open("Customers.txt");
		while (fin && !fin.eof())
		{
			try
			{
				if (!fin)
				{
					break;
				}
				Customer* customer = new Customer();
				fin >> *customer;
				if (!customer->_purchased.empty())
				{
					auto& purchased = customer->_purchased;
					for (unsigned int i = 0; i < purchased.size(); i++)
					{
						auto videoInStore = store.findVideo(purchased.at(i));
						if (videoInStore)
						{
							purchased.at(i) = videoInStore->video;
						}
					}
				}
				addAccount(customer);
				if (fin.peek() == ' ')
				{
					break;
				}
			}
			catch (...)
			{
				continue;
			}
		}
		return;
	}
	void save(Store& store)
	{
		ofstream out;
		out.open("Videoo.txt");
		for (auto video = store._videoo.begin(); video != store._videoo.end(); video++)
		{
			out << **video;
		}
		out.close();
		out.open("Admins.txt");
		for (auto user = _users.begin(); user != _users.end(); user++)
		{
			if ((*user).second->_type == "admin")
			{
				out << *(*user).second;
			}
		}
		out.close();
		out.open("Customers.txt");
		for (auto user = _users.begin(); user != _users.end(); user++)
		{
			if ((*user).second->_type == "customer")
			{
				out << *(*user).second;
			}
		}
		out.close();
	}

	bool accountExists(string name)
	{
		if (_users.find(name) != _users.end())
		{
			return true;
		}
		return false;
	}
	void addAccount(Account* account)
	{
		_users.insert(make_pair(account->name, account));
	}
}
