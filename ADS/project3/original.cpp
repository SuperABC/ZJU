#include "original.h"

void Original::decrease(int index, int distance) {
	int queueIndex = identifier[index];
	HeapNode *tmpNode = nullptr;
	int tmpIndex = 0;
	queue[queueIndex]->distance = distance;

	while (queueIndex > 0 && queue[(queueIndex - 1) / 2]->distance > queue[queueIndex]->distance) {
		swap<int>(&identifier[index], &identifier[queue[(queueIndex - 1) / 2]->index]);
		swap<HeapNode>(queue[queueIndex], queue[(queueIndex - 1) / 2]);
		queueIndex = (queueIndex - 1) / 2;
	}
}
int Original::get() {
	int ret = queue[0]->index;
	HeapNode *tmpNode;
	int tmpIndex = 0;
	int index = 0;

	if (tmpNum == 0)return -1;
	tmpNum--;
	swap<int>(&identifier[queue[tmpNum]->index], &identifier[queue[0]->index]);
	swap<HeapNode>(queue[0], queue[tmpNum]);
	tmpNode = queue[0];
	tmpIndex = queue[0]->index;
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
	identifier[tmpIndex] = index;
	queue[index] = tmpNode;
	return ret;
}
