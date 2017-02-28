#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
int cap, stations, problem, roads;
int rslt = 50000, back, time = 50000;
int init[501], dirdis[501][501], link[501][501], scaned[501], e[501], toltime[501], total[501], current[501], t[501];
void find(int x, int y) {
	t[y] = x;
	if (x == 0) {
		t[0] = y;
		return;
	}
	find(e[x], y + 1);
}
void operate(int x) {
	int xx;
	if (x == problem) {
		if (total[x]<rslt || (total[x] == rslt&&current[x]<back) || toltime[x]<time) {
			time = toltime[x];
			rslt = total[x];
			back = current[x];
			find(x, 1);
		}
		return;
	}
	scaned[x] = 1;
	for (int i = 1; i <= link[x][0]; ++i) {
		int ii = link[x][i];
		if (toltime[x] + dirdis[x][ii] <= toltime[ii] && scaned[ii] == 0) {
			if (init[ii] <= 0) {
				total[ii] = total[x];
				current[ii] = current[x] - init[ii];
				toltime[ii] = toltime[x] + dirdis[x][ii];
				e[ii] = x;
				operate(ii);
			}
			else {
				if (current[x] >= init[ii]) {
					total[ii] = total[x];
					current[ii] = current[x] - init[ii];
					toltime[ii] = toltime[x] + dirdis[x][ii];
					e[ii] = x;
					operate(ii);
				}
				else {
					total[ii] = total[x] + init[ii] - current[x];
					current[ii] = 0;
					toltime[ii] = toltime[x] + dirdis[x][ii];
					e[ii] = x;
					operate(ii);
				}
			}
		}
	}
	scaned[x] = 0;
}
int main()
{
	int tempa, tempb, tempt;
	memset(link, 0, sizeof(link));
	memset(dirdis, 0, sizeof(dirdis));
	memset(scaned, 0, sizeof(scaned));
	memset(e, 0, sizeof(e));
	memset(current, 0, sizeof(current));
	memset(total, 0, sizeof(total));
	memset(toltime, 0x7F, sizeof(toltime));
	scanf("%d %d %d %d", &cap, &stations, &problem, &roads);
	cap = cap / 2;
	for (int i = 1; i <= stations; ++i) {
		scanf("%d", init + i);
		init[i] = cap - init[i];
	}
	for (int i = 1; i <= roads; ++i) {
		scanf("%d %d %d", &tempa, &tempb, &tempt);
		dirdis[tempa][tempb] = dirdis[tempb][tempa] = tempt;
		link[tempa][0]++;
		link[tempb][0]++;
		link[tempa][link[tempa][0]] = tempb;
		link[tempb][link[tempb][0]] = tempa;
	}
	toltime[0] = 0;
	operate(0);
	printf("%d ", rslt);
	for (int i = t[0]; i >= 2; --i) {
		printf("%d->", t[i]);
	}
	printf("%d %d", t[1], back);
	getchar();
	getchar();
	return 0;
}