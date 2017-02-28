#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char con[10000][1250];
short list[10000], lsn;
int total;
int comp = 0;
void input();
void check();
void DFS(int n);
int has(int n);
void whole();
int main() {
	char op;
	memset(con, 0, sizeof(con));
	memset(list, 0, sizeof(list));
	scanf("%d", &total);
	while ((op = getchar()) != 'S') {
		if (op == 'I')input();
		else if (op == 'C')check();
	}
	whole();
	getchar();
	getchar();
	return 0;
}
void input() {
	int n1, n2;
	scanf("%d %d", &n1, &n2);
	con[n1][n2 / 8] = (1 << (n2 % 8))|con[n1][n2 / 8];
	con[n2][n1 / 8] = (1 << (n1 % 8))|con[n2][n1 / 8];
}
void check() {
	int n1, n2, i;
	scanf("%d %d", &n1, &n2);
	memset(list, 0, sizeof(list));
	lsn = 0;
	DFS(n1);
	for (i = 1; i <= total; i++) {
		if (list[i] == n2)break;
	}
	if (i > total)printf("no\n");
	else printf("yes\n");
}
void DFS(int n) {
	int i;
	list[lsn++] = n;
	for (i = 1; i <= total; i++) {
		if ((con[n][i/8]&(1<<(i%8)))&&!has(i))DFS(i);
	}
}
int has(int n) {
	int i;
	for (i = 0; list[i] != 0; i++) {
		if (n == list[i])return 1;
	}
	return 0;
}
void whole() {
	int i;
	memset(list, 0, sizeof(list));
	lsn = 0;
	for (i = 1; i <= total; i++) {
		if (!has(i)) {
			comp++;
			DFS(i);
		}
	}
	if (comp == 1)printf("The network is connected.\n");
	else printf("There are 2 components.\n");
}