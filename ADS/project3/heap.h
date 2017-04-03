#ifndef HEAP_H
#define HEAP_H

#define MAX_SIZE 300000
#define INFINITY 1000000000

template<class T>
void swap(T *a, T *b) {
	T tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

struct HeapNode {
	int index;
	int distance;
	HeapNode(int i = 0) : index(i), distance(INFINITY) {};
	~HeapNode() {};
	HeapNode operator=(HeapNode h) {
		index = h.index;
		distance = h.distance;
		return *this;
	}
};

class Heap {
public:
	Heap();
	virtual ~Heap();
	virtual int get() = 0;
	virtual void decrease(int index, int distance) = 0;
protected:
	HeapNode *queue[MAX_SIZE];
	HeapNode *dynQueue[MAX_SIZE];
	int identifier[MAX_SIZE];
	int nodeNum, tmpNum;
};

#endif
