#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *BinTree;
struct TNode {
	int Key;
	BinTree Left;
	BinTree Right;
};

BinTree BuildTree();
int CheckBST(BinTree T, int K);
int main()
{
	BinTree T;
	int K, out;

	T = BuildTree();
	K = 4;
	out = CheckBST(T, K);
	if (out < 0)
		printf("No.  Height = %d\n", -out);
	else
		printf("Yes.  Key = %d\n", out);

	return 0;
}


BinTree BuildTree() {
	BinTree n1 = (BinTree)malloc(sizeof(BinTree));
	BinTree n2 = (BinTree)malloc(sizeof(BinTree));
	BinTree n3 = (BinTree)malloc(sizeof(BinTree));
	BinTree n4 = (BinTree)malloc(sizeof(BinTree));
	BinTree n5 = (BinTree)malloc(sizeof(BinTree));
	BinTree n6 = (BinTree)malloc(sizeof(BinTree));
	BinTree n7 = (BinTree)malloc(sizeof(BinTree));
	BinTree n8 = (BinTree)malloc(sizeof(BinTree));
	BinTree n9 = (BinTree)malloc(sizeof(BinTree));
	n1->Key = 1;
	n2->Key = 2;
	n3->Key = 3;
	n4->Key = 4;
	n5->Key = 5;
	n6->Key = 6;
	n7->Key = 7;
	n8->Key = 8;
	n9->Key = 9;
	n4->Left = n3;
	n4->Right = n5;
	n3->Left = n1;
	n3->Right = NULL;
	n1->Left = NULL;
	n1->Right = n2;
	n2->Left = NULL;
	n2->Right = NULL;
	n5->Left = NULL;
	n5->Right = n7;
	n7->Left = n6;
	n7->Right = n8;
	n6->Left = NULL;
	n6->Right = NULL;
	n8->Left = NULL;
	n8->Right = NULL;
	n9->Left = NULL;
	n9->Right = NULL;
	return n4;
}

int isBST(BinTree T) {
	if (T == NULL)return 1;
	if (T->Left == NULL&&T->Right == NULL)return 1;
	if (T->Right == NULL) {
		if (findMax(T->Left) > T->Key)return 0;
		else return isBST(T->Left);
	}
	if (T->Left == NULL) {
		if (findMin(T->Right) < T->Key)return 0;
		else return isBST(T->Right);
	}
	if (findMax(T->Left) > T->Key || findMin(T->Right) < T->Key)return 0;
	else return isBST(T->Left)&isBST(T->Right);
}
int countLevel(BinTree T) {
	static int level = 0;
	int left, right;
	if (T != NULL)level++;
	if (T->Left == NULL&&T->Right == NULL)return 1;
	if (T->Left == NULL)return countLevel(T->Right) + 1;
	if (T->Right == NULL)return countLevel(T->Left) + 1;
	else {
		left = countLevel(T->Left);
		right = countLevel(T->Right);
		return (left > right ? (left + 1) : (right + 1));
	}
}
int countNodes(BinTree node, int count) {
	int para = count;
	if (node!=NULL) {
		count += countNodes(node->Left, para);
		count += countNodes(node->Right, para);
		count++;
		return count;
	}
	else return 0;
}
int rate(BinTree T, int K, int r) {
	if (r == K)
		if(T)return T->Key;
		else return 0;
	if (r < K)return rate(T->Left, K - r, countNodes(T->Left->Right, 0) + 1);
	if (r > K)return rate(T->Right, K, countNodes(T->Right->Right, 0) + 1);
}
int findMin(BinTree T) {
	int left, right;
	if (T->Left == NULL || T->Right == NULL)return T->Key;
	if (T->Left == NULL)return findMin(T->Right);
	if (T->Right == NULL)return findMin(T->Left);
	left = findMin(T->Left);
	right = findMin(T->Right);
	return T->Key < (left < right ? left : right) ? T->Key : (left < right ? left : right);
}
int findMax(BinTree T) {
	int left, right;
	if (T->Left == NULL || T->Right == NULL)return T->Key;
	if (T->Left == NULL)return findMax(T->Right);
	if (T->Right == NULL)return findMax(T->Left);
	left = findMax(T->Left);
	right = findMax(T->Right);
	return T->Key > (left > right ? left : right) ? T->Key : (left > right ? left : right);
}
int CheckBST(BinTree T, int K) {
	int is,first, rs;
	is = isBST(T);
	if (is == 0)return -countLevel(T);
	else {
		first = countNodes(T->Right, 0);
		rs = rate(T, K, first + 1);
		return rs;
	}
}