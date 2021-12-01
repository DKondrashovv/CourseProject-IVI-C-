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
		cout << "\t����\n1. - ����������� �������\n2. - �������� ����� � �������\n3. - ������������� ����� �� ��������"
			<< "\n4. - ������� ����� �� ��������\n5. - ������� ���������� �� ��������\nEsc. - ����� �� ��������" << endl;
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
				editVideo(_store->video(enterIndex("������� ����� ����� ��� ��������������: ", _store->videoQuantity())));
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
			cout << "\t����\n1. - ����������� �������\n2. - �������� ����� � �������\n3. - ������������� ����� �� ��������"
				<< "\n4. - ������� ����� �� ��������\n5. - ������� ���������� �� ��������\nEsc. - ����� �� ��������" << endl;
		}
	}

	void Admin::addVideo()
	{
		system("cls");
		cout << "\t���������� �����" << endl;
		_store->addVideo();
	}
	void Admin::deleteVideo()
	{
		system("cls");
		cout << "\t�������� �����" << endl;
		_store->deleteVideo(enterIndex("������� ����� ������ ��� ��������: ", _store->videoQuantity()));
	}
	void Admin::editVideo(VideoStatus* video)
	{
		system("cls");
		cout << "\t�������������� ������ (" << *video << ')' << endl;
		cout << "��� �� ������ ��������?\n1. - �������� ������� �����\n2. - �������� �������� �����\n3. - �������� ����� �����"
			<< "\n4. - �������� ��������� �����\nEsc - ��������� � ���������� ����" << endl;
		while (true)
		{
			char ch = _getch();
			switch (ch)
			{
			case '1':
			{
				cout << "\n������� ������ �����: " << video->video->author() << ". ";
				video->video->setAuthor(enterString("������� ������ �������: "));
				cout << "������ ������� �������" << endl;
				return;
			}
			case '2':
			{
				cout << "\n������� �������� �����: " << video->video->name() << ". ";
				video->video->setName(enterString("������� ����� �������� �����: "));
				cout << "�������� ������� ��������" << endl;
				return;
			}
			case '3':
			{
				system("cls");
				cout << "\t�������������� ������ �����" << endl;
				cout << "��� �� ������ �������?\n1. - �������� ����� ����\n2. - �������� ������������ ����"
					<< "\n3. - ������� ������������ ����\nEsc. - �� �������� ������" << endl;
				vector<string> genre = video->video->genre();
				while (true)
				{
					char ch = _getch();
					switch (ch)
					{
					case '1': case '2': case '3':
					{
						cout << "\n���� ����� �����: " << endl;
						int genreCounter = 0;
						for (auto genreIterator = genre.begin(); genreIterator != genre.end(); genreIterator++)
						{
							cout << ++genreCounter << ". " << *genreIterator << endl;
						}
						cout << endl;
						if (ch == '1')
						{
							string newGenre = enterString("������� ����� ���� ��� �����: ");
							if (!video->video->hasGenre(newGenre))
							{
								genre.push_back(newGenre);
								cout << "���� ������� ��������" << endl;
							}
							else
							{
								cout << "� ����� ��� ���� ���� ����" << endl;
							}
						}
						else if (ch == '2')
						{
							cout << "����� ���� �� ������ ��������? ";
							int i = enterIndex("���� �", genreCounter);
							cout << "������� ����: " << genre.at(i) << ". ";
							string newGenre = enterString("����� ���� �����: ");
							if (!video->video->hasGenre(newGenre))
							{
								genre.at(i) = newGenre;
								cout << "���� ����� ������� �������" << endl;
							}
							else
							{
								cout << "� ����� ��� ���� ���� ����. ������� ���� �� ��� ������" << endl;
							}
						}
						else if (ch == '3')
						{
							cout << "����� ���� �� ������ �������? ";
							int i = enterIndex("���� �", genreCounter);
							cout << "���� \"" << genre.at(i) << "\" ��� �����." << endl;
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
				cout << "\n������� ��������� �����: " << video->video->price() << "$. ";
				video->video->setPrice(enterDouble("����� ��������� �����: "));
				cout << "��������� ������� ���������" << endl;
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
		cout << "\n���������� �� ��������" << endl;
		cout << "��� ������� ������: �������������. ��� ������������ " << name << endl;
	}
}

