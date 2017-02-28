#define _CRT_SECURE_NO_WARNINGS
#define INS 0
#define HEAP 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int N, sort;
int insb, heapb;
int list[100];
int tmp[100];
int cmp(const void *a, const void *b) {
	int *ha = (int *)a;
	int *hb = (int *)b;
	return *ha - *hb;
}
int heap(int i) {

	int pos = 0, last = heapb, max;
	tmp[pos] ^= tmp[last] ^= tmp[pos] ^= tmp[last];
	while (pos<last) {
		max = pos;
		if (pos * 2 + 1<last&&tmp[pos * 2 + 1]>tmp[max])
			max = pos * 2 + 1;
		if (pos * 2 + 2<last&&tmp[pos * 2 + 2]>tmp[max])
			max = pos * 2 + 2;
		if (max == pos)
			break;
		tmp[pos]^=tmp[max]^= tmp[pos] ^= tmp[max];
		pos = max;
	}
}
int main() {
	int i;
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", list + i);
	}
	for (i = 0; i < N; i++) {
		scanf("%d", tmp + i);
	}
	for (i = N - 1; i >= 0; i--) {
		if (list[i] == tmp[i])continue;
		else break;
	}
	while (i < N - 1 && tmp[i] < tmp[i + 1])i++;
	insb = i + 1;
	while (i >= 1) {
		if (tmp[i] >= tmp[i - 1])i--;
		else break;
	}
	if (!i)sort = INS;
	else sort = HEAP;
	printf(sort == INS ? "Insertion Sort\n" : "Heap Sort\n");
	if (sort == INS) {
		if(insb+1<=N)qsort(tmp, insb + 1, sizeof(int), cmp);
	}
	else {
		for (int j = N - 1; j >= 0; j--) {
			if (tmp[j]<tmp[0]) {
				heapb = j;
				break;
			}
			if (j == 0)goto end;
		}
		heap(1);
	}
end:
	for (i = 0; i < N - 1; i++) {	
		printf("%d ", tmp[i]);
	}
	printf("%d", tmp[N-1]);
	getchar();
	getchar();
	return 0;
}