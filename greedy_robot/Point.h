/*
@Author: Christopher DuBois
CSS 342
Professor Dimpsey

GIMPY point class uses for factoring for the Lost Robot Recursive problem
*/



#pragma once
using namespace std;
#include <iostream>
class Point
{
	friend istream& operator>>(istream &inStream, Point& passedPoint);
public:
	Point();
	Point(int xCo, int yCo);
	int getX() const;
	int getY() const;
	bool setX(int xCo);
	bool setY(int yCo);
	bool operator==(Point &passedPoint) const;
	bool operator!=(Point &passedPoint) const;
	~Point();
private:
	int x;
	int y;
};

