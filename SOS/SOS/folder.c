#include "folder.h"

textMap *folderCover;

char *tmpDir = "\\";

void folderInit() {
	folderCover = (textMap *)malloc(sizeof(textMap));
	getText(10, 3, 69, 25, folderCover);

	folderPanel();
}
int folderKey(int key) {
	if (key == SG_CTRL)return 0;
	if (key == SG_ESC) {
		putText(10, 3, folderCover);
		free(folderCover->content);
		free(folderCover);
		disProc();
	}
	return 1;
}
void folderLoop() {

}

void folderPanel() {
	setBfc(DARKGRAY, WHITE);
	for (int i = 4; i < 26; i++) {
		for (int j = 10; j < 70; j++) {
			writeChar(' ', j, i);
		}
	}
	setBfc(WHITE, BLACK);
	writeString("Explorer                                                    ", 10, 3);

	setBfc(LIGHTGRAY, CYAN);
	writeString("                                        ", 20, 5);
	writeString(tmpDir, 20, 5);
}