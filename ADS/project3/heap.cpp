#include "heap.h"

Heap::Heap() {
	for (int i = 0; i < MAX_SIZE; i++) {
		queue[i] = new HeapNode(i);
		identifier[i] = i;
	}
}
Heap::~Heap() {
	for (int i = 0; i < MAX_SIZE; i++) {
		delete queue[i];
	}
}

