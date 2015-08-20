#include "stdafx.h"
#include "Robot.h"
#include "Point.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << "Your robot is lost!" << endl;
	cout << "Give some starting and ending coordinates" << endl;
	cout << "Each number should be seperated by spaces, e.g., 1 2 3 4" << endl;
	cout << "which will represent start at (1, 2) and end at (3, 4)" << endl;
	cout << "and the robot will calculate the quickest paths" << endl;
	cout << "(North South East West - NSEW) combination to get there" << endl;
	cout << "The robot assumes proper input, pass in ONLY int int int int" << endl;
	Point start;
	Point end;
	cin >> start >> end;
	Robot PathFinder(start, end);
	PathFinder.Display();
	return 0;
}