#ifndef SOS_LOGIN
#define SOS_LOGIN
#include "main.h"

#define MAX_USER_NUM 64

void loginInit();
int loginKey(int key);
void loginLoop();

void loginPanel();

#endif