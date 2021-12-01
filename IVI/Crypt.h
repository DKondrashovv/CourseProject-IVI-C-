#pragma once

#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;

namespace VideoStore
{
	string enterString(string message);
	int enterInt(string message);
	int enterIndex(string message, int maxValue);
	double enterDouble(string message);
	string stringToLower(string str);

	string enterPassword(string message);

	string cryptor(string toCrypt);

	template<typename Type>
	static void showList(list<Type> toShow);
}
