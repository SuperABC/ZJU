#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main() {
	int r, i, temp = 0, ip, first = 1;
	int st[30] = { 0 }, lr[30] = { 0 };
	char *ch = malloc(5);
	scanf("%d", &r);
	i = 0;
	while (i < r) {
		scanf("%s", ch);
		if (strcmp(ch, "Push")==0) {
			scanf("%d", &ip);
			if (st[temp])temp++;
			st[temp] = ip;
			temp++;
			i++;
		}
		else if (strcmp(ch, "Pop")==0) {
			if (st[temp]) {
				if (first) {
					printf("%d", st[temp]);
					first = 0;
				}
				else {
					printf(" %d", st[temp]);
				}
				st[temp] = 0;
			}
			lr[temp] = 0;
			temp--;
			while (lr[temp] == 1) {
				if (first) {
					printf("%d", st[temp]);
					first = 0;
				}
				else {
					printf(" %d", st[temp]);
				}
				st[temp] = 0;
				lr[temp] = 0;
				temp--;
			}
			if (st[temp])lr[temp] = 1;
		}
	}
	while (temp>=0) {
		if (st[temp]) {
			if (first) {
				printf("%d", st[temp]);
				first = 0;
			}
			else {
				printf(" %d", st[temp]);
			}
			st[temp] = 0;
		}
		temp--;
	}
	getchar();
	getchar();
	return 0;
}