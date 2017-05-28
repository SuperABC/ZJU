#pragma once
#include "main.h"
#include "enemy.h"
class player {
private:
	char *name;
	int blood;
	int status;
	int exp;
	int level;
public:
	player();
	~player();
	void isAttacked(int type);
	void addExp(int type);
	void showMsg();
};
