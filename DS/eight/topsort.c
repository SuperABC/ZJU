#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;
	PtrToAdjVNode Next;
};

typedef struct Vnode {
	PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;
	int Ne;
	AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool TopSort(LGraph Graph, Vertex TopOrder[]);

int main()
{
	int i;
	Vertex TopOrder[MaxVertexNum];
	LGraph G = ReadG();

	if (TopSort(G, TopOrder) == true)
		for (i = 0; i<G->Nv; i++)
			printf("%d ", TopOrder[i]);
	else
		printf("ERROR");
	printf("\n");
	getchar();
	getchar();
	return 0;
}
LGraph ReadG() {
	LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
	Vertex V, W;
	PtrToAdjVNode Temp_Now, Temp_Before;
	int i;
	scanf("%d %d", &(Graph->Nv), &(Graph->Ne));
	for (i = 0; i < Graph->Nv; i++) {
		Graph->G[i].FirstEdge = NULL;
	}
	for (i = 0; i < Graph->Ne; i++) {
		scanf("%d %d", &V, &W);
		Temp_Now = Temp_Before = Graph->G[V].FirstEdge;
		while (Temp_Now != NULL) {
			Temp_Before = Temp_Now;
			Temp_Now = Temp_Now->Next;
		}
		Temp_Now = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
		Temp_Now->AdjV = W;
		Temp_Now->Next = NULL;
		if (Temp_Before == NULL)
			Graph->G[V].FirstEdge = Temp_Now;
		else
			Temp_Before->Next = Temp_Now;
	}

	return Graph;
}
#define Enque(i) Queue[++front] = i
#define Deque(Q) Queue[rare++]
#define Empty(Q) (front-rare<0)
bool TopSort(LGraph Graph, Vertex TopOrder[]) {
	int i, j, tmp = 0, front = -1, rare = 0;
	int rti = 0;
	int Queue[MaxVertexNum];
	int Ind[MaxVertexNum] = { 0 };
	PtrToAdjVNode v;
	for (i = 0; i < Graph->Nv; i++) {
		v = Graph->G[i].FirstEdge;
		while (v) {
			Ind[v->AdjV]++;
			v = v->Next;
		}
	}
	for (i = 0; i < Graph->Nv; i++) {
		if (!Ind[i]) {
			Enque(i);
		}
	}
	while (!Empty(Queue)) {
		tmp = Deque(Queue);
		TopOrder[rti++] = tmp;
		v = Graph->G[tmp].FirstEdge;
		while (v) {
			if (--Ind[v->AdjV] == 0)Enque(v->AdjV);
			v = v->Next;
		}
	}
	for (i = 0; i < Graph->Nv; i++) {
		if (Ind[i])return false;
	}
	return true;
}