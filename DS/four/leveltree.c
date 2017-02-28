#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>

#define MaxTree 10
using namespace std;
typedef int ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
	ElementType Element;
	Tree  Left;
	Tree  Right;
};

Tree BuildTree() {
	Tree t1 = (Tree)malloc(sizeof(Tree));
	Tree t2 = (Tree)malloc(sizeof(Tree));
	Tree t3 = (Tree)malloc(sizeof(Tree));
	Tree t4 = (Tree)malloc(sizeof(Tree));
	Tree t5 = (Tree)malloc(sizeof(Tree));
	Tree t6 = (Tree)malloc(sizeof(Tree));
	Tree t7 = (Tree)malloc(sizeof(Tree));
	Tree t8 = (Tree)malloc(sizeof(Tree));
	Tree t9 = (Tree)malloc(sizeof(Tree));
	Tree t10 = (Tree)malloc(sizeof(Tree));
	t1->Element = 1;
	t2->Element = 2;
	t3->Element = 3;
	t4->Element = 4;
	t5->Element = 5;
	t6->Element = 6;
	t7->Element = 7;
	t8->Element = 8;
	t9->Element = 9;
	t10->Element = 10;
	t3->Left = t5;
	t3->Right = t6;
	t5->Left = t1;
	t5->Right = t8;
	t6->Left = NULL;
	t6->Right = t10;
	t8->Left = t9;
	t8->Right = NULL;
	t1->Left = NULL;
	t1->Right = NULL;
	t2->Left = NULL;
	t2->Right = NULL;
	t4->Left = NULL;
	t4->Right = NULL;
	t7->Left = NULL;
	t7->Right = NULL;
	t9->Left = NULL;
	t9->Right = NULL;
	t10->Left = NULL;
	t10->Right = NULL;
	return t3;
}

void PrintNode(Tree NodePtr){
	cout << NodePtr->Element;
}

void Level_order(Tree T, void(*visit)(Tree ThisNode));

int main(){
	Tree T = BuildTree();
	cout << "Level-order:";
	Level_order(T, PrintNode);
	return 0;
}

void Level_order(Tree T, void(*visit)(Tree ThisNode)) {
	Tree list[MaxTree] = { 0 };
	int i = 0, j, m = 1;
	list[0] = T;
	if (T == NULL)return;
	do {
		if(list[i])printf(" %d", list[i]->Element);
		if (list[i]->Left) {
			list[m] = list[i]->Left;
			m++;
		}
		if (list[i]->Right) {
			list[m] = list[i]->Right;
			m++;
		}
		list[i] = NULL;
		i++;
		for (j = 0; j < MaxTree; j++) {
			if (list[j])break;
		}
		if (j == MaxTree)break;
	} while (1);
}