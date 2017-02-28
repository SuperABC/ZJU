//Author: Zhu Ruisheng; ID:3150104497; No.02;

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define INF 65535
#define MAXP 150000
struct path {
	short city1, city2;
	int cost;
	char good;
}road[MAXP];
int cost[MAXP];
int pre[MAXP] = { 0 };
//This function is used to find the root node recursively.
int find(int c) {
	return (pre[c] == 0) ? (c) : (find(pre[c]));
}
//This function is used to sort the input records.
int cmp(const void *a, const void *b) {
	struct path *pa = (struct path*)a, *pb = (struct path*)b;
	if (pa->good == pb->good)return pa->good - pb->good;
	else return pa->good == 1 ? -1 : 1;
}
int main() {
	int N, M;
	int index = 0, count = 0, max = 0;
	int px, py;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d%d", &road[i].city1, &road[i].city2, &road[i].cost, &road[i].good);
	}
	qsort(road, M, sizeof(road[0]), cmp);
	for (int i = 1; i <= N; i++) {
		memset(pre, 0, (N+1)*sizeof(int));
		count = 0;
		index = -1;
		while (count < N - 2&&index < M) {
			index++;
			if (road[index].city1 == i || road[index].city2 == i)continue;
			px = find(road[index].city1);
			py = find(road[index].city2);
			if (px == py)continue;
			count++;
			pre[py] = px;
			if (!road[index].good)cost[i] += road[index].cost;
		}
		if (index == M&&count < N - 2)cost[i] = INF;
		if (cost[i] > max)max = cost[i];
	}
	if (max == 0)printf("0\n");
	else {
		int first = 1;
		for (int i = 1; i <= N; i++)
			if (cost[i] == max)
				if (first) {
					first = 0;
					printf("%d", i);
				}
				else printf(" %d", i);
	}
	system("pause");
	return 0;
}
