#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"original.h"

#define maxVetexNum 300000
#define infinite 1e13

using namespace std;

struct AdjListNode {
public:
	AdjListNode(int index) :vertexIndex(index), nextAdjNodePtr(nullptr) {}
	int vertexIndex;
	double passCost;
	AdjListNode* nextAdjNodePtr;
};
struct GraphNode {
public:
	GraphNode() : isKnown(false), adjList(nullptr) ,lastIndex(-1) {}
	~GraphNode() {
		clearNode(adjList);
	}
	void insertAdjNode(int vertexIndex, double cost) {
		if (adjList == nullptr) {
			adjList = new AdjListNode(vertexIndex);
			adjList->passCost = cost;
			return;
		}
		AdjListNode* endPtr(adjList);
		while (endPtr->nextAdjNodePtr != nullptr) {
			endPtr = endPtr->nextAdjNodePtr;
		}
		endPtr->nextAdjNodePtr = new AdjListNode(vertexIndex);
		endPtr->nextAdjNodePtr->passCost = cost;
	}
	AdjListNode* adjList;
	int lastIndex;
	bool isKnown;
	double cost;
private:
	void clearNode(AdjListNode* ptrToNode) {
		if (ptrToNode == nullptr)
			return;
		else if (ptrToNode != nullptr)
			clearNode(ptrToNode->nextAdjNodePtr);
		else
			delete ptrToNode;
	}
};

class Graph {
public:
	Graph();
	void initialGraph() {}
	void dijkstra(int targetIndex);
	vector<GraphNode> nodes;
	int nodesNum;
private:
	void printPass(int currentIndex, int targetIndex);
};

Graph::Graph() : nodes(maxVetexNum) {
	ifstream inputFile("roads.txt");
	int passNum, index1, index2;
	double cost;
	inputFile >> nodesNum >> passNum;
	for (int i(0); i != passNum; ++i) {
		inputFile >> index1 >> index2 >> cost;
		nodes[index1 - 1].insertAdjNode(index2 - 1, cost);
	}
	return;
}
void Graph::dijkstra(int targetIndex) {
	Heap<HeapNode> *heap = new Original(nodesNum);
	for (int i(0); i != nodesNum; ++i) {
		nodes[i].cost = infinite;
		nodes[i].lastIndex = -1;
		nodes[i].isKnown = 0;
	}
	nodes[targetIndex].cost = 0;
	nodes[targetIndex].lastIndex = -1;

	heap->decrease(targetIndex, 0);
	int currentIndex, nextIndex;
	while (true) {
		currentIndex = heap->get().index;
		if (currentIndex < 0)break;
		nodes[currentIndex].isKnown = true;
		AdjListNode* nextNodePtr = nodes[currentIndex].adjList;
		while (nextNodePtr != nullptr) {
			nextIndex = nextNodePtr->vertexIndex;
			if (nodes[nextIndex].isKnown) {
				nextNodePtr = nextNodePtr->nextAdjNodePtr;
				continue;
			}
			if (nodes[currentIndex].cost + nextNodePtr->passCost >= nodes[nextIndex].cost) {
				nextNodePtr = nextNodePtr->nextAdjNodePtr;
				continue;
			}
			heap->decrease(nextIndex, nodes[currentIndex].cost + nextNodePtr->passCost);
			nodes[nextIndex].cost = nodes[currentIndex].cost + nextNodePtr->passCost;
			nodes[nextIndex].lastIndex = currentIndex;
			nextNodePtr = nextNodePtr->nextAdjNodePtr;
		}
	}

	for (int i(0); i != nodesNum; ++i) {
		cout << "The " << i << " th " << "vertex :" << endl << targetIndex;
		int index(i);
		printPass(i, targetIndex);
		cout << endl;
	}
	delete heap;
}
void Graph::printPass(int currentIndex, int targetIndex) {
	if (nodes[currentIndex].lastIndex == -1)return;
	if (currentIndex == targetIndex) {
		cout << currentIndex;
		return;
	}
	printPass(nodes[currentIndex].lastIndex, targetIndex);
	cout << " -> " << currentIndex;
	return;
}

int main() {
	Graph roads;
	roads.initialGraph();
	while (true) {
		int targetIndex;
		if (!(cin >> targetIndex)) {
			break;
		}
		roads.dijkstra(targetIndex);
	}

	return EXIT_SUCCESS;
}