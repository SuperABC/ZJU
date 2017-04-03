#include "original.h"

void Original::decrease(int index, int distance) {
	int queueIndex = identifier[index];
	HeapNode *tmpNode = nullptr;
	int tmpIndex = 0;
	while (queueIndex > 0 && queue[(queueIndex - 1) / 2]->distance > queue[queueIndex]->distance) {
		tmpIndex = identifier[index];
		identifier[index] = identifier[queue[(queueIndex - 1) / 2]->index];
		identifier[queue[(queueIndex - 1) / 2]->index] = tmpIndex;
		tmpNode = queue[queueIndex];
		queue[queueIndex] = queue[(queueIndex - 1) / 2];
		queue[(queueIndex - 1) / 2] = tmpNode;
	}
}
int Original::get() {
	int ret = queue[0]->index;
	HeapNode *tmpNode = queue[0];
	int tmpIndex = 0;
	int index = 0;

	tmpNum--;
	identifier[queue[tmpNum]->index] = 0;
	queue[0] = queue[tmpNum];
	while (1) {
		if (queue[index * 2 + 1]->distance >= queue[index * 2 + 2]->distance && tmpNode->distance > queue[index * 2 + 2]->distance) {
			identifier[queue[index * 2 + 2]->index] = index;
			queue[index] = queue[index * 2 + 2];
			index = index * 2 + 2;
		}
		else if(queue[index * 2 + 1]->distance <= queue[index * 2 + 2]->distance && tmpNode->distance > queue[index * 2 + 1]->distance){
			identifier[queue[index * 2 + 1]->index] = index;
			queue[index] = queue[index * 2 + 1];
			index = index * 2 + 1;
		}
		else break;
	}
	identifier[0] = index;
	queue[0] = tmpNode;
}