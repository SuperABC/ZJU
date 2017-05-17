#pragma once
#include "main.h"
#include "enemy.h"
#define RIFLETOT 240
#define RIFLEVAL 20
#define PISTOLTOT 40
#define PISTOLVAL 4
#define ROCKETTOT 8
#define ROCKETVAL 1
class gun {
private:
	int type;
	int bulletLeft;
	int clipVol;
	int totalBullet;
	threeVect bulletPos[20] = { 0, 0, 0 };
	twoVect bulletDir[20] = { 0, 0 };
	int bulletDist[20] = { 0 };
	int outBullet = 0;
	int endBullet = 0;
	int fireIcon = 0;
	void updateGun();
	void buildHand();
	void showHand();
	void buildRifle();
	void showRifle();
	void buildPistol();
	void showPistol();
	void buildKnife();
	void showKnife();
	void buildRocket();
	void showRocket();
	void buildBlock();
	void showBlock();
	void showStar();
public:
	GLfloat RGB[3] = { 1, 1, 1 };
	int blockType = 1;
	gun(int t);
	void aim();
	void disaim();
	void shoot();
	void change();
	void show();
	friend bool enemy::beKilled();
};
