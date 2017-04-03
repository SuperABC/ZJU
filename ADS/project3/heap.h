#pragma once
#ifndef HEAP_H
#define HEAP_H

#define MAX_SIZE 300000

struct HeapNode {
	int index;
	int distance;
};

class Heap {
public:
	Heap();
	~Heap();
	virtual void insert(int index, int distance) = 0;
	virtual int get() = 0;
	virtual void decrease(int index, int distance) = 0;
private:
	HeapNode queue[MAX_SIZE];
};

#endif
