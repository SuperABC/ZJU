#include "heap.h"

#ifndef ORIGINAL_H
#define ORIGINAL_H

class Original : public Heap {
public:
	Original(int num) { nodeNum = num; tmpNum = num; };
	~Original() {};
	virtual int get();
	virtual void decrease(int index, int distance);
};


#endif 