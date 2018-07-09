#ifndef SOS_TERMINAL
#define SOS_TERMINAL
#include "main.h"

void terminalInit();
int terminalKey(int key);
void terminalLoop();

void blackFrame();
void inputKey(int key);
void terminalPrint(char *s, int x, int y);
void rollScrn();
void finish();
void close();

void interprete();
void version();
void nocmd();

#endif