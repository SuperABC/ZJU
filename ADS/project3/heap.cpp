#include "heap.h"

Heap::Heap() {
	for (int i = 0; i < MAX_SIZE; i++) {
		dynQueue[i] = queue[i] = new HeapNode(i);
		identifier[i] = i;
	}
}
Heap::~Heap() {
	for (int i = MAX_SIZE- 1; i >= 0; i--) {
		delete queue[i];
	}
}

