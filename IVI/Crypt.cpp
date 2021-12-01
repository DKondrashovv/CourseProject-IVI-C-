#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "Crypt.h"
#include "Store.h"

using namespace std;

namespace VideoStore
{
	string enterString(string message)
	{
		string str;
		cin.clear();
		do
		{
			cout << message;
			getline(cin, str, '\n');
			
			cin.clear();
			
		} while (str.empty());
		return str;
	}
	int enterInt(string message)
	{
		cout << message;
		int value;
		cin.clear();
		noskipws(cin);
		while (!(cin >> value) || value < 0)
		{
			cout << "Ошибка. Введите корректное значение\n" << message;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		skipws(cin);
		cin.clear();
		return value;
	}
	int enterIndex(string message, int maxValue)
	{
		cout << message;
		int value;
		cin.clear();
		noskipws(cin);
		while (!(cin >> value) || value < 1 || value > maxValue)
		{
			cout << "Ошибка. Введите корректное значение\n" << message;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		skipws(cin);
		cin.clear();
		return --value;
	}
	double enterDouble(string message)
	{
		cout << message;
		double value;
		cin.clear();
		noskipws(cin);
		while (!(cin >> value) || value < 0)
		{
			cout << "Ошибка. Введите корректное значение\n" << message;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		skipws(cin);
		cin.clear();
		return value;
	}
	string stringToLower(string str)
	{
		int size = str.size();
		int offsetCyrillic = 'А' - 'а'; 
		int offsetLatin = 'A' - 'a'; 
		for (int i = 0; i < size; i++)
		{
			if (str[i] >= 'А' && str[i] <= 'Я')
			{
				str[i] -= offsetCyrillic;
			}
			else if (str[i] >= 'A' && str[i] <= 'Z')
			{
				str[i] -= offsetLatin;
			}
		}
		return str;
	}

	string enterPassword(string message)
	{
		cout << message;
		string buff;
		char ch = 0;
		int i = 0;
		while (true)
		{
			ch = _getch();
			switch (ch)
			{
			case 13:
				if (!buff.empty())
				{
					cout << '\n';
					return cryptor(buff);
				}
			case '\b':
				if (!buff.empty())
				{
					cout << "\b \b";
					buff.pop_back();
				}
				break;
			default:
				if (ch > 31)
				{
					cout << '*';
					buff.push_back(ch);
				}
				break;
			}
		}
	}

	string cryptor(string toCrypt)
	{
		string cryptor = "Danik";
		int cryptorSize = cryptor.size();
		int toCryptSize = toCrypt.size();
		for (int i = 0; i < toCryptSize; i++)
		{
			toCrypt[i] ^= cryptor[i % cryptor.size()];
		}
		return toCrypt;
	}

	template<typename Type>
	extern void showList(list<Type> toShow);
}