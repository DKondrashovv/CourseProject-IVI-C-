#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <map>
#include <vector>

#include "Account.h"

using namespace std;

namespace VideoStore
{
	Customer::Customer()
	{
		_type = "customer";
		name = "DefaultCustomer";
		_password = cryptor("1");
		_money = 0;
	}
	Account* Customer::signUp()
	{
		Customer* customer = dynamic_cast<Customer*>(Account::signUp());
		if (customer)
		{
			ofstream fout("Customers.txt", ios_base::app);
			fout << *customer;
		}
		return customer;
	}

	void Customer::menu()
	{
		system("cls");
		cout << "\t����\n1. - ����������� �������\n2. - ������ � ��������\n3. - ������ ����� �� �������"
			<< "\n4. - �������� ��������� ���������� �����\n5. - ������� ���������� �� ��������\nEsc. - ����� �� ��������" << endl;
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
				cout << "\t�������\n1. - �������� ����� � �������\n2. - ����������� �������" <<
					"\n3. - ������� ����� �� �������\n4. - �������� �������\nEsc - ��������� � ���������� ����" << endl;
				bool back = false;
				while (true)
				{
					char ch = _getch();
					switch (ch)
					{
					case '1':
					{
						system("cls");
						cout << "\t����������� ��������" << endl;
						if (_store->videoQuantity() <= 0)
						{
							cout << "������� ����" << endl;
							break;
						}
						_store->showVideo();
						int i = enterIndex("������� ����� ������ ��� ���������� � �������: ", _store->videoQuantity());
						addToCrate(_store->addToCrate(i));
						break;
					}
					case '2':
					{
						system("cls");
						showCrate();
						break;
					}
					case '3':
					{
						system("cls");
						if (!_crate.empty())
						{
							showCrate();
							cout << "����� ����� �� ������ ������� �� �������? ";
							deleteFromCrate(enterIndex("����� ����� ", _crate.size()));
						}
						else
						{
							cout << "���� ������� �����" << endl;
						}
						break;
					}
					case '4':
					{
						system("cls");
						cout << "\t������� �������" << endl;
						cout << "�� �������, ��� ������ �������� ������� (1/����� �������)?" << endl;
						if (_getch() == '1')
						{
							while (!_crate.empty())
							{
								deleteFromCrate(0);
							}
							cout << "������� ������� �������" << endl;
						}
						break;

					}
					case 27:
						back = true;
						break;
					default:
						continue;
					}
					if (back)
					{
						break;
					}
					system("pause");
					system("cls");
					cout << "\t�������\n1. - �������� ����� � �������\n2. - ����������� �������" <<
						"\n3. - ������� ����� �� �������\n4. - �������� �������\nEsc - ��������� � ���������� ����" << endl;
				}
				break;
			}
			case '3':
			{
				system("cls");
				cout << "\t�������" << endl;
				if (!_crate.empty())
				{
					cout << "����� ��������� ����� � ����� �������: " << totalPrice << "$, � ��� ���� " << _money << '$' << endl;
					if (totalPrice <= _money)
					{
						cout << "�� �������, ��� ������ ������ ��� ������ (1/����� �������)?" << endl;
						if (_getch() == '1')
						{
							buy();
							cout << "������ ������� �������" << endl;
						}
						else
						{
							cout << "������� ��������" << endl;
						}
					}
					else
					{
						cout << "� ��� ������������ ����� (����� ��� " << totalPrice - _money << "$)" << endl;
					}
				}
				else
				{
					cout << "���� ������� �����" << endl;
				}
				break;
			}
			case '4':
			{
				system("cls");
				cout << "\t���������" << endl;
				cout << "������ � ��� ���� " << _money << "$. ";
				_money = enterDouble("����� �����: ");
				cout << "���������� ����� ������� ���������" << endl;
				break;
			}
			case '5':
			{
				system("cls");
				info();
				break;
			}
			case 27:
				while (!_crate.empty())
				{
					deleteFromCrate(0);
				}
				return;
			default:
				continue;
			}
			system("pause");
			system("cls");
			cout << "\t����\n1. - ����������� �������\n2. - ������ � ��������\n3. - ������ ����� �� �������"
				<< "\n4. - �������� ��������� ���������� �����\n5. - ������� ���������� �� ��������\nEsc. - ����� �� ��������" << endl;
		}
	}

	void Customer::showCrate()
	{
		cout << "\t���� �������" << endl;
		if (_crate.empty())
		{
			cout << "�����" << endl;
			return;
		}
		else
		{
			for (unsigned int i = 0; i < _crate.size(); i++)
			{
				cout << i + 1 << ". " << *(_crate.at(i)) << endl;
			}
			cout << "����� ��������� ���� ���������: " << totalPrice << '$' << endl;
		}
	}

	void Customer::addToCrate(Video* video)
	{
		_crate.push_back(video);
		totalPrice += video->price();
		cout << "����� (" << *video << ") ������� ���������" << endl;
	}
	void Customer::deleteFromCrate(int index)
	{
		Video* video = _crate.at(index);
		totalPrice -= video->price();
		_store->returnVideo(video);
		_crate.erase(_crate.begin() + index);
	}
	void Customer::buy()
	{
		while (!_crate.empty())
		{
			_purchased.push_back(_crate.back());
			_crate.pop_back();
		}
		_money -= totalPrice;
	}
	void Customer::info()
	{
		cout << "\t���������� �� ��������" << endl;
		cout << "��� ������� ������: ����������. �� ������ ������������� ������� �������, ������ ��������� �������, �������" << endl;
		cout << "\n��� ������������: " << name << ", ���������� �����: " << _money << '$' << endl;
		cout << "\t�������� � �������:" << endl;
		if (_crate.empty())
		{
			cout << "�����������" << endl;
		}
		else
		{
			for (unsigned int i = 0; i < _crate.size(); i++)
			{
				cout << i + 1 << ". " << *_crate.at(i) << endl;
			}
		}
		cout << "\n\t��������� �������:" << endl;
		if (_purchased.empty())
		{
			cout << "�����������" << endl;
		}
		else
		{
			for (unsigned int i = 0; i < _purchased.size(); i++)
			{
				cout << i + 1 << ". " << *_purchased.at(i) << endl;
			}
		}
	}
}