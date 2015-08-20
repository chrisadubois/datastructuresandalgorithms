/*
*@Author: Christopher DuBois
*Homework #2 Lost In The Supermarket
*Professor Robert Dimpsey
*CSS342
*/

#include "stdafx.h"
#include "Robot.h"
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h> 

using namespace std;

Robot::Robot()
{
	start.setX(0);
	start.setY(0);
	end.setX(0);
	end.setY(0);
	pathCounter = 0;
	path = "No Movement Necessary";
	routes.push_back(path);
}

Robot::Robot(Point begin, Point destination)
{
	start = begin;
	end = destination;
	pathCounter = 0;
	if (start == end)
	{
		pathCounter = -1;
		routes.push_back("No Movement Necessary");
	}
}

Robot::~Robot()
{
}

bool Robot::PlayAgain()
{
	cout << "Would you like to play again? Type Y for yes and N for No" << endl;
	char YorN;
	cin >> YorN;
		if ((YorN == 'Y') || (YorN == 'y'))
		{
			return true;
		}
		else if ((YorN == 'N') || (YorN == 'n'))
		{
			return false;
		}
		else
		{
			cout << "Invalid entry...try again" << endl;
			PlayAgain();
		}
}

void Robot::Display()
{
	cout << endl;
	cout << "Robot's start: (" << start.getX() << "," << start.getY() << ") AND " << "Robot's end: (" << end.getX() << "," << end.getY() << ")" << endl;
	FindShortestPaths(start.getX(), start.getY(), end.getX(), end.getY(), pathCounter, path);
	cout << endl;
	cout << pathCounter << " << Unique Combinations" << endl;
	for (int i = 0; i < routes.size(); i++)
	{
		cout << routes.at(i) << endl;
	}
	cout << endl;
	bool lostAgain = PlayAgain();
	if (lostAgain)
	{
		cout << "Please enter your robot's starting x y coordinates again" << endl;
		cout << "as well as your robot's ending destination x y coordinates" << endl;
		int x, y, dx, dy;
		cin >> x >> y >> dx >> dy;
		Point begin(x, y);
		Point destination(dx, dy);
		Robot PathFinder(begin, destination);
		PathFinder.Display();
	}
	else 
	{
		cout << "Goodbye, thanks for helping your robot recalculate his directions!" << endl;
		Sleep(2500);//used to keep the console up for a moment to read the message displayed above
	}
}

void Robot::FindShortestPaths(int currentX, int currentY, int endX, int endY, int &counter, string &avenue)
{
	if ((currentX == endX) && (currentY == endY))
	{
		counter++;
		routes.push_back(path);
	}
	else 
	{
		if (currentX < endX)
		{
			path.push_back('E');
			FindShortestPaths(currentX+1, currentY, endX, endY, counter, path);
			path.pop_back();
		}
		if (currentY < endY)
		{
			path.push_back('N');
			FindShortestPaths(currentX, currentY+1, endX, endY, counter, path);
			path.pop_back();
		}
		if (currentY > endY)
		{
			path.push_back('S');
			FindShortestPaths(currentX, currentY-1, endX, endY, counter, path);
			path.pop_back();
		}
		if (currentX > endX)
		{
			path.push_back('W');
			FindShortestPaths(currentX-1, currentY, endX, endY, counter, path);
			path.pop_back();
		}
	}
}
