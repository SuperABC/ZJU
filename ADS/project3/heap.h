#ifndef HEAP_H
#define HEAP_H

#define MAX_SIZE 300000
#define INFINITY 1000000000

struct HeapNode {
	int index;
	int distance;
	HeapNode(int i) : index(i), distance(INFINITY) {};
};

class Heap {
public:
	Heap();
	~Heap();
	virtual int get() = 0;
	virtual void decrease(int index, int distance) = 0;
protected:
	HeapNode *queue[MAX_SIZE];
	int identifier[MAX_SIZE];
	int nodeNum, tmpNum;
};

#endif
