#include <stdio.h>
#include <stdlib.h>
typedef struct TNode *BinTree;
struct TNode {
	int left;
	int right;
	int data;
};
typedef struct Queues *Queue;
struct Queues {
	struct TNode Elements[100];
	int front;
	int rear;
};
BinTree T;
int table[100];
Queue createQueue() {
	Queue q = (Queue)malloc(sizeof(Queue));
	q->front = q->rear = 0;
	return q;
}
void enQueue(Queue q, struct TNode item) {
	q->Elements[q->rear++] = item;
}
struct TNode deQueue(Queue q) {
	return q->Elements[q->front++];
}
void preOrder(struct TNode node) {
	if (node.left != -2) {
		printf("%d ", node.data);
		preOrder(T[node.left]);
		preOrder(T[node.right]);
	}
}
int countNodes(struct TNode node, int count) {
	int para = count;
	if (node.left != -2) {
		count += countNodes(T[node.left], para);
		count += countNodes(T[node.right], para);
		count++;
		return count;
	}
	else return 0;
}
int compare(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}
void insertBST(int start, int end, BinTree node) {
	if (node->left != -2) {
		int begin = start;
		int stop = start + countNodes(T[node->left], 0);
		node->data = table[stop];
		insertBST(begin, stop - 1, T + node->left);
		begin = stop + 1;
		stop = begin + countNodes(T[node->right], 0);
		insertBST(begin, stop - 1, T + node->right);
	}
}
void mediaOrder(BinTree T) {
	int count = 0;;
	Queue q = createQueue();
	enQueue(q, T[0]);
	while (q->front != q->rear) {
		struct TNode t = deQueue(q);
		if (count == 0) {
			count = 1;
			printf("%d", t.data);
		}
		else {
			printf(" %d", t.data);
		}
		if (T[t.left].data != -1) {
			enQueue(q, T[t.left]);
		}
		if (T[t.right].data != -1) {
			enQueue(q, T[t.right]);
		}
	}
	printf("\n");
}

int main() {
	int N;
	scanf("%d", &N);
	BinTree TempTree = (BinTree)malloc(sizeof(struct TNode)*(N + 1));
	TempTree->left = -2;
	TempTree->right = -2;
	TempTree->data = -1;
	T = TempTree + 1;
	for (int i = 0; i < N; i++) {
		BinTree node = T + i;
		node->data = 0;
		scanf("%d%d", &node->left, &node->right);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", table + i);
	}
	qsort(table, N, sizeof(int), compare);
	insertBST(0, N - 1, T + 0);
	mediaOrder(T);
	return 0;
}