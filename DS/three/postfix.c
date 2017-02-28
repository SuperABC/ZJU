#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30
ElementType EvalPostfix(char *expr);
int main() {
	ElementType v;
	char expr[Max_Expr];
	gets(expr);
	v = EvalPostfix(expr);
	if (v < Infinity)
		printf("%f\n", v);
	else
		printf("ERROR\n");
	getchar();
	getchar();
	return 0;
}
ElementType EvalPostfix(char *expr) {
	double a[Max_Expr] = { 0 };
	char b[Max_Expr] = { 0 };
	int an = 0, bn = 0;
	while (*expr != '\0') {
		if (*expr == ' ')expr++;
		else if ((*expr == '-'&&*(expr + 1) != ' ') && *(expr + 1) != '\0') {
			a[an++] = atof(expr);
			while (*expr != ' '&&*expr != '\0')expr++;
		}
		else if (*expr == '+' || *expr == '-' || *expr == '*' || *expr == '/') {
			b[bn++] = *(expr++);
			if (an < 2)return Infinity+1;
			switch ((int)b[bn - 1]) {
			case '+':a[an - 2] = a[an - 2] + a[an-1];an--;break;
			case '-':a[an - 2] = a[an - 2] - a[an-1];an--;break;
			case '*':a[an - 2] = a[an - 2] * a[an-1];an--;break;
			case '/':if (a[an - 1] == 0)return Infinity + 1;
				a[an - 2] = a[an - 2] / a[an-1];an--;break;
			}
		}
		else {
			a[an++] = atof(expr);
			while (*expr != ' '&&*expr != '\0')expr++;
		}
	}
	if(an>1)return Infinity + 1;
	return a[0];
}