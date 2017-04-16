#ifndef ORIGINAL_H
#define ORIGINAL_H

#include "heap.h"

class Original : public Heap<HeapNode> {
public:
	Original(int num) {
		totalNum = num;
		tmpNum = num;
		for (int i = 0; i < MAX_SIZE; i++)identifier[i] = i;
	};
	virtual ~Original() {};

	virtual HeapNode get();
	virtual void decrease(int index, int distance);
private:
	int identifier[MAX_SIZE];
};

#endif 