#pragma once
#include <climits>
#include <vector>
#include <iostream>

using namespace std;
class MinHeap
{
public:
	MinHeap();
	~MinHeap();

	int getMin() const;
	int getLeftChild(const int) const;
	int getRightChild(const int) const;
	int getParent(const int) const;
	bool isEmpty() const;

	bool insert(const int value);
	bool insert2(const int value);
	bool remove2();
	bool remove();
	void heapify(const vector<int>&);
	const int top() const;


	void print() const;

private:
	vector<int> data;
	int heapSize;

	void bubbleUp(const int);
	void bubbleDown(const int);
};

