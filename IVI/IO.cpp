#include "Videoo.h"
#include "Account.h"

using namespace std;

namespace VideoStore
{
	ostream& operator<< (ostream& out, Video& video)
	{
		out << video._author << ", \"" << video._name << "\" (";
		for (auto genre = video._genre.begin(); genre != video._genre.end() - 1; genre++)
		{
			out << *genre << ", ";
		}
		out << *(video._genre.end() - 1) << ") за " << video._price << "$.";
		return out;
	}
	ofstream& operator<< (ofstream& out, Video& video)
	{
		out << video._author << '|' << video._name << '|';
		for (string str : video._genre)
		{
			out << str << ',';
		}
		out << '|' << video._price << '|';
		return out;
	}
	ifstream& operator>> (ifstream& fin, Video& video)
	{
		try
		{
			getline(fin, video._author, '|');
			getline(fin, video._name, '|');
			string buff;
			if (fin.peek() != ',')
			{
				video._genre.clear();
				do
				{
					getline(fin, buff, ',');
					video._genre.push_back(buff);
				} while (fin.peek() != '|' && fin);
				fin.ignore(1);
			}
			else
			{
				fin.ignore(2);
			}
			getline(fin, buff, '|');
			if (!buff.empty())
			{
				video._price = stod(buff);
			}
			else
			{
				video._price = 0;
			}
		}
		catch (...)
		{
			delete& video;
			throw;
		}
		return fin;
	}

	ofstream& operator<<(ofstream& out, Account& account)
	{
		if (account._type == "admin")
		{
			out << *dynamic_cast<Admin*>(&account);
		}
		else if (account._type == "customer")
		{
			out << *dynamic_cast<Customer*>(&account);
		}
		return out;
	}

	ofstream& operator<< (ofstream& out, Admin& admin)
	{
		out << admin.name << '|' << admin._password << '\n';
		return out;
	}
	ifstream& operator>> (ifstream& fin, Admin& admin)
	{
		try
		{
			getline(fin, admin.name, '|');
			getline(fin, admin._password, '\n');
		}
		catch (...)
		{
			delete& admin;
		}
		return fin;
	}

	ofstream& operator<< (ofstream& out, Customer& customer)
	{
		out << customer.name << '|' << customer._password << '|' << customer._money << '|';
		if (customer._purchased.empty())
		{
			out << ",|\n";
			return out;
		}
		else
		{
			unsigned int i = 0;
			for (i; i < customer._purchased.size() - 1; i++)
			{
				out << *customer._purchased.at(i) << ',';
			}
			out << *customer._purchased.at(i) << "|\n";
		}
		return out;
	}
	ifstream& operator>> (ifstream& fin, Customer& customer)
	{
		try
		{
			getline(fin, customer.name, '|');
			getline(fin, customer._password, '|');
			string buff;
			getline(fin, buff, '|');
			if (!buff.empty())
			{
				customer._money = stod(buff);
			}
			else
			{
				customer._money = 0;
			}
			if (fin.peek() != ',')
			{
				do
				{
					Video* video = new Video();
					fin >> *video;
					customer._purchased.push_back(video);
				} while (fin.peek() != '|' && fin);
			}
			getline(fin, buff, '\n');
		}
		catch (...)
		{
			delete& customer;
			throw;
		}
		return fin;
	}


	ostream& operator<< (ostream& out, VideoStatus& video)
	{
		out << *video.video << '(' << video.quantity << " кол-во купить)";
		return out;
	}
	ofstream& operator<< (ofstream& out, VideoStatus& video)
	{
		out << *video.video << video.quantity << '\n';
		return out;
	}
	ifstream& operator>> (ifstream& fin, VideoStatus& video)
	{
		try
		{
			fin >> *video.video;
			string buff;
			getline(fin, buff, '|');
			if (!buff.empty())
			{
				video.quantity = stoi(buff);
			}
			else
			{
				video.quantity = 0;
			}
			getline(fin, buff, '\n');
		}
		catch (...)
		{
			delete& video;
			throw;
		}
		return fin;
	}
}