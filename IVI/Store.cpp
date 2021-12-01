#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <list>
#include <vector>	

#include "Store.h"

using namespace std;

namespace VideoStore
{
	void Store::advanceVideo(list<VideoStatus*>::iterator& iterator, int index)
	{
		for (unsigned int i = 0; i < _videoo.size(); i++)
		{
			if ((*iterator)->isAvailable)
			{
				index--;
				if (index <= 0)
				{
					return;
				}
			}
			iterator++;
		}
	}

	Store::Store()
	{
		_availableVideoo = 0;
		ifstream fin;
		fin.open("Videoo.txt");
		while (fin && !fin.eof())
		{
			if (fin.peek() == -1 || fin.peek() == ' ' || fin.peek() == '\n')
			{
				break;
			}
			VideoStatus* video = new VideoStatus();
			fin >> *video;
			_videoo.push_back(video);
			_availableVideoo++;
		}
	}
	Store::Store(const Store& other)
	{
		_videoo = other._videoo;
		_availableVideoo = other._availableVideoo;
	}

	VideoStatus* Store::video(int index)
	{
		auto it = _videoo.begin();
		advanceVideo(it, index);
		return *it;
	}

	int Store::videoQuantity()
	{
		return _availableVideoo;
	}
	void Store::showVideo()
	{
		int i = 1;
		for (auto video = _videoo.begin(); video != _videoo.end(); video++)
		{
			if ((*video)->isAvailable)
			{
				cout << i++ << ". " << **video << endl;
			}
		}
	}
	void Store::addVideo()
	{
		Video* video = new Video();
		video->setAuthor();
		video->setName();
		video->setGenre();
		video->setPrice();
	    int quantity = enterInt("Введите количество видосов, которое можно будет купить: ");
		_videoo.push_back(new VideoStatus(video, quantity));
		cout << "Видео успешно добавлено" << endl;
		_availableVideoo++;
	}
	void Store::deleteVideo(int index)
	{
		auto video = _videoo.begin();
		advanceVideo(video, index);
		cout << "Видео (" << *(*video)->video << ") успешно удалено";
		(*video)->isAvailable = false;
		_availableVideoo--;
	}

	Video* Store::addToCrate(int index)
	{
		auto video = _videoo.begin();
		advanceVideo(video, index);
		if ((*video)->isAvailable)
		{
			(*video)->quantity--;
			if ((*video)->quantity <= 0)
			{
				(*video)->isAvailable = false;
				_availableVideoo--;
			}
			return (*video)->video;
		}
		return nullptr;
	}
	void Store::returnVideo(Video* videoToReturn)
	{
		VideoStatus* video = findVideo(videoToReturn);
		if (!video->isAvailable)
		{
			video->isAvailable = true;
		}
		if (video->quantity == 0)
		{
			_availableVideoo++;
		}
		video->quantity++;
	}

	bool compareVideoo(VideoStatus* first, VideoStatus* second);
	void Store::sort()
	{
		list<VideoStatus*> sorted = list<VideoStatus*>(_videoo);
		sorted.sort(compareVideoo);
		showList<VideoStatus*>(sorted);
	}

	list<VideoStatus*> Store::find(string request)
	{
		list<VideoStatus*> requested;
		request = stringToLower(request);
		for (auto videoIterator = _videoo.begin(); videoIterator != _videoo.end(); videoIterator++)
		{
			Video video = *(*videoIterator)->video;
			if (stringToLower(video.author()).compare(request) == 0 || stringToLower(video.name()).compare(request) == 0 || video.hasGenre(request))
			{
				requested.push_back(*videoIterator);
			}
		}
		return requested;
	}
	VideoStatus* Store::findVideo(Video* video)
	{
		for (auto videoIterator = _videoo.begin(); videoIterator != _videoo.end(); videoIterator++)
		{
			if ((*videoIterator)->video == video)
			{
				return *videoIterator;
			}
		}
		return nullptr;
	}

	VideoStatus::VideoStatus()
	{
		video = new Video();
		quantity = 1;
		isAvailable = true;
	}
	VideoStatus::VideoStatus(const VideoStatus& other)
	{
		video = other.video;
		quantity = other.quantity;
		isAvailable = other.isAvailable;
	}
	VideoStatus::VideoStatus(Video* video, int quantity)
	{
		this->video = video;
		this->quantity = quantity;
		if (quantity > 0)
		{
			this->isAvailable = true;
		}
		else
		{
			this->isAvailable = false;
		}
	}

	bool compareVideoo(VideoStatus* first, VideoStatus* second)
	{
		if (stringToLower(first->video->author()) < stringToLower(second->video->author()))
		{
			return true;
		}
		return false;
	}

	template<typename Type>
	void showList(list<Type> toShow)
	{
		int i = 1;
		for (auto iterator = toShow.begin(); iterator != toShow.end(); iterator++)
		{
			cout << i++ << ". " << **iterator << endl;
		}
	}
}