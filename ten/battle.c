#include <stdio.h>    
#include <stdlib.h>    
#include <string.h>  
#include <limits.h>  

#define MAX 300000

typedef struct road {
	int city1;
	int city2;
	int weight;
	int status;
}EDGE;

EDGE edge[MAX];

int pre[MAX];
int cost[MAX];

int find(int x) {
	while (pre[x] != 0) {
		x = pre[x];
	}
	return x;
}

int cmp(const void *a, const void *b) {
	if (((EDGE*)a)->status == ((EDGE*)b)->status) {
		return ((EDGE*)a)->weight, ((EDGE*)b)->weight;
	}
	return ((EDGE*)b)->status - ((EDGE*)a)->status;
}

int main() {
	int M, N, i, j;
	int count;
	int Fx, Fy;
	int max = 0;
	int flag;
	scanf("%d%d", &N, &M);
	for (i = 0; i < M; i++) {
		scanf("%d%d%d%d", &edge[i].city1, &edge[i].city2, &edge[i].weight, &edge[i].status);
	}
	qsort(edge, M, sizeof(edge[0]), cmp);
	for (i = 1; i <= N; i++) {
		count = 1;
		cost[i] = 0;
		memset(pre, 0, (N + 1) * sizeof(pre[0]));
		for (j = 0; j < M; j++) {
			if (edge[j].city1 == i || edge[j].city2 == i)continue; //city i has been captured
			Fx = find(edge[j].city1);
			Fy = find(edge[j].city2);
			if (Fx == Fy)continue;//already connected 
			count++;  //a new city has been added to the set  
			pre[Fx] = Fy;
			if (edge[j].status == 0)cost[i] += edge[j].weight;//need to repair the road  
		}
		if (count != N - 1)cost[i] = INT_MAX;//can't connect all the cities left
		if (cost[i] > max)max = cost[i];
	}
	if (max == 0)puts("0");//delete any city would cost nothing.
	else {
		flag = 1;
		for (i = 1; i <= N; i++) {
			if (cost[i] == max) {
				if (flag) {
					flag = 0;
					printf("%d", i);
				}
				else printf(" %d", i);
			}
		}
	}
	return 0;
}