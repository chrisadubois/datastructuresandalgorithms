#pragma once
#include "MinHeap.h"

using namespace std;
class PriorityQueue
{
public:
	PriorityQueue();
	bool enqueue(const int);
	bool dequeue();
	void print() const;
	const int FirstPriority() const;
	~PriorityQueue();
private:
	MinHeap data;
	int size;
};

