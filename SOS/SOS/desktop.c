#include "desktop.h"
#include "terminal.h"
#include "setting.h"
#include "login.h"
#include "folder.h"
#include "monitor.h"

int started = 0;
int selected = 0;

extern char *user[MAX_USER_NUM];
extern int tmpUser;

textMap *startCover;

void desktopInit() {
	backGround();
}
int desktopKey(int key) {
	if (started == 0) {
		if (key == SG_CTRL) {
			startList();
			return 1;
		}
	}
	else {
		if (key == SG_CTRL || key == SG_ESC) {
			clearStart();
			return 1;
		}
		if (key == SG_DOWN) {
			changeSelect(0);
			return 1;
		}
		if (key == SG_UP) {
			changeSelect(1);
			return 1;
		}
		if (key == '\r') {
			if (selected == 0)exit(0);
			else {
				clearStart();
				if (selected == 1) {
					regProc("login", loginInit, loginKey, loginLoop);
				}
				if (selected == 3) {
					regProc("setting", settingInit, settingKey, settingLoop);
				}
				if (selected == 4) {
					regProc("terminal", terminalInit, terminalKey, terminalLoop);
				}
				if (selected == 5) {
					regProc("explorer", folderInit, folderKey, folderLoop);
				}
				if (selected == 6) {
					regProc("monitor", monitorInit, monitorKey, monitorLoop);
				}
			}
			return 1;
		} 
		if (key == 'O' || key == 'o')exit(0);
		if (key == 'L' || key == 'l') {
			clearStart();
			regProc("login", loginInit, loginKey, loginLoop);
		}
		if (key == 'S' || key == 's') {
			clearStart();
			regProc("setting", settingInit, settingKey, settingLoop);
			return 1;
		}
		if (key == 'T' || key == 't') {
			clearStart();
			regProc("terminal", terminalInit, terminalKey, terminalLoop);
			return 1;
		}
		if (key == 'E' || key == 'e') {
			clearStart();
			regProc("folder", folderInit, folderKey, folderLoop);
			return 1;
		}
		if (key == 'M' || key == 'm') {
			clearStart();
			regProc("monitor", monitorInit, monitorKey, monitorLoop);
			return 1;
		}
	}
	return 0;
}
void desktopLoop() {

}

void backGround() {
	setBfc(BLUE, LIGHTCYAN);
	clearText();

	setBfc(BLACK, WHITE);
	writeString("Start", 0, 29);
	setCharColor(BLACK << 4 | LIGHTRED, 0, 29);
	setBfc(LIGHTCYAN, BLACK);
	writeString("                                                                           ", 5, 29);

	if (tmpUser == -1) {
		setBfc(BLUE, LIGHTCYAN);
		writeString("Hello, guest.", 0, 0);
	}
	else {
		setBfc(BLUE, LIGHTCYAN);
		writeString("Hello ", 0, 0);
		writeString(user[tmpUser], 6, 0);
	}
}
void startList() {
	startCover = (textMap *)malloc(sizeof(textMap));
	getText(0, 20, 9, 28, startCover);

	setBfc(DARKGRAY, BLACK);
	writeString("Turn Off  ", 0, 28);
	setCharFgc(WHITE, 5, 28);
	writeString("Log in    ", 0, 27);
	setCharFgc(WHITE, 0, 27);
	writeString("          ", 0, 26);

	writeString("Setting   ", 0, 25);
	setCharFgc(WHITE, 0, 25);
	writeString("Terminal  ", 0, 24);
	setCharFgc(WHITE, 0, 24);
	writeString("Explorer  ", 0, 23);
	setCharFgc(WHITE, 0, 23);
	writeString("Monitor   ", 0, 22);
	setCharFgc(WHITE, 0, 22);
	writeString("          ", 0, 21);

	setBfc(YELLOW, RED);
	writeString("Start list", 0, 20);

	for (int i = 0; i < 10; i++) {
		setCharBgc(RED, i, 28 - selected);
	}

	started = 1;
}
void clearStart() {
	putText(0, 20, startCover);
	free(startCover->content);
	free(startCover);
	started = 0;
}
void changeSelect(int dir) {
	for (int i = 0; i < 10; i++) {
		setCharBgc(DARKGRAY, i, 28 - selected);
	}
	if (dir == 0) {
		if (selected > 0)selected--;
		if (selected == 2)selected--;
	}
	if (dir == 1) {
		if (selected < 6)selected++;
		if (selected == 2)selected++;
	}
	for (int i = 0; i < 10; i++) {
		setCharBgc(RED, i, 28 - selected);
	}
}