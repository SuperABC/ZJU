#pragma once
#include "main.h"
class light {
private:
	int index;
	bool on;
	bool mode;
	GLfloat lightPos[4];
	GLfloat lightAmb[4];
	GLfloat lightDif[4];
	GLfloat lightSpc[4];
public:
	light(int d);
	void enable(bool newl = TRUE);
	void disable();
	void update();
};
