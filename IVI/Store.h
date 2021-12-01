#pragma once

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <list>
#include <vector>	

#include "Videoo.h"

using namespace std;

namespace VideoStore
{
	template<typename Type>
	void showList(list<Type> toShow);

	struct VideoStatus
	{
		Video* video;
		int quantity;
		bool isAvailable;
		VideoStatus();
		VideoStatus(const VideoStatus& other);
		VideoStatus(Video* video, int quantity);
		friend ostream& operator<< (ostream& out, VideoStatus& video);
		friend ofstream& operator<< (ofstream& out, VideoStatus& video);
		friend ifstream& operator>> (ifstream& in, VideoStatus& video);
	};

	class Store
	{
		list<VideoStatus*> _videoo;
		int _availableVideoo;
		void advanceVideo(list<VideoStatus*>::iterator& iterator, int index);
	public:
		Store();
		Store(const Store& other);
		VideoStatus* video(int index);
		void showVideo();
		void addVideo();
		void deleteVideo(int index);

		int videoQuantity();

		Video* addToCrate(int index);
		void returnVideo(Video* video);


		list<VideoStatus*> find(string request);
		void sort();

		VideoStatus* findVideo(Video* video);

		friend void save(Store& store);
	};
}