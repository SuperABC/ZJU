#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Car {
	char *plate;//the car plate.
	int time;//the time that the car drive in or out.
	int inout;//drive in or drive out.
}T[10001];//all the records
struct TT {
	char *plate;//the car plate.
	int total;//the whole time that the car parked.
}Total[10001];//all the cars.
int check[86400];//the in and out message in each second.
int gettime(char *t) {//change the time string into the amount of seconds.
	int hh = (t[0] - '0') * 10 + t[1] - '0', mm = (t[3] - '0') * 10 + t[4] - '0', ss = (t[6] - '0') * 10 + t[7] - '0';
	return hh * 3600 + mm * 60 + ss;
}
int cmp(const void *x, const void *y) {//compare the two records.
	struct Car *xx = (struct Car *)x, *yy = (struct Car *)y;
	if (strcmp(xx->plate, yy->plate) == 0)return xx->time-yy->time;//sort the time if the plates are same.
	return strcmp(xx->plate, yy->plate);//sort the plate if the plates are different.
}
int main() {
	int record, test;
	int i, j, timenum, max = 0, tt = 0;
	char *timech = malloc(9), *io = malloc(4);
	scanf("%d %d", &record, &test);
	memset(check, 0, sizeof(check));
	memset(Total, 0, sizeof(Total));//basic initializings.
	for (i = 0; i < record; i++) {
		T[i].plate = malloc(8);//allocate the memory for the plate.
		scanf("%s%s%s", T[i].plate, timech, io);//get one record.
		T[i].time = gettime(timech);//change its time string into integer.
		if (strcmp("in", io) == 0)T[i].inout = 0;
		else if (strcmp("out", io) == 0)T[i].inout = 1;//judge it's driving in or out.
	}
	qsort(T, record, sizeof(T[0]), cmp);//sort the records.
	Total[0].plate = malloc(8);
	for (i = 1; i < record; ) {//delete those wrong records.
		if (strcmp(T[i].plate, T[i - 1].plate) == 0 && T[i].inout == 1 && T[i - 1].inout == 0) {
			check[T[i - 1].time]++;
			check[T[i].time]--;//put the right records into each second.
			if (strcmp(Total[tt].plate, T[i].plate)==0)Total[tt].total += T[i].time - T[i - 1].time;//add every time period of the same car.
			else {
				Total[++tt].plate = malloc(8);//a new car record.
				strcpy(Total[tt].plate, T[i].plate);
				Total[tt].total = T[i].time - T[i - 1].time;//the first time period of this car.
			}
			i += 2;
		}
		else i++;
	}
	for (i = 1; i<86400; i++)check[i] += check[i - 1];//add all the records before each second.
	while (test--) {
		scanf("%s", timech);
		timenum = gettime(timech);
		printf("%d\n", check[timenum]);
	}//give the number of the cars of each input time.
	for (j = 1; j <= tt; j++)if (Total[j].total>max)max = Total[j].total;//find the max time.
	for (j = 1; j <= tt; j++)if (Total[j].total == max)printf("%s ", Total[j].plate);//print the max time.
	printf("%02d:%02d:%02d\n", max / 3600, max % 3600 / 60, max % 60);//give the results.
	return 0;
}