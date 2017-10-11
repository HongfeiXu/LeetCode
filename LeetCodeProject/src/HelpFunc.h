#pragma once
#include <vector>
#include <iostream>
using namespace std;

template<typename T>
void PrintVector(const vector<T> &vec, char seperator = ' ')
{
	for (unsigned i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << seperator;
	}
}