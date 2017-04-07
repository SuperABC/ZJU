#ifndef ORIGINAL_H
#define ORIGINAL_H

#include "heap.h"

class Original : public Heap<HeapNode> {
public:
	Original(int num) { totalNum = num; tmpNum = num; };
	virtual ~Original() {};

	virtual HeapNode get();
	virtual void decrease(int index, int distance);
};

#endif 