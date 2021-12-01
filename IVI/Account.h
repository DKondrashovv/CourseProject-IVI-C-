#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "Store.h" 
#include "Videoo.h" 
#include "Crypt.h" 

using namespace std;

namespace VideoStore
{
	class Account
	{
	protected:
		string _type;
		string _password;
		static Store* _store;
	public:
		string name;
		Account* signUp();
		static Account* login(string name, string password);
		virtual void info() = 0;
		virtual void menu() = 0;
		void showCatalog();
		void find();

		static void setStore(Store* store);

		friend ofstream& operator<< (ofstream& out, Account& account);
		friend void save(Store& store);
	};

	class Admin : public Account
	{
	public:
		Admin();
		Account* signUp();

		void menu();
		void addVideo();
		void deleteVideo();
		void editVideo(VideoStatus* video);
		void info();

		friend ifstream& operator>> (ifstream& fin, Admin& admin);
		friend ofstream& operator<< (ofstream& out, Admin& admin);
		friend void save(Store& store);
	};

	class Customer : public Account
	{
		double _money;
		double totalPrice;
		vector<Video*> _purchased;
		vector<Video*> _crate;
	public:
		Customer();
		Account* signUp();

		void menu();
		void addToCrate(Video* video);
		void deleteFromCrate(int index);
		void showCrate();
		void buy();
		void info();

		friend ifstream& operator>> (ifstream& fin, Customer& customer);
		friend ofstream& operator<< (ofstream& out, Customer& customer);
		friend void load(Store& store);
		friend void save(Store& store);
	};

	class Guest : public Account
	{
	public:
		void menu();
		void info();
	};

	extern map<string, Account*> _users;
}

