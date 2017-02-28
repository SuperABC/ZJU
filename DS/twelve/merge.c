#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass(ElementType list[], ElementType sorted[], int N, int length);

void output(ElementType list[], int N)
{
	int i;
	for (i = 0; i<N; i++) printf("%d ", list[i]);
	printf("\n");
}

void  merge_sort(ElementType list[], int N)
{
	ElementType extra[MAXN];  /* the extra space required */
	int  length = 1;  /* current length of sublist being merged */
	while (length < N) {
		merge_pass(list, extra, N, length); /* merge list into extra */
		output(extra, N);
		length *= 2;
		merge_pass(extra, list, N, length); /* merge extra back to list */
		output(list, N);
		length *= 2;
	}
}


int main()
{
	int N, i;
	ElementType A[MAXN];

	scanf("%d", &N);
	for (i = 0; i<N; i++) scanf("%d", &A[i]);
	merge_sort(A, N);
	output(A, N);

	return 0;
}

#include <stdlib.h>
#include <string.h>
int cmp(const void *a, const void *b) {
	int *ma = (int *)a;
	int *mb = (int *)b;
	return *ma - *mb;
}
void merge_pass(ElementType list[], ElementType sorted[], int N, int length) {
	int i = 0;
	while (i + 2 * length <= N) {
		qsort(list + i, 2 * length, sizeof(int), cmp);
		i += 2 * length;
	}
	if(i!=N)qsort(list + i, N - i, sizeof(int), cmp);
	memcpy(sorted, list, N * sizeof(int));
}