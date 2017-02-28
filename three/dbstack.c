#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;

typedef struct StackRecord *Stack;
struct StackRecord {
	int Capacity;
	int Top1;
	int Top2;
	ElementType *Array;
};

Stack CreateStack(int MaxElements);
int IsEmpty(Stack S, int Stacknum);
int IsFull(Stack S);
int Push(ElementType X, Stack S, int Stacknum);
ElementType Top_Pop(Stack S, int Stacknum);

Operation GetOp();
void PrintStack(Stack S, int Stacknum);

int main()
{
	int N, Sn, X;
	Stack S;
	int done = 0;

	scanf("%d", &N);
	S = CreateStack(N);
	while (!done) {
		switch (GetOp()) {
		case push:
			scanf("%d %d", &Sn, &X);
			if (!Push(X, S, Sn)) printf("Stack %d is Full!\n", Sn);
			break;
		case pop:
			scanf("%d", &Sn);
			X = Top_Pop(S, Sn);
			if (X == ERROR) printf("Stack %d is Empty!\n", Sn);
			break;
		case end:
			PrintStack(S, 1);
			PrintStack(S, 2);
			done = 1;
			break;
		}
	}
	getchar();
	getchar();
	return 0;
}
Stack CreateStack(int MaxElements) {
	Stack rt = malloc(sizeof(struct StackRecord));
	rt->Capacity = MaxElements;
	rt->Top1 = 0;
	rt->Top2 = MaxElements - 1;
	rt->Array = malloc(MaxElements * sizeof(ElementType));
	return rt;
}
int IsEmpty(Stack S, int Stacknum) {
	if (Stacknum == 1 && S->Top1 == 0)return 1;
	if (Stacknum == 2 && S->Top2 == S->Capacity-1)return 1;
	return 0;
}
int IsFull(Stack S) {
	if (S->Top1 - 1 == S->Top2)return 1;
	return 0;
}
int Push(ElementType X, Stack S, int Stacknum) {
	if (IsFull(S))return 0;
	switch (Stacknum) {
	case 1:
		(S->Top1)++;
		S->Array[S->Top1 - 1] = X;
		break;
	case 2:
		(S->Top2)--;
		S->Array[S->Top2 + 1] = X;
		break;
	}
	return 1;
}
ElementType Top_Pop(Stack S, int Stacknum) {
	if (Stacknum == 1)
	{
		if (S->Top1 == 0)
		{
			return ERROR;
		}
		return S->Array[--S->Top1];
	}
	else
	{
		if (S->Top2 == S->Capacity - 1)
		{
			return ERROR;
		}
		return S->Array[++S->Top2];
	}
}
Operation GetOp() {
	char * str = malloc(5 * sizeof(char));
	scanf("%s", str);
	if (strcmp(str, "Push") == 0)return push;
	if (strcmp(str, "Pop") == 0)return pop;
	if (strcmp(str, "End") == 0)return end;
	return 3;
}
void PrintStack(Stack S, int Stacknum) {
	printf("Pop from Stack %d: ", Stacknum);
	switch (Stacknum) {
	case 1:
		S->Top1--;
		while (S->Top1 >= 0) {
			printf("%d ", S->Array[S->Top1]);
			S->Top1--;
		}
		break;
	case 2:
		S->Top2++;
		while (S->Top2 < S->Capacity) {
			printf("%d ", S->Array[S->Top2]);
			S->Top2++;
		}
	}
	printf("\n");
}
