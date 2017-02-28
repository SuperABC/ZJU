#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ENQUE(a) (q[front++] = a)
#define DEQUE q[rear++]
#define EMPTY (front==rear)
int N, M;
int G[11][11] = { 0 };
int known[11] = { 0 };
int q[20];
int front = 0, rear = 0;
int l = 1;
int dfs(int i) {
	if (known[i] == 1)return 0;
	known[i] = 1;
	printf(" %d", i);
	for (int w = 0; w < N; w++) {
		if (G[i][w])dfs(w);
	}
	return 1;
}
int bfs(int i) {
	int j;
	if (known[i] == 1)return 0;
	known[i] = 1;
	printf(" %d", i);
	for (int w = 0; w < N; w++) {
		if (G[i][w] && !known[w]) {
			for (j = rear; j < front; j++) {
				if (q[j] == w)break;
			}
			if (j != front)continue;
			ENQUE(w);
		}
	}
	if (!EMPTY)bfs(DEQUE);
	return 1;
}

int main() {
	int tmp1, tmp2;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &tmp1, &tmp2);
		G[tmp1][tmp2] = 1;
		G[tmp2][tmp1] = 1;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (known[j] == 0) {
				if (l) {
					printf("{");
					l = 0;
				}
				break;
			}
		}
		if (!dfs(i))continue;
		l = 1;
		printf(" }\n");
	}
	memset(known, 0, 10 * sizeof(int));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (known[j] == 0) {
				if (l) {
					printf("{");
					l = 0;
				}
				break;
			}
		}
		if (!bfs(i))continue;
		l = 1;
		printf(" }\n");
	}
	getchar();
	getchar();
	return 0;
}