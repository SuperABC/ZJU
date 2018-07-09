#include "login.h"

textMap *loginCover;

char *user[MAX_USER_NUM];
int tmpUser = -1;

void loginInit() {
	loginCover = (textMap *)malloc(sizeof(textMap));
	getText(24, 7, 55, 21, loginCover);

	loginPanel();
}
int loginKey(int key) {
	if (key == SG_CTRL)return 0;
	if (key == SG_ESC) {
		putText(24, 7, loginCover);
		free(loginCover->content);
		free(loginCover);
		disProc();
	}
	return 1;
}
void loginLoop() {

}

void loginPanel() {
	setBfc(LIGHTGRAY, BLACK);
	for (int i = 8; i < 22; i++) {
		for (int j = 24; j < 56; j++) {
			writeChar(' ', j, i);
		}
	}
	setBfc(WHITE, BLACK);
	writeString("Login                           ", 24, 7);

	setBfc(LIGHTGRAY, BLACK);
	writeString("Admin       ", 34, 10);
	writeString("User        ", 34, 11);
	setBfc(RED, WHITE);
	writeString("Guest        ", 34, 12);
}