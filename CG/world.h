#pragma once
#include "main.h"
class block {
private:
	GLint bx, by, bz;
	void showUp();
	void showDown();
	void showLeft();
	void showRight();
	void showFront();
	void showBack();
public:
	GLuint type;
	GLfloat RGB[3];
	block(GLint x, GLint y, GLint z);
	directList isChosen(int octent);
	void showBlock(threeVect p);
	void buildBlock(int t, GLfloat r = 0, GLfloat g = 0, GLfloat b = 0);
	void destroyBlock();
};
