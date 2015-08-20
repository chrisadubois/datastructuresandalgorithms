#include "stdafx.h"
#include "Point.h"
#include <iostream>
using namespace std;

Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(int xCo, int yCo)
{
	x = xCo;
	y = yCo;
}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

bool Point::setX(int xCo)
{
	x = xCo;
	return true;
}

bool Point::setY(int yCo)
{
	y = yCo;
	return true;
}

istream& operator>>(istream& instream, Point& passedPoint)
{
	int xGet, yGet;
	instream >> xGet >> yGet;
	passedPoint.setX(xGet);
	passedPoint.setY(yGet);
	return instream;
}

bool Point::operator==(Point &passedPoint) const
{
	return (getX() == passedPoint.getX() && getY() == passedPoint.getY());
}

bool Point::operator!=(Point &passedPoint) const
{
	return *this == passedPoint;
}

Point::~Point()
{
}
