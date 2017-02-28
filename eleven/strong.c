#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef struct VNode *PtrToVNode;
struct VNode {
	int Vert;
	PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
	int NumOfVertices;
	int NumOfEdges;
	PtrToVNode Array[MaxVertices];
};

Graph ReadG() {
	Graph G = malloc(sizeof(Graph));
	G->NumOfVertices = 4;
	G->NumOfEdges = 5;
	for (int i = 0; i < 5; i++) {
		G->Array[i] = malloc(sizeof(struct VNode));
	}
	G->Array[0]->Vert = 1;
	G->Array[0]->Next = NULL;
	G->Array[1]->Vert = 2;
	G->Array[1]->Next = NULL;
	G->Array[2]->Vert = 0;
	G->Array[2]->Next = NULL;
	PtrToVNode tmp = malloc(sizeof(struct VNode));
	tmp->Vert = 2;
	tmp->Next = NULL;
	G->Array[3]->Vert = 1;
	G->Array[3]->Next = tmp;
	return G;
}

void PrintV(int V)
{
	printf("%d ", V);
}

void StronglyConnectedComponents(Graph G, void(*visit)(int V));

int main()
{
	Graph G = ReadG();
	StronglyConnectedComponents(G, PrintV);
	getchar();
	getchar();
	return 0;
}
int known[MaxVertices] = { 0 };
int printed[MaxVertices] = { 0 };
int next[MaxVertices] = { 0 };
void dfs(Graph G, int i, PtrToVNode V) {
	if (printed[i] == 1)return;
	if (known[i]) {
		while (1) {
			printf("%d ", i);
			printed[i] = 1;
			i = next[i];
			if (printed[i] == 1)break;
		}
		printf("\n");
	}
	else {
		while (V != NULL) {
			next[i] = V->Vert;
			known[i] = 1;
			dfs(G, V->Vert, G->Array[V->Vert]);
			known[i] = 0;
			V = V->Next;
		}
	}
}
void StronglyConnectedComponents(Graph G, void(*visit)(int V)) {
	memset(next, 255, MaxVertices*sizeof(int));
	for (int i = 0; i < G->NumOfVertices; i++) {
		if (known[i])continue;
		else {
			memset(known, 0, MaxVertices * sizeof(int));
			dfs(G, i, G->Array[i]);
		}
	}
	for (int i = 0; i < G->NumOfVertices; i++) {
		if (printed[i] == 0)printf("%d \n", i);
	}
}