#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
int judge(int *ele, int size, int cap);
int main(){
	int m, n, k, i, j, rs;
	int a[1000], full = 0;
	scanf("%d %d %d", &m, &n, &k);
	for(i = 0; i < k; i++){
		for(j = 0; j < n; j++){
			scanf("%d", &a[j]);
		}
		rs = judge(a, m, n);
		if(rs == 0)printf("NO\n");
		else printf("YES\n");
	}
	getchar();
	getchar();
	return 0;
}
int judge(int *ele, int size, int cap){ 
	int i = 0, j = 0;
	int a[1000] = {0}, an = 0;
	int b[1000] = {0}, bn = 0;
	for(i = 0; i < 1000; i++)b[i] = i+1;
	i = 0;
	while(i<cap){
		if(ele[i]>=b[bn]){
			for(j = b[bn]; j <= ele[i]; j++){
				a[an] = b[bn];
				an++;
				bn++;
				if(an > size)return 0;
			}
			a[an-1] = 0;
			an--;
		}
		else if(a[an-1]==ele[i]){
			a[an-1] = 0;
			an--;
		}
		else return 0;
		i++;
	}
	return 1;
}
