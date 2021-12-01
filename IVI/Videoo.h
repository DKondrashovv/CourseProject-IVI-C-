#pragma once

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <map>
#include <vector>	

#include "Crypt.h"

using namespace std;

namespace VideoStore
{
	class Video
	{
		string _author;
		string _name;
		vector<string> _genre;
		double _price;
	public:
		Video();
		Video(const Video& other);

		void setAuthor();
		void setAuthor(string author);
		void setName();
		void setName(string name);
		void setGenre();
		void setGenre(string genre);
		void setPrice();
		void setPrice(double price);

		string author();
		string name();
		vector<string>& genre();
		string genre(int genreNumber);
		double price();

		bool hasGenre(string genreToCompare);

		friend ostream& operator<< (ostream& out, Video& video);
		friend ofstream& operator<< (ofstream& out, Video& video);
		friend ifstream& operator>> (ifstream& fin, Video& video);
		bool operator< (Video* other);
		bool operator> (Video* other);
		bool operator== (Video* other);
	};
}