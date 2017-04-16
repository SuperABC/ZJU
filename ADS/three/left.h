#ifndef LEFTHEAP_H_
#define LEFTHEAP_H_
#include<limits>
#include "heap.h"

struct LeftNode : public HeapNode {
	LeftNode(int index, int cost = -1) : HeapNode(index, cost), left(nullptr), right(nullptr),parent(nullptr), npl(0) {}
	LeftNode *left, *right, *parent;
	int npl;
};

class Left : public Heap<LeftNode> {
public:
	Left(int nodesNum):root(nullptr), nodesNum(0){
		indexToPtr = new LeftNode*[nodesNum];
		for (int i(0); i != nodesNum; ++i) {
			insert(i, INT_MAX);
		}
	}
	Left::~Left() {
		deleteTree(root);
		delete[] indexToPtr;
	}
	LeftNode get();
	void decrease(int cityIndex, int distance);
private:
	LeftNode* merge(LeftNode* root1, LeftNode* root2);
	void insert(int index, int distance);
	void deleteTree(LeftNode* root);
	inline int getNpl(LeftNode* root) {
		return root == nullptr ? -1 : root->npl;
	}

	LeftNode* root;
	int nodesNum;
	LeftNode** indexToPtr;
};
#endif
