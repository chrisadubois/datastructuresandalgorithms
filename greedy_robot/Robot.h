#pragma once

#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <vector>
#include "Point.h"

using namespace std;

class Robot
{
public:
	Robot();
	Robot(Point start, Point end);
	~Robot();
	/*
	*This method starts the program and makes the console interactive
	it will call the FindPaths method inside, this method just keeps the 
	display working
	*/
	void Display();
private:
	vector<string> routes;
	string path;
	Point start;
	Point end;
	int pathCounter;
	/*
	* This method allows for the user to decide whether or not they want to play the game again
	*by typing y or n into the console, invalid entries cause a recursive call to ask for valid input
	*/
	bool PlayAgain();
	/*
	*This method finds the shortest paths from the starting point to the destination
	*by using recursion, all the directional moves, and the helper method, undoMovements
	*which operates by backtracking through the path.  Following the stack frames...
	*the method will recursively find one path destination from the starting destination,
	*print out that path, and backtrack step by step using undoMovements, trying a different direction
	*to get to the destination, and this works because in the stack frames, the function already knows
	*it has gone through a particular path previously, which is why the method does not print out the same path
	*over and over again
	*/
	void FindShortestPaths(int currentX, int currentY, int endingX, int endingY, int &counter, string &arr);
};
#endif
