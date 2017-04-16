
#ifndef HEAP_H
#define HEAP_H

#include <vector>

#define MAX_SIZE 1000000
#define INFINITE 1000000000

template<class T>
void swap(T *a, T *b) {
	T tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* Since the heap is essentially priority queue, it shound not allow random
access to the elements. The implementation of a heap is varied, and these are
the private matters.
The very basic methods that a heap should provide are as follows (Wikipedia):
- Basic
	- find-min									get_top
	- insert 		(Special case of meld)		push
	- extract-min	(Aka pop)					pop
	- delete-min								pop
	- replace									replace_top
	- Creation
	- create-heap								Constructor
- heapify									heapify
	- merge	(Return a new heap)					merge/operator+
	- meld	(Join but destruct original)		meld/operator+=
- Inspection
	- size										size
	- is-empty									is_empty
- Internal (varied by implementation, keep them private)
	- increase/decrease-key
	- delete
	- percolate-up
	- percolate-down*/

struct HeapNode {
	int index;
	int distance;
	HeapNode(int i = 0, int dist = INFINITE) : index(i), distance(dist) {};
	~HeapNode() {};
	HeapNode operator=(HeapNode h) {
		index = h.index;
		distance = h.distance;
		return *this;
	}
};

template<class Type>
class Heap {
public:
	Heap() {
		totalNum = 0;
		tmpNum = 0;
		for (int i = 0; i < MAX_SIZE; i++) {
			queue[i] = new Type(i);
		}
	}
	Heap(Heap<Type> &src) {
		totalNum = src.totalNum;
		tmpNum = 0;
		memcpy(queue, src.queue, MAX_SIZE);
		memcpy(identifier, src.identifier, MAX_SIZE);
	}
	virtual ~Heap() {
		for (int i = MAX_SIZE - 1; i >= 0; i--) {
			delete queue[i];
		}
	};

	virtual Type get() = 0;
	virtual void decrease(int index, int distance) = 0;

	unsigned size() const { return totalNum; }

protected:
	int leftSon(int index) {
		identifier[index] * 2 + 1;
	}
	int rightSon(int index) {
		identifier[index] * 2 + 2;
	}
	int father(int index) {
		return (identifier[index] - 1) / 2;
	}

	unsigned int totalNum, tmpNum;
	Type *queue[MAX_SIZE];
};

/*
struct HeapNode {
	int index;
	int distance;
	HeapNode(int i = 0) : index(i), distance(INFINITE) {};
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
*/
#endif
