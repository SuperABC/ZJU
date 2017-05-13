#pragma once
#include "main.h"
#define TOTALENEMY 7
#define BOMBPOS 20
enum experience {
	BOMB,
	SOLDIER,
	KNIGHT,
	MOUSE,
	SUPER,
	TRANSF,
	BOSS,
	DEATH
};
class enemy {
private:
	int type;
	bool appear;
	int blood;
	GLfloat ex, ey, ez;
	GLfloat face_x, face_y, face_z, face_ang;
	bool changing, changeDir;
	inline bool inRange(int x, int y, int z);
public:
	enemy(int t, int p);
	void showEnemy();
	void randMove();
	void attachPlayer();
	bool beKilled();
	void leftMoney();
};
