//Author: Zhu Ruisheng; ID:3150104497; No.01; 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Node {
	int num;
	int Next[101];
}T[101];
struct Res {
	int res[101];
}result[101];
int addlist[101], lstindex = 0, rsltindex = 0, weight;
//This function is used to find the path of equal weight recursively.
void cmp(int num, struct Node n) {
	int i = 0, j;
	if (n.Next[0] == 0) {
		if (num + n.num == weight) {
			addlist[lstindex++] = n.num;
			for (j = 0; j < lstindex; j++) {
				result[rsltindex].res[j] = addlist[j];
			}
			rsltindex++;
			addlist[lstindex--] = 0;
		}
		return;
	}
	else {
		addlist[lstindex++] = n.num;
		while (n.Next[i])cmp(num + n.num, T[n.Next[i++]]);
	}
	addlist[lstindex--] = 0;
}
//This function is used to sort the result.
int cmparr(const void *a, const void *b) {
	struct Res pa = *(struct Res *)a, pb = *(struct Res *)b;
	int d = 0;
	while (d <= 100) {
		if (pa.res[d] != pb.res[d])return pb.res[d] - pa.res[d];
		else d++;
	}
	return 0;
}
int main() {
	int all, non, i, j, tmp, tmpn;
	memset(T, 0, sizeof(T));
	memset(addlist, 0, sizeof(addlist));
	memset(result, 0, sizeof(result));
	scanf("%d %d %d", &all, &non, &weight);
	for (i = 0; i < all; i++) {
		T[i].num = 0;
		scanf("%d", &T[i].num);
	}
	for (i = 0; i < non; i++) {
		scanf("%02d %d", &tmp, &tmpn);
		for (j = 0; j < tmpn; j++) {
			scanf("%02d", &T[tmp].Next[j]);
		}
	}
	cmp(0, T[0]);
	qsort(result, rsltindex, sizeof(struct Res), cmparr);
	for (i = 0; i < rsltindex; i++) {
		printf("%d", result[i].res[0]);
		for (j = 1; result[i].res[j] != 0; j++) {
			printf(" %d", result[i].res[j]);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}
