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
	Admin::Admin()
	{
		_type = "admin";
		name = "DefaultAdmin";
		_password = cryptor("1");
	}
	Account* Admin::signUp()
	{
		Admin* admin = dynamic_cast<Admin*>(Account::signUp());
		if (admin)
		{
			ofstream fout("Admins.txt", ios_base::app);
			fout << *admin;
		}
		return admin;
	}

	void Admin::menu()
	{
		system("cls");
		cout << "\tМеню\n1. - Просмотреть каталог\n2. - Добавить видео в каталог\n3. - Редактировать видео из каталога"
			<< "\n4. - Удалить видео из каталога\n5. - Вывести информацию об аккаунте\nEsc. - Выйти из аккаунта" << endl;
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
				addVideo();
				break;
			}
			case '3':
			{
				system("cls");
				_store->showVideo();
				editVideo(_store->video(enterIndex("Введите номер видео для редактирования: ", _store->videoQuantity())));
				break;
			}
			case '4':
			{
				system("cls");
				showCatalog();
				deleteVideo();
				break;
			}
			case '5':
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
			cout << "\tМеню\n1. - Просмотреть каталог\n2. - Добавить видео в каталог\n3. - Редактировать видео из каталога"
				<< "\n4. - Удалить видео из каталога\n5. - Вывести информацию об аккаунте\nEsc. - Выйти из аккаунта" << endl;
		}
	}

	void Admin::addVideo()
	{
		system("cls");
		cout << "\tДобавление видео" << endl;
		_store->addVideo();
	}
	void Admin::deleteVideo()
	{
		system("cls");
		cout << "\tУдаление видео" << endl;
		_store->deleteVideo(enterIndex("Введите номер видоса для удаления: ", _store->videoQuantity()));
	}
	void Admin::editVideo(VideoStatus* video)
	{
		system("cls");
		cout << "\tРедактирование видоса (" << *video << ')' << endl;
		cout << "Что вы хотите изменить?\n1. - Изменить режисёра видео\n2. - Изменить название видео\n3. - Изменить жанры видео"
			<< "\n4. - Изменить стоимость видео\nEsc - Вернуться в предыдущее меню" << endl;
		while (true)
		{
			char ch = _getch();
			switch (ch)
			{
			case '1':
			{
				cout << "\nТекущий режисёр видео: " << video->video->author() << ". ";
				video->video->setAuthor(enterString("Введите нового режисёра: "));
				cout << "режисёр успешно обновлён" << endl;
				return;
			}
			case '2':
			{
				cout << "\nТекущее название видео: " << video->video->name() << ". ";
				video->video->setName(enterString("Введите новое название видео: "));
				cout << "Название успешно обновлёно" << endl;
				return;
			}
			case '3':
			{
				system("cls");
				cout << "\tРедактирование жанров видео" << endl;
				cout << "Что вы хотите сделать?\n1. - Добавить новый жанр\n2. - Изменить существующий жанр"
					<< "\n3. - Удалить существующий жанр\nEsc. - Не изменять ничего" << endl;
				vector<string> genre = video->video->genre();
				while (true)
				{
					char ch = _getch();
					switch (ch)
					{
					case '1': case '2': case '3':
					{
						cout << "\nЖанр этого видео: " << endl;
						int genreCounter = 0;
						for (auto genreIterator = genre.begin(); genreIterator != genre.end(); genreIterator++)
						{
							cout << ++genreCounter << ". " << *genreIterator << endl;
						}
						cout << endl;
						if (ch == '1')
						{
							string newGenre = enterString("Введите новый жанр для видео: ");
							if (!video->video->hasGenre(newGenre))
							{
								genre.push_back(newGenre);
								cout << "Жанр успешно добавлен" << endl;
							}
							else
							{
								cout << "У видео уже есть этот жанр" << endl;
							}
						}
						else if (ch == '2')
						{
							cout << "Какой жанр вы хотите изменить? ";
							int i = enterIndex("Жанр №", genreCounter);
							cout << "Текущий жанр: " << genre.at(i) << ". ";
							string newGenre = enterString("Новый жанр видео: ");
							if (!video->video->hasGenre(newGenre))
							{
								genre.at(i) = newGenre;
								cout << "Жанр видео успешно обновлён" << endl;
							}
							else
							{
								cout << "У видео уже есть этот жанр. Текущий жанр не был изменён" << endl;
							}
						}
						else if (ch == '3')
						{
							cout << "Какой жанр вы хотите удалить? ";
							int i = enterIndex("Жанр №", genreCounter);
							cout << "Жанр \"" << genre.at(i) << "\" был удалён." << endl;
							genre.erase(genre.begin() + i);
						}
						return;
					}
					case 27:
						return;
					default:
						continue;
					}
				}
				return;
			}
			case '4':
			{
				cout << "\nТекущая стоимость видео: " << video->video->price() << "$. ";
				video->video->setPrice(enterDouble("Новая стоимость видео: "));
				cout << "Стоимость успешно обновлена" << endl;
				return;
			}
			case 27:
				return;
			default:
				continue;
			}
			return;
		}
	}
	void Admin::info()
	{
		cout << "\nИнформация об аккаунте" << endl;
		cout << "Ваш текущий статус: администратор. Имя пользователя " << name << endl;
	}
}

