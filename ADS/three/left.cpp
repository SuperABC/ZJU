#include "left.h"

void setParent(LeftNode *child, LeftNode *parent) {
	(child == nullptr) ? nullptr : parent = child->parent;
}

void setChild(LeftNode *parent, LeftNode *child, bool flag) {
	(parent == nullptr) ?
		nullptr :
		(flag == false ? parent->left = child : parent->right = child);
}

void Left::deleteTree(LeftNode *root) {
	if (root == nullptr) {
		return;
	}
	deleteTree(root->left);
	deleteTree(root->right);
}

void Left::insert(int index, int distance) {
	LeftNode* singleHeap = new LeftNode(index, distance);
	root = merge(root, singleHeap);
	indexToPtr[index] = singleHeap;
	++nodesNum;
}

LeftNode *Left::merge(LeftNode *root1, LeftNode *root2) {
	if (root1 == nullptr) {
		return root2;
	}
	else if (root2 == nullptr) {
		return root1;
	}
	else if(root1->distance > root2->distance){
		LeftNode* temp = root1;
		root1 = root2;
		root2 = temp;
	}
	if (root1->left == nullptr) {
		root1->left = root2;
		root2->parent = root1;
	}
	else {
		root1->right = merge(root1->right, root2);
		root1->right->parent = root1;
		if (getNpl(root1->left) < getNpl(root1->right)) {
			LeftNode* temp = root1->left;
			root1->left = root1->right;
			root1->right = temp;
		}
		root1->npl = getNpl(root1->right) + 1;
	}
	return root1;
}

LeftNode Left::get() {
	if (nodesNum == 0) {
		return LeftNode(-1, 0);
	}
	--nodesNum;
	LeftNode* temp = root;
	int res = root->index;
	setParent(root->left, nullptr);
	setParent(root->right, nullptr);
	root = merge(root->left, root->right);
	delete temp;
	return LeftNode(res);
}

void Left::decrease(int cityIndex, int distance) {
	LeftNode* currentNode = indexToPtr[cityIndex];
	currentNode->distance = distance;
	LeftNode* parent = currentNode->parent;
	while (currentNode != root && currentNode->distance < parent->distance){
		swap(&indexToPtr[currentNode->index], &indexToPtr[parent->index]);
		swap(&(currentNode->index), &(parent->index));
		swap(&(currentNode->distance), &(parent->distance));
		swap(&(currentNode->npl), &(parent->npl));
		currentNode = parent;
		parent = currentNode->parent;
	}
}