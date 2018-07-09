#include "terminal.h"

int curX = 0, curY = 0;
int baseX = 8, baseY = 3;
int sizeX = 64, sizeY = 24;
int cmdX = 5, cmdY = 0;

char inst[256];
int len = 0;

textMap *terminalCover;

void terminalInit() {
	terminalCover = (textMap *)malloc(sizeof(textMap));
	getText(baseX, baseY - 1, baseX + sizeX - 1, baseY + sizeY - 1, terminalCover);

	blackFrame();
	for (int i = 0; i < 256; i++)inst[i] = 0;
	len = 0;
}
int terminalKey(int key) {
	inputKey(key);
	return 0;
}
void terminalLoop() {

}

void blackFrame() {
	setBfc(BLACK, WHITE);
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 24; j++) {
			writeChar(' ', 8 + i, 3 + j);
		}
	}
	setBfc(WHITE, BLACK);
	writeString("Terminal --written by Super GP                                  ", 8, 2);

	setBfc(BLACK, LIGHTGRAY);
	writeString("SOS >_", 8, 3);

	curX = 5;
	curY = 0;
}
void inputKey(int key) {
	if (key >= 0x20 && key < 0x80) {
		setBfc(BLACK, WHITE);
		if (curX < sizeX - 1) {
			writeChar(key, baseX + curX, baseY + curY);
			writeChar('_', baseX + curX + 1, baseY + curY);
			curX++;
		}
		else {
			if (curY < sizeY - 1) {
				writeChar(key, baseX + curX, baseY + curY);
				writeChar('_', baseX, baseY + curY + 1);
				curX = 0;
				curY++;
			}
			else {
				writeChar(key, baseX + curX, baseY + curY);
				rollScrn();
				writeChar('_', baseX, baseY + curY);
				curX = 0;
			}
		}
		inst[len++] = key;
	}
	if (key == 0x08) {
		if (curX == cmdX&&curY == cmdY)return;
		if (curX > 0) {
			writeChar(' ', baseX + curX, baseY + curY);
			writeChar('_', baseX + curX - 1, baseY + curY);
			curX--;
		}
		else {
			writeChar(' ', baseX + curX, baseY + curY);
			writeChar('_', baseX + sizeX - 1, baseY + curY - 1);
			curX = sizeX - 1;
			curY--;
		}
		inst[len--] = 0;
	}
	if (key == '\r') {
		writeChar(' ', baseX + curX, baseY + curY);
		curX = 0;
		if (curY == sizeY - 1)rollScrn();
		else curY++;
		interprete();

		for (int i = 0; i < 256; i++)inst[i] = 0;
		len = 0;
	}
}
void rollScrn() {
	short c;
	setBfc(BLACK, WHITE);
	for (int i = 1; i < 24; i++) {
		for (int j = 0; j < 64; j++) {
			c = getShort(baseX + j, baseY + i);
			writeChar(c, baseX + j, baseY + i - 1);
			setCharColor(c >> 8, baseX + j, baseY + i - 1);
		}
	}
	for (int i = 0; i < 64; i++) {
		writeChar(' ', baseX + i, baseY + sizeY - 1);
	}
}
void terminalPrint(char *s, int x, int y) {
	if (strlen(s) < sizeX - curX) {
		writeString(s, baseX + x, baseY + y);
	}
	else {
		int i;
		for (i = x; i < sizeX; i++) {
			writeChar(s[i - x], baseX + i, baseY + y);
		}
		if (y == sizeY - 1)rollScrn();
		else {
			y++;
			curY++;
		}
		terminalPrint(s + sizeX - x, 0, y);
	}
}
void finish() {
	curX = 0;
	if (curY == sizeY - 1)rollScrn();
	else curY++;

	setBfc(BLACK, LIGHTGRAY);
	writeString("SOS >_", baseX + curX, baseY + curY);
	curX = 5;
}
void close() {
	putText(baseX, baseY - 1, terminalCover);
	free(terminalCover->content);
	free(terminalCover);
	disProc();
}

void interprete() {
	if (inst[0] == 0)finish();
	else if (strcmp(inst, "exit") == 0)close();
	else if (strcmp(inst, "version") == 0)version();
	else nocmd(); 
}
void version() {
	terminalPrint("SOS(Super Operating System)", curX, curY);

	curX = 0;
	if (curY == sizeY - 1)rollScrn();
	else curY++;
	terminalPrint("Coded by SG, GS, SS.", curX, curY);

	curX = 0;
	if (curY == sizeY - 1)rollScrn();
	else curY++;
	terminalPrint("Version v0.0. However, it's not a complete OS.", curX, curY);

	curX = 0;
	if (curY == sizeY - 1)rollScrn();
	else curY++;
	terminalPrint("We will add many other features next version.", curX, curY);

	curX = 0;
	if (curY == sizeY - 1)rollScrn();
	else curY++;
	if (curY == sizeY - 1)rollScrn();
	else curY++;
	terminalPrint("All rights reserved. 2017.10.30", curX, curY);

	finish();
}
void nocmd() {
	terminalPrint(strcat(inst, " is not a command or a executable program."), curX, curY);
	finish();
}