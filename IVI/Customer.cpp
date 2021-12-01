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
		cout << "\tМеню\n1. - Просмотреть каталог\n2. - Работа с корзиной\n3. - Купить видео из корзины"
			<< "\n4. - Изменить имеющееся количество денег\n5. - Вывести информацию об аккаунте\nEsc. - Выйти из аккаунта" << endl;
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
				cout << "\tКорзина\n1. - Добавить видео в корзину\n2. - Просмотреть корзину" <<
					"\n3. - Удалить видео из корзины\n4. - Очистить корзину\nEsc - Вернуться в предыдущее меню" << endl;
				bool back = false;
				while (true)
				{
					char ch = _getch();
					switch (ch)
					{
					case '1':
					{
						system("cls");
						cout << "\tАссортимент магазина" << endl;
						if (_store->videoQuantity() <= 0)
						{
							cout << "Магазин пуст" << endl;
							break;
						}
						_store->showVideo();
						int i = enterIndex("Введите номер видоса для добавления в корзину: ", _store->videoQuantity());
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
							cout << "Какое видео вы хотите удалить из корзины? ";
							deleteFromCrate(enterIndex("Номер видео ", _crate.size()));
						}
						else
						{
							cout << "Ваша корзина пуста" << endl;
						}
						break;
					}
					case '4':
					{
						system("cls");
						cout << "\tОчистка корзины" << endl;
						cout << "Вы уверены, что хотите очистить корзину (1/Любая клавиша)?" << endl;
						if (_getch() == '1')
						{
							while (!_crate.empty())
							{
								deleteFromCrate(0);
							}
							cout << "Корзина успешно очищена" << endl;
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
					cout << "\tКорзина\n1. - Добавить видео в корзину\n2. - Просмотреть корзину" <<
						"\n3. - Удалить видео из корзины\n4. - Очистить корзину\nEsc - Вернуться в предыдущее меню" << endl;
				}
				break;
			}
			case '3':
			{
				system("cls");
				cout << "\tПокупка" << endl;
				if (!_crate.empty())
				{
					cout << "Общая стоимость видео в Вашей корзине: " << totalPrice << "$, у Вас есть " << _money << '$' << endl;
					if (totalPrice <= _money)
					{
						cout << "Вы уверены, что хотите купить все видосы (1/Любая клавиша)?" << endl;
						if (_getch() == '1')
						{
							buy();
							cout << "Видосы успешно куплены" << endl;
						}
						else
						{
							cout << "Покупка отменена" << endl;
						}
					}
					else
					{
						cout << "У вас недостаточно денег (нужно еще " << totalPrice - _money << "$)" << endl;
					}
				}
				else
				{
					cout << "Ваша корзина пуста" << endl;
				}
				break;
			}
			case '4':
			{
				system("cls");
				cout << "\tИнфокиоск" << endl;
				cout << "Сейчас у вас есть " << _money << "$. ";
				_money = enterDouble("Новая сумма: ");
				cout << "Количество денег успешно обновлено" << endl;
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
			cout << "\tМеню\n1. - Просмотреть каталог\n2. - Работа с корзиной\n3. - Купить видео из корзины"
				<< "\n4. - Изменить имеющееся количество денег\n5. - Вывести информацию об аккаунте\nEsc. - Выйти из аккаунта" << endl;
		}
	}

	void Customer::showCrate()
	{
		cout << "\tВаша корзина" << endl;
		if (_crate.empty())
		{
			cout << "Пуста" << endl;
			return;
		}
		else
		{
			for (unsigned int i = 0; i < _crate.size(); i++)
			{
				cout << i + 1 << ". " << *(_crate.at(i)) << endl;
			}
			cout << "Общая стоимость всех видосиков: " << totalPrice << '$' << endl;
		}
	}

	void Customer::addToCrate(Video* video)
	{
		_crate.push_back(video);
		totalPrice += video->price();
		cout << "Видео (" << *video << ") успешно добавлено" << endl;
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
		cout << "\tИнформация об аккаунте" << endl;
		cout << "Ваш текущий статус: покупатель. Вы можете просматривать каталог видосов, делать поисковые запросы, покупки" << endl;
		cout << "\nИмя пользователя: " << name << ", количество денег: " << _money << '$' << endl;
		cout << "\tВидосики в корзине:" << endl;
		if (_crate.empty())
		{
			cout << "Отсутствуют" << endl;
		}
		else
		{
			for (unsigned int i = 0; i < _crate.size(); i++)
			{
				cout << i + 1 << ". " << *_crate.at(i) << endl;
			}
		}
		cout << "\n\tКупленные видосов:" << endl;
		if (_purchased.empty())
		{
			cout << "Отсутствуют" << endl;
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