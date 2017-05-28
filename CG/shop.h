#pragma once
#include "main.h"
class shop {
private:
	int level;
	GLfloat flySpeed;
public:
	shop();
	void inTo();
	void outOf();
	void stayIn();
	int isSelected();
	void showMsg();
	void showHouse();
};
