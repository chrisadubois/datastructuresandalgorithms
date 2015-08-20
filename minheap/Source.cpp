#include "MinHeap.h"

int main()
{
	MinHeap a;
	a.insert(40);
	a.insert(50);
	a.insert(60);
	a.insert(100);
	a.insert(180);
	a.insert(120);
	a.insert(65);
	a.insert(55);
	a.insert(150);
	a.insert(30);
	a.print();
	a.remove();
	a.remove();
	a.print();
	vector<int> b;
	b.push_back(40);
	b.push_back(50);
	b.push_back(60);
	b.push_back(100);
	b.push_back(180);
	b.push_back(120);
	b.push_back(65);
	b.push_back(55);
	b.push_back(150);
	b.push_back(30);
	MinHeap c;
	c.heapify(b);
	c.print();


	MinHeap d;
	d.insert2(40);
	d.insert2(50);
	d.insert2(60);
	d.insert2(100);
	d.insert2(180);
	d.insert2(120);
	d.insert2(65);
	d.insert2(55);
	d.insert2(150);
	d.insert2(30);
	d.print();
	d.remove2();
	d.remove2();
	d.print();

	MinHeap e;
	e.insert2(40);
	e.insert2(50);
	e.insert2(60);
	e.print();
	e.remove2();
	e.print();
	e.remove2();
	e.print();
	e.remove2();
	e.print();



	vector<int> k;
	k.push_back(40);
	k.push_back(50);
	k.push_back(60);
	k.push_back(100);
	k.push_back(180);
	k.push_back(120);
	k.push_back(65);
	k.push_back(55);
	k.push_back(150);
	k.push_back(30);
	MinHeap f;
	f.heapify(k);
	f.print();

	return 0;
}