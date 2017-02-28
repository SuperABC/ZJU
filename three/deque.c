#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
	ElementType Element;
	PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
	PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push(ElementType X, Deque D);
ElementType Pop(Deque D);
int Inject(ElementType X, Deque D);
ElementType Eject(Deque D);

Operation GetOp();
void PrintDeque(Deque D);

int main()
{
	ElementType X;
	Deque D;
	int done = 0;

	D = CreateDeque();
	while (!done) {
		switch (GetOp()) {
		case push:
			scanf("%d", &X);
			if (!Push(X, D)) printf("Memory is Full!\n");
			break;
		case pop:
			X = Pop(D);
			if (X == ERROR) printf("Deque is Empty!\n");
			break;
		case inject:
			scanf("%d", &X);
			if (!Inject(X, D)) printf("Memory is Full!\n");
			break;
		case eject:
			X = Eject(D);
			if (X == ERROR) printf("Deque is Empty!\n");
			break;
		case end:
			PrintDeque(D);
			done = 1;
			break;
		}
	}
	getchar();
	getchar();
	return 0;
}
Deque CreateDeque() {
	PtrToNode n;
	Deque rt = malloc(sizeof(Deque));
	n = malloc(sizeof(struct Node));
	n->Next = NULL;
	rt->Front = n;
	rt->Rear = n;
	return rt;
}
int Push(ElementType X, Deque D) {
	PtrToNode n, m;
	n = malloc(sizeof(struct Node));
	if (n == NULL)return 0;
	D->Front->Element = X;
	n->Next = D->Front;
	D->Front->Last = n;
	n->Last = NULL;
	D->Front = n;
	return 1;
}
ElementType Pop(Deque D) {
	if (D->Front == D->Rear)return ERROR;
	D->Front = D->Front->Next;
	free(D->Front->Last);
	D->Front->Last = NULL;
	return 0;
}
int Inject(ElementType X, Deque D) {
	PtrToNode n, m;
	n = malloc(sizeof(struct Node));
	if (n == NULL)return 0;
	n->Element = X;
	n->Last = D->Rear;
	D->Rear->Next= n;
	n->Next = NULL;
	D->Rear = n;
	return 1;
}
ElementType Eject(Deque D) {
	if (D->Front == D->Rear)return ERROR;
	D->Rear = D->Rear->Last;
	free(D->Rear->Next);
	D->Rear->Next= NULL;
	return 0;
}
Operation GetOp() {
	char * str=malloc(6*sizeof(char));
	scanf("%s", str);
	if (strcmp(str, "Push") == 0)return push;
	if (strcmp(str, "Pop") == 0)return pop;
	if (strcmp(str, "Inject") == 0)return inject;
	if (strcmp(str, "Eject") == 0)return eject;
	if (strcmp(str, "End") == 0)return end;
	return 6;
}
void PrintDeque(Deque D) {
	PtrToNode i = D->Front->Next;
	while (i != D->Rear) {
		printf("%d ", i->Element);
		i = i->Next;
	}
}
