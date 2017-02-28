#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
	ElementType Element;
	Position Next;
};

List Read();
void Print(List L);
List Reverse(List L);

int main()
{
	List L1, L2;
	L1 = Read();
	L2 = Reverse(L1);
	Print(L1->Next);
	printf("\n");
	Print(L2->Next);
	getchar();
	getchar();
	return 0;
}

List Read() {
	int n, i;
	List rt, j, next;
	scanf("%d", &n);
	next = j = rt = NULL;
	if (!n)return rt;
	j = malloc(sizeof(struct Node));
	j->Next = NULL;
	next = j;
	rt = j;
	for (i = 0; i < n; i++) {
		j = malloc(sizeof(struct Node));
		scanf("%d", &j->Element);
		j->Next = NULL;
		next->Next = j;
		next = next->Next;
	}
	return rt;
}

void Print(List L) {
	if (L == NULL) {
		return;
	}
	printf("%d ", L->Element);
	Print(L->Next);
}

List Reverse(List L) {
	Position pre, pos, next;
	List rt = NULL;
	if (L == NULL)return rt;
	L = L->Next;
	if (L == NULL) {
		next = rt;
		rt = malloc(sizeof(struct Node));
		rt->Next = next;
		return rt;
	}
	rt = malloc(sizeof(struct Node));
	rt->Element = L->Element;
	rt->Next = NULL;
	next = rt;
	if (L->Next == NULL) {
		next = rt;
		rt = malloc(sizeof(struct Node));
		rt->Next = next;
		return rt;
	}
	pre = L->Next;
	pos = L;
	while (pre != NULL) {
		L = pre;
		rt = malloc(sizeof(struct Node));
		rt->Element = L->Element;
		rt->Next = next;
		next = rt;
		pre = L->Next;
	}
	while (next != NULL) {
		pos->Element = next->Element;
		pos = pos->Next;
		next = next->Next;
	}
	next = rt;
	rt = malloc(sizeof(struct Node));
	rt->Next = next;
	return rt;
}