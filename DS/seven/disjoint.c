#define _CRT_SECURE_NO_WARNINGS
#include"stdio.h"
#include"stdlib.h"

#define MAXNUM 10010
typedef int DisjSet[MAXNUM];

void Initilialize(DisjSet S, int N);
void SetUnion(DisjSet S, int Rootl, int Root2);
int Find(int X, DisjSet S);
int ComponentsOfDisjSet(DisjSet S, int N);

int main(int argc, char argv[]) {
	int N, Count;
	int C1, C2;
	char Op;
	DisjSet S;

	scanf("%d", &N);
	Initilialize(S, N);
	getchar();

	while ((Op = getchar())!='S') {
		if (Op == 'I') {
			scanf("%d %d", &C1, &C2);
			getchar();
			SetUnion(S, Find(C1, S), Find(C2, S));
		}
		else if(Op == 'C') {
			scanf("%d%d", &C1, &C2);
			getchar();
			if (Find(C1, S) == Find(C2, S))
				printf("yes\n");
			else
				printf("no\n");
		}
	}
	Count = ComponentsOfDisjSet(S, N);
	if (Count == 1)
		printf("The network is connected.");
	else
		printf("There are %d components.", Count);

	return 0;
}

void Initilialize(DisjSet S, int N) {
	int i;
	for (i = 1; i <= N; i++)
		S[i] = -1;
}

void SetUnion(DisjSet S, int Root1, int Root2) {
	if (S[Root2] < S[Root1]) {
		S[Root2] = S[Root1] + S[Root2];
		S[Root1] = Root2;
	}
	else {
		S[Root1] = S[Root1] + S[Root2];
		S[Root2] = Root1;
	}
}

int Find(int X, DisjSet S) {
	if (S[X] < 0)
		return X;
	else
		return S[X] = Find(S[X], S);
}

int ComponentsOfDisjSet(DisjSet S, int N) {
	int Count = 0, i;
	for (i = 1; i <= N; i++)
		if (S[i] < 0)
			Count++;
	return Count;
}
