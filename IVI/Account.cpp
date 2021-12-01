#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <map>
#include <vector>

#include "Account.h"
#include "Store.h"
#include "Crypt.h"

using namespace std;

namespace VideoStore
{
	template <class Type>
	void showList(list<Type> toShow);

	bool accountExists(string name);
	void addAccount(Account* account);

	Account* Account::signUp()
	{
		cout << "���������� ��� ������������: ";
		cin >> name;
		if (accountExists(name))
		{
			cout << "������������ � ����� ������ ��� ����������" << endl;
			return nullptr;
		}
		_password = enterPassword("���������� ������: ");
		addAccount(this);
		return this;
	}
	Account* Account::login(string name, string password)
	{
		auto account = _users.find(name);
		if (account != _users.end())
		{
			if (account->second->_password == password)
			{
				return account->second;
			}
		}
		return nullptr;
	}

	Store* Account::_store = 0;
	void Account::setStore(Store* store)
	{
		_store = store;
	}

	void Account::showCatalog()
	{
		system("cls");
		cout << "\t����������� ��������" << endl;
		if (_store->videoQuantity() <= 0)
		{
			cout << "����������� ����" << endl;
			return;
		}
		_store->showVideo();
		cout << "\n\t�������������� ��������\n1. - ����� ����� �� �������\n2. - ������������� �����\nEsc. - ��������� � ���������� ����" << endl;
		while (true)
		{
			char ch = _getch();
			switch (ch)
			{
			case '1':
				system("cls");
				find();
				break;
			case '2':
				system("cls");
				cout << "\t��������������� ������ ���������" << endl;
				_store->sort();
				break;
			case 27:
				return;
			default:
				continue;
			}
			system("pause");
			system("cls");
			cout << "\t�������������� ��������\n1. - ����� ����� �� �������\n2. - ������������� �����\nEsc. - ��������� � ���������� ����" << endl;
		}
	}
	void Account::find()
	{
		auto requested = _store->find(enterString("������� ��������� ������: "));
		if (requested.empty())
		{
			cout << "�� ������ ������� ������ �� �������" << endl;
			return;
		}
		else
		{
			cout << "�� ������ ������� ������� ��������� ����������: " << endl;
			int i = 1;
			showList(requested);
			return;
		}
	}

	void Guest::menu()
	{
		system("cls");
		cout << "\t����\n1. - ����������� �������\n2. - ������� ���������� �� ��������\nEsc. - ����� �� ��������" << endl;
		while (true)
		{
			char ch = _getch();
			switch (ch)
			{
			case '1':
			{
				showCatalog();
				break;
			}
			case '2':
			{
				system("cls");
				info();
				break;
			}
			case 27:
				return;
			default:
				continue;
			}
			system("pause");
			system("cls");
			cout << "\t����\n1. - ����������� �������\n2. - ������� ���������� �� ��������\nEsc. - ����� �� ��������" << endl;
		}
	}

	void Guest::info()
	{
		cout << "\t���������� �� ��������" << endl;
		cout << "��� ������� ������: �����. �� ������ ������ ������������� ������� � ������ ��������� ������� (������� �������� ������ ����� �����������!!!!!)" << endl;
	}
}

