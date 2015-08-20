#include "PriorityQueue.h"


PriorityQueue::PriorityQueue()
{
	size = 0;
}

bool PriorityQueue::enqueue(const int val)
{
	data.insert(val);
	size++;
	return true;
}

bool PriorityQueue::dequeue()
{
	data.remove();
	size--;
	return true;
}

const int PriorityQueue::FirstPriority() const
{
	return data.top();
}


PriorityQueue::~PriorityQueue()
{
}
