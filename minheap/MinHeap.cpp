#include "MinHeap.h"

MinHeap::MinHeap()
{
	heapSize = 0;
}

MinHeap::~MinHeap()
{
}

bool MinHeap::isEmpty() const
{
	return heapSize == 0;
}

int MinHeap::getMin() const
{
	if (isEmpty())
	{
		return INT_MAX;
	}
	else
	{
		return data[0];
	}
}

int MinHeap::getLeftChild(int idx) const
{
	return (2 * idx) + 1;
}

int MinHeap::getRightChild(int idx) const
{
	return (2 * idx) + 2;
}

int MinHeap::getParent(int idx) const
{
	return (idx - 1) / 2;
}

//add an element to the end of the vector
//then bubble up the new item pushed back as long as the
//"heap property" is "broken" heap property here is defined as all nodes are
//less than their parent, bubbling up can be completed by ensuring that the
//index is a valid idnex in the array, comparing the node value with parent
//value, if not accurate, swap them up.
bool MinHeap::insert(const int value)
{
	data.push_back(value);
	heapSize++;
	bubbleUp(heapSize - 1);
	return true;
}

bool MinHeap::insert2(const int value)
{
	data.push_back(value);
	heapSize++;
	int idx = heapSize - 1;
	int pIdx = getParent(idx);
	while (data[pIdx] > data[idx] && idx >= 0)
	{
		int temp = data[idx];
		data[idx] = data[pIdx];
		data[pIdx] = temp;

		idx = (idx - 1) / 2;
		pIdx = getParent(idx);
	}
	return true;
}

void MinHeap::bubbleUp(const int idx)
{
	int parentIdx = 0;
	int pretend = INT_MAX;
	if (idx >= 0)
	{
		parentIdx = getParent(idx);
		if (data[parentIdx] > data[idx])
		{
			pretend = data[parentIdx];
			data[parentIdx] = data[idx];
			data[idx] = pretend;

			bubbleUp(parentIdx);
		}
	}
}

//add the value at the end of the Binary Heap to the root of the Binary Heap
//replacing the minimum there with a larger value, decrement the heap size
//push the pretend root's value down into the Binary Heap until the heap
//property has been restored by doing such:
//if the current idx has no children, then we are done
//if the current idx has one child, check for heap property, if the heap 
//property is broken, swap current idx value with child value, then bubble
//down the child
//if the current idx has two children, locate the smallest of the two, if the
//heap property is broken, then swap the current idx with the smallest of the
//two then bubble the child down
bool MinHeap::remove()
{
	data[0] = data[heapSize - 1];
	heapSize--;
	if (heapSize > 0)
	{
		bubbleDown(0);
	}
	return true;
}

bool MinHeap::remove2()
{
	if (heapSize != 0)
	{
		int min = data[0];
		int last = data[heapSize - 1];
		heapSize--;
		int current = 0;
		data[current] = last;
		//it won't go into the single child case
		while 
			((getLeftChild(current) < heapSize && 
			data[current] > data[getLeftChild(current)]) ||
			(getRightChild(current) < heapSize && 
			data[current] > data[getRightChild(current)]))
		{
			//right child case
			if (getLeftChild(current) >= heapSize &&
				getRightChild(current) < heapSize)
			{
				int temp = data[current];
				data[current] = data[getRightChild(current)];
				data[getRightChild(current)] = temp;
				//increment current to its right child
				current = (current * 2 + 2);
				continue;
			}
			//left child case
			if (getLeftChild(current) < heapSize &&
				getRightChild(current) >= heapSize)
			{
				int temp = data[current];
				data[current] = data[getLeftChild(current)];
				data[getLeftChild(current)] = temp;
				//increment current  to it's left child
				current = (current * 2 + 1);
				continue;
			}
			//
			//two children case
			if (data[getLeftChild(current)] < data[getRightChild(current)])
			{
				int temp = data[current];
				data[current] = data[getLeftChild(current)];
				data[getLeftChild(current)] = temp;
				//increment current  to it's left child
				current = (current * 2 + 1);
				continue;
			}
			else
			{
				int temp = data[current];
				data[current] = data[getRightChild(current)];
				data[getRightChild(current)] = temp;
				//increment current to its right child
				current = (current * 2 + 2);
				continue;
			}
		}
		return min;
	}
	return -1;
}

void MinHeap::bubbleDown(const int idx)
{
	int pretend = INT_MAX;
	int LChild = getLeftChild(idx);
	int RChild = getRightChild(idx);
	int minIdx;
	//Node has no children, complete
	if (LChild >= heapSize && RChild >= heapSize)
	{
		return;
	}
	//one right child
	else if (LChild >= heapSize && RChild < heapSize)
	{
		minIdx = RChild;
	}
	//one left child
	else if (LChild < heapSize && RChild >= heapSize)
	{
		minIdx = LChild;
	}
	//otherwise two children
	else
	{
		if (data[LChild] <= data[RChild])
		{
			minIdx = LChild;
		}
		else //(data[LChild] > data[RChild])
		{
			minIdx = RChild;
		}
	}
	//check to see if the heap property is broken
	if (data[idx] > data[minIdx])
	{
		//swap----------swap//
		pretend = data[minIdx];
		data[minIdx] = data[idx];
		data[idx] = pretend;
		//swap----------swap//

		//recursive call to complete
		bubbleDown(minIdx);
	}
}

void MinHeap::print() const
{
	for (int i = 0; i < heapSize; i++)
	{
		cout << data[i] << ", ";
	}
	cout << endl;
}

void MinHeap::heapify(const vector<int>& toIfy)
{
	heapSize = toIfy.size();
	data = toIfy;
	for (int i = toIfy.size() / 2; i >= 0; i--)
	{
		bubbleDown(i);
	}
}

const int MinHeap::top() const
{
	return data[0];
}