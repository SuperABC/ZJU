#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node {
	int Coefficient;
	int Exponent;
	PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read();
void Print(Polynomial p);
Polynomial Add(Polynomial a, Polynomial b);

int main(){
	Polynomial a, b, s;
	a = Read();
	b = Read();
	s = Add(a, b);
	Print(s);
	getchar();
	getchar();
	return 0;
}

Polynomial Read() {
	int n,i; 
	Polynomial rt, j, next;
	scanf("%d", &n);
	next = j = rt = NULL;
	if (!n)return rt;
	j = malloc(sizeof(struct Node));
	scanf("%d %d", &j->Coefficient, &j->Exponent);
	j->Next = NULL;
	next = j;
	rt = j;
	for (i = 1; i < n; i++) {
		j = malloc(sizeof(struct Node));
		scanf("%d %d", &j->Coefficient, &j->Exponent);
		j->Next = NULL;
		next->Next = j;
		next = next->Next;
	}
	return rt;
}

void Print(Polynomial p) {
	static int ov = 0;
	if (p == NULL) {
		return;
	}
	if (ov)printf(" ");
	else ov++;
	printf("%d %d", p->Coefficient, p->Exponent);
	Print(p->Next);
}

Polynomial Add(Polynomial a, Polynomial b) {
	Polynomial rs, i, next;
	next = i = rs = NULL;
	if (a == NULL&&b == NULL)return rs;
	i = malloc(sizeof(struct Node));
	i->Coefficient = 0;
	i->Exponent = (a->Exponent >= b->Exponent) ? a->Exponent : b->Exponent;
	if (i->Exponent == a->Exponent) {
		i->Coefficient += a->Coefficient;
		a = a->Next;
	}
	if (i->Exponent == b->Exponent) {
		i->Coefficient += b->Coefficient;
		b = b->Next;
	}
	i->Next = NULL;
	next = i;
	rs = i;
	while (a != NULL || b != NULL) {
		i = malloc(sizeof(struct Node));
		i->Coefficient = 0;
		if (a == NULL) {
			i->Exponent = b->Exponent;
			i->Coefficient = b->Coefficient;
			b = b->Next;
		}
		else if (b == NULL) {
			i->Exponent = a->Exponent;
			i->Coefficient = a->Coefficient;
			a = a->Next;
		}
		else {
			i->Exponent = (a->Exponent > b->Exponent) ? a->Exponent : b->Exponent;
			if (i->Exponent == a->Exponent) {
				i->Coefficient += a->Coefficient;
				a = a->Next;
			}
			if (i->Exponent == b->Exponent) {
				i->Coefficient += b->Coefficient;
				b = b->Next;
			}
		}
		if (i->Coefficient == 0) {
			i = NULL;
			continue;
		}
		i->Next = NULL;
		next->Next = i;
		next = next->Next;
	}
	return rs;
}
