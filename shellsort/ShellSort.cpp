// ShellSort.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;
void ShellSort(vector<int>& arr)
{
	for (int gap = arr.size() / 2; gap > 0; gap = (gap == 2) ? 1 : int(gap / 2.2))
	{
		for (int i = gap; i < arr.size(); i++)
		{
			int tmp = arr[i];
			int j = i;
			//for (;(j >= gap) && (tmp < arr[j - gap]); j -= gap)
			while ((j >= gap) && (tmp < arr[j - gap]))
			{
				arr[j] = arr[j - gap];
				j -= gap;
			}
			arr[j] = tmp;
		}
	}
}

void RadixSort(vector<string>& arr)
{

}


int main()
{
	int c;
	vector<int> a = { 78, 9, 12, 3, 1, 97, 6, 21, 27, 89, 93, 100, 112, 7 };
	vector<string> b = { "Cat", "Tar", "Bat", "Act" };
	cout << a.size() << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << a.at(i) << ", ";
	}
	cout << endl;
	ShellSort(a);
	for (int i = 0; i < a.size(); i++)
	{
		cout << a.at(i) << ", ";
	}
	cout << endl;
	cin >> c;
	return 0;
}

