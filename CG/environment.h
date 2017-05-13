#pragma once
#include "main.h"
#include "light.h"
enum planetType {
	SUN,
	MOON,
	SKY
};

class planet {
private:
	int type;
	GLfloat Pos_x, Pos_y, Pos_z;
	GLfloat Vert_x, Vert_y, Vert_z;
	GLfloat Ang;
	GLfloat Dist;
public:
	planet(int t);
	friend class dt;
	void secPass();
	void show();
	friend light;
};
class dt {
private:
	int hour, min, sec;
	int year, month, day;
public:
	dt();
	void oneSec(planet &s, planet &m);
	bool inRange(int hour1, int min1, int sec1, int hour2, int min2, int sec2);
	friend void light::update();
	friend planet;
};
class fog {
private:
	int fogMode;
	GLfloat RGBA[4];
	GLfloat dense;
	GLfloat start, end;
public:
	fog();
	void update();
};