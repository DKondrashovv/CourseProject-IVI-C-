#pragma once

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <map>
#include <vector>	

#include "Crypt.h"
#include "Videoo.h"

using namespace std;

namespace VideoStore
{
	Video::Video()
	{
		_author = "DefaultAuthor";
		_name = "DefaultName";
		_genre.push_back("defaultGenre");
		_price = 0;
	}
	Video::Video(const Video& other)
	{
		_author = other._author;
		_name = other._name;
		_genre = other._genre;
		_price = other._price;
	}

	void Video::setAuthor()
	{
		_author = enterString("Введите имя режисёра видео: ");
	}
	void Video::setAuthor(string author)
	{
		_author = author;
	}
	void Video::setName()
	{
		_name = enterString("Введите название видео: ");
	}
	void Video::setName(string name)
	{
		_name = name;
	}
	void Video::setGenre()
	{
		if (*(_genre.begin()) == "defaultGenre")
		{
			_genre.erase(_genre.begin());
		}
		char ch;
		do
		{
			string genre = enterString("Жанр видоса: ");
			if (!hasGenre(genre))
			{
				_genre.push_back(genre);
				cout << "Добавить ещё один жанр? (1/Любая клавиша)" << endl;
			}
			else
			{
				cout << "У видоса уже есть такой жанр" << endl;
			}
			ch = _getch();
		} while (ch == '1');
	}
	void Video::setGenre(string genre)
	{
		if (*(_genre.begin()) == "defaultGenre")
		{
			_genre.erase(_genre.begin());
		}
		_genre.push_back(genre);
	}
	void Video::setPrice()
	{
		_price = enterDouble("Стоимость видоса: ");
	}

	void Video::setPrice(double price)
	{
		_price = price;
	}

	string Video::author()
	{
		return _author;
	}
	string Video::name()
	{
		return _name;
	}
	vector<string>& Video::genre()
	{
		return _genre;
	}
	string Video::genre(int genreNumber)
	{
		return _genre.at(genreNumber);
	}
	double Video::price()
	{
		return _price;
	}

	bool Video::hasGenre(string genreToCompare)
	{
		for (auto genre = _genre.begin(); genre != _genre.end(); genre++)
		{
			if (stringToLower(*genre) == stringToLower(genreToCompare))
			{
				return true;
			}
		}
		return false;
	}

	bool Video::operator< (Video* other)
	{
		if (_author < other->_author)
		{
			return true;
		}
		if (_name < other->_name)
		{
			return true;
		}
		return false;
	}
	bool Video::operator> (Video* other)
	{
		if (_author > other->_author)
		{
			return true;
		}
		if (_name > other->_name)
		{
			return true;
		}
		return false;
	}
	bool Video::operator== (Video* other)
	{
		if (_author == other->_author && _name == other->_name)
		{
			return true;
		}
		return false;
	}
}