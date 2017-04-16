#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "original.h"
#include "fibnacci.h"
#include "left.h"

#define maxVetexNum 300000
#define infinite 1e13

using namespace std;

double initTime = 0, dijTime = 0, decNum = 0, decTime = 0, decOnce = 0;

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
	string a;
	int passNum, index1, index2;
	double cost;
	clock_t start, end;
	start = clock();
	inputFile >> nodesNum >> passNum;
	for (int i(0); i != passNum; ++i) {
		inputFile >> a >> index1 >> index2 >> cost;
		nodes[index1 - 1].insertAdjNode(index2 - 1, cost);
	}
	end = clock();
	cout << "Input takes ";
	cout << (end - start) / (CLOCKS_PER_SEC*1.0) << " (s)" << endl;
	cout << "Initialize done!" << endl;
	return;
}
void Graph::dijkstra(int targetIndex) {
	time_t begin = clock(), end;
	int newCost;

	//Heap<HeapNode> *heap = new Original(nodesNum);
	Heap<FibNode> *heap = new Fibonacci(nodesNum);
	//Heap<LeftNode> *heap = new Left(nodesNum);

	int decreaseNum(1);
	time_t decreaseTime(0), decreaseBegin;
	for (int i(0); i != nodesNum; ++i) {
		nodes[i].cost = infinite;
		nodes[i].lastIndex = -1;
		nodes[i].isKnown = 0;
	}
	nodes[targetIndex].cost = 0;
	nodes[targetIndex].lastIndex = -1;

	end = clock();
	cout << (end - begin) / (CLOCKS_PER_SEC*1.0) << " ";
	initTime += (end - begin) / (CLOCKS_PER_SEC*1.0);
	begin = clock();
	heap->decrease(targetIndex, 0);
	decreaseTime += clock() - begin;

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
			newCost = nodes[currentIndex].cost + nextNodePtr->passCost;
			if (newCost >= nodes[nextIndex].cost) {
				nextNodePtr = nextNodePtr->nextAdjNodePtr;
				continue;
			}
			decreaseBegin = clock();
			heap->decrease(nextIndex, newCost);
			decreaseTime += clock() - decreaseBegin;
			++decreaseNum;
			nodes[nextIndex].cost = newCost;
			nodes[nextIndex].lastIndex = currentIndex;
			nextNodePtr = nextNodePtr->nextAdjNodePtr;
		}
	}
	/*for (int i(0); i != nodesNum; ++i) {
		cout << "The " << i << " th " << "vertex :" << endl << targetIndex;
		int index(i);
		printPass(i, targetIndex);
		cout << endl;
	}*/

	end = clock();
	cout << (end - begin) / (CLOCKS_PER_SEC*1.0) << " ";
	dijTime += (end - begin) / (CLOCKS_PER_SEC*1.0);
	cout << decreaseNum << " " << decreaseTime / (CLOCKS_PER_SEC*1.0) << " ";
	decNum += decreaseNum;
	decTime += decreaseTime;
	cout << decreaseTime*1.0 * 1000 / decreaseNum << endl;
	decOnce += decreaseTime*1.0 * 1000 / decreaseNum;
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
	int num = roads.nodesNum;
	ofstream outputFile("output.txt");
	streambuf* oldBuf = cout.rdbuf(outputFile.rdbuf());
	for (int i(0); i != 1000; ++i) {
		int targetIndex = rand() % num;
		roads.dijkstra(targetIndex);
		if (i % 50 == 0)printf("Finished %d%%бн\n", i / 10);
	}
	cout.rdbuf(oldBuf);
	cout << "Done!" << endl;

	cout << initTime / 1000 << " " << dijTime / 1000 << " " << decNum / 1000 << " " << decTime / 1000 << " " << decOnce / 1000 << endl;

	return EXIT_SUCCESS;
}