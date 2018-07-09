#ifndef SOS_MAIN
#define SOS_MAIN

#include "winsgl.h"
#pragma comment(lib, SG_LIB("winsgl"))

#define MAX_PROC 256

struct proc {
	int id;
	char *name;
	int(*keyFunc)(int key);
	void(*loop)();
};

void regProc(char *name, void(*init)(), int(*func)(int key), void(*loop)());
void disProc();

#endif