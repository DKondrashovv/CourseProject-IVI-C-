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
		cout << "Придумайте имя пользователя: ";
		cin >> name;
		if (accountExists(name))
		{
			cout << "Пользователь с таким именем уже существует" << endl;
			return nullptr;
		}
		_password = enterPassword("Придумайте пароль: ");
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
		cout << "\tАссортимент магазина" << endl;
		if (_store->videoQuantity() <= 0)
		{
			cout << "Ассортимент пуст" << endl;
			return;
		}
		_store->showVideo();
		cout << "\n\tДополнительные действия\n1. - Найти видео по запросу\n2. - Отсортировать видео\nEsc. - Вернуться в предыдущее меню" << endl;
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
				cout << "\tОтсортированный список видосиков" << endl;
				_store->sort();
				break;
			case 27:
				return;
			default:
				continue;
			}
			system("pause");
			system("cls");
			cout << "\tДополнительные действия\n1. - Найти видео по запросу\n2. - Отсортировать видео\nEsc. - Вернуться в предыдущее меню" << endl;
		}
	}
	void Account::find()
	{
		auto requested = _store->find(enterString("Введите поисковый запрос: "));
		if (requested.empty())
		{
			cout << "По вашему запросу ничего не найдено" << endl;
			return;
		}
		else
		{
			cout << "По вашему запросу найдены следующие результаты: " << endl;
			int i = 1;
			showList(requested);
			return;
		}
	}

	void Guest::menu()
	{
		system("cls");
		cout << "\tМеню\n1. - Просмотреть каталог\n2. - Вывести информацию об аккаунте\nEsc. - Выйти из аккаунта" << endl;
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
			cout << "\tМеню\n1. - Просмотреть каталог\n2. - Вывести информацию об аккаунте\nEsc. - Выйти из аккаунта" << endl;
		}
	}

	void Guest::info()
	{
		cout << "\tИнформация об аккаунте" << endl;
		cout << "Ваш текущий статус: гость. Вы можете только просматривать каталог и делать поисковые запросы (покупка доступна только после регистрации!!!!!)" << endl;
	}
}

