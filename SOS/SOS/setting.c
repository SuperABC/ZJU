#include "setting.h"

textMap *settingCover;

int item = 0;
int enter = -1;

void settingInit() {
	settingCover = (textMap *)malloc(sizeof(textMap));
	getText(20, 5, 59, 23, settingCover);

	settingPanel();
	item = 0;
}
int settingKey(int key) {
	if (key == SG_CTRL)return 0;
	if (enter == -1) {
		if (key == SG_ESC) {
			putText(20, 5, settingCover);
			free(settingCover->content);
			free(settingCover);
			disProc();
		}
		else if (key == SG_UP) {
			if (item != 0) {
				for (int i = 0; i < 8; i++)
					for (int j = 0; j < 5; j++)
						setCharBgc(CYAN, 24 + i, 8 + j);
				setBfc(DARKGRAY, WHITE);
				for (int i = 0; i < 24; i++) {
					for (int j = 0; j < 14; j++) {
						writeChar(' ', 32 + i, 8 + j);
					}
				}
				switch (--item) {
				case 0:dispPanel(); break;
				case 1:devicePanel(); break;
				case 2:appPanel(); break;
				case 3:termPanel(); break;
				case 4:verPanel(); break;
				}
			}
		}
		else if (key == SG_DOWN) {
			if (item != 4) {
				for (int i = 0; i < 8; i++)
					for (int j = 0; j < 5; j++)
						setCharBgc(CYAN, 24 + i, 8 + j);
				setBfc(DARKGRAY, WHITE);
				for (int i = 0; i < 24; i++) {
					for (int j = 0; j < 14; j++) {
						writeChar(' ', 32 + i, 8 + j);
					}
				}
				switch (++item) {
				case 0:dispPanel(); break;
				case 1:devicePanel(); break;
				case 2:appPanel(); break;
				case 3:termPanel(); break;
				case 4:verPanel(); break;
				}
			}
		}
		else if (key == SG_RIGHT) {
			enter = item;
		}
	}
	else {
		if (key == 0x1B) {
			enter = -1;
			switch (item) {
			case 0:dispPanel(); break;
			case 1:devicePanel(); break;
			case 2:appPanel(); break;
			case 3:termPanel(); break;
			case 4:verPanel(); break;
			}
		}
	}
	return 1;
}
void settingLoop() {

}
 
void settingPanel() {
	setBfc(LIGHTGRAY, BLACK);
	for (int i = 6; i < 24; i++) {
		for (int j = 20; j < 60; j++) {
			writeChar(' ', j, i);
		}
	}
	setBfc(WHITE, BLACK);
	for (int i = 20; i < 60; i++) {
		writeString("Settings                                ", 20, 5);
	}

	setBfc(RED, WHITE);
	writeString("Disp    ", 24, 8);

	setBfc(CYAN, WHITE);
	writeString("Device  ", 24, 9);
	writeString("App     ", 24, 10);
	writeString("Term    ", 24, 11);
	writeString("Ver     ", 24, 12);

	setBfc(DARKGRAY, WHITE); 
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 14; j++) {
			writeChar(' ', 32 + i, 8 + j);
		}
	}
	dispPanel();
}

void dispPanel() {
	for (int i = 0; i < 8; i++) {
		setCharBgc(RED, 24 + i, 8);
	}

	setBfc(DARKGRAY, WHITE);
	writeString("Color style     ", 36, 10);
	writeString("Start side      ", 36, 12);
}
void devicePanel() {
	for (int i = 0; i < 8; i++) {
		setCharBgc(RED, 24 + i, 9);
	}
	setBfc(DARKGRAY, WHITE);
	writeString("Keyboard check  ", 36, 10);
	writeString("Screen check    ", 36, 12);
	writeString("Disc check      ", 36, 14);
}
void appPanel() {
	for (int i = 0; i < 8; i++) {
		setCharBgc(RED, 24 + i, 10);
	}
}
void termPanel() {
	for (int i = 0; i < 8; i++) {
		setCharBgc(RED, 24 + i, 11);
	}
}
void verPanel() {
	for (int i = 0; i < 8; i++) {
		setCharBgc(RED, 24 + i, 12);
	}
}
