#include "main.h"
#include "desktop.h"

struct proc process[MAX_PROC];
int procNum = 0;
int procActive = 0;

void sgSetup() {
	initWindow(80, 30, "SuperGP OS", TEXT_MAP);
	initKey();
}
void sgLoop() {
	static int first = 1;
	int key;

	if (first) {
		regProc("desktop", desktopInit, desktopKey, desktopLoop);
		first = 0;
	}

	if (biosKey(1)) {
		key = biosKey(0);

		if (!process[0].keyFunc(key))
			if (procActive != 0)process[procActive].keyFunc(key);
	}
	for (int i = 0; i < procNum; i++) {
		process[i].loop();
	}
	return;
}

void regProc(char *name, void (*init)(), int (*func)(int key), void (*loop)()) {

	for (int i = 0; i < procNum; i++) {
		if (strcmp(name, process[i].name) == 0) {
			return;
		}
	}
	init();

	procActive = procNum;

	process[procNum].id = procNum;
	process[procNum].name = name;
	process[procNum].keyFunc = func;
	process[procNum++].loop = loop;
}
void disProc() {
	for (int i = procActive; i < procNum; i++) {
		process[i].id = process[i + 1].id;
		process[i].keyFunc = process[i + 1].keyFunc;
	}
	procNum--;
	procActive--;
}

