#include "monitor.h"

textMap *monitorCover;

int selectPanel = 0;

void monitorInit() {
	monitorCover = (textMap *)malloc(sizeof(textMap));
	getText(10, 3, 69, 25, monitorCover);

	monitorPanel();
}
int monitorKey(int key) {
	if (key == SG_CTRL)return 0;
	if (key == SG_ESC) {
		putText(10, 3, monitorCover);
		free(monitorCover->content);
		free(monitorCover);
		disProc();
	}
	if (key == SG_RIGHT) {
		if (selectPanel == 0) {
			selectPanel = 1;
			for (int i = 0; i < 20; i++) {
				setCharColor(LIGHTGRAY << 4 | BLACK, 20 + i, 5);
			}
			for (int i = 0; i < 20; i++) {
				setCharColor(RED << 4 | WHITE, 40 + i, 5);
			}
		}
	}
	if (key == SG_LEFT) {
		if (selectPanel == 1) {
			selectPanel = 0;
			for (int i = 0; i < 20; i++) {
				setCharColor(RED << 4 | WHITE, 20 + i, 5);
			}
			for (int i = 0; i < 20; i++) {
				setCharColor(LIGHTGRAY << 4 | BLACK, 40 + i, 5);
			}
		}
	}
	return 1;
}
void monitorLoop() {

}

void monitorPanel() {
	setBfc(DARKGRAY, WHITE);
	for (int i = 4; i < 26; i++) {
		for (int j = 10; j < 70; j++) {
			writeChar(' ', j, i);
		}
	}
	setBfc(WHITE, BLACK);
	writeString("Monitor                                                     ", 10, 3);

	setBfc(LIGHTGRAY, BLACK);
	writeString("      Progress             Memory       ", 20, 5);
	for (int i = 0; i < 20; i++) {
		setCharColor(RED<<4 | WHITE, 20 + i, 5);
	}
}
void processPanel() {

}
void memoryPanel() {

}