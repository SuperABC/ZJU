#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#define MAX_ROOT 100

#include "heap.h"

struct FibNode : public HeapNode {
	int degree;
	bool mark;
	FibNode *left, *right, *parent, *child;
	FibNode(int i = 0) : HeapNode(i, -1), degree(0), mark(false), left(this), right(this), parent(NULL), child(NULL) {};
};

class Fibonacci : public Heap<FibNode> {
public:
	Fibonacci(int num = 0) {
		totalNum = 0;
		tmpNum = 0;
	};
	virtual ~Fibonacci() {};

	virtual FibNode get();
	virtual void decrease(int index, int dist);

//private:
	void insert(int index, int dist);
	void merge(FibNode *r);
	void remove(FibNode *r);
	void link(FibNode *r1, FibNode *r2);
	void consolidate();
	void cascade(FibNode *p);

	FibNode *root = NULL;
	FibNode *cons[MAX_ROOT];
};

#endif