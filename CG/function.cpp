#include "main.h"
#include "environment.h"
#include "eye.h"
#include "gun.h"
#include "player.h"
#include "start.h"
#include "world.h"
#include "font.h"
#include "shop.h"
#include "enemy.h"
#include "file.h"
#include "texture.h"
#include "light.h"
#include "shadow.h"
#include "particle.h"

extern block *wholeWorld[2 * MAXBORDER][MAXHEIGHT][2 * MAXBORDER];
extern gun *gunArry[4];
extern eye playerEye;
extern int winsize[2];
extern GLuint texName;
extern light *lights[8];
extern systemp *Rain;
extern enemy *enemies[TOTALENEMY][100];

extern initGlobal initGV;
extern loadingGlobal loadingGV;
extern welcomeGlobal welcomeGV;
extern instructGlobal instructGV;
extern archiveGlobal archiveGV;
extern playingGlobal playingGV;
extern pauseGlobal pauseGV;
extern deadGlobal deadGV;
extern shopGlobal shopGV;
extern informationGlobal informationGV;
extern fileGlobal fileGV;

using std::cout;
using std::endl;
using std::cin;

inline bool checkFace(int i, int j, int k) {
	if (wholeWorld[i][j][k] == NULL)return FALSE;
	if (k < 0 || k>=2 * MAXBORDER)return FALSE;
	if (i < 0 || i>=2 * MAXBORDER)return FALSE;
	if (j < 0 || j>=MAXBORDER)return FALSE;
	if (i == 0 || j == 0 || k == 0)return FALSE;
	if (((int)wholeWorld[i][j + 1][k] & (int)wholeWorld[i][j - 1][k] & (int)wholeWorld[i + 1][j][k] & (int)wholeWorld[i - 1][j][k] & (int)wholeWorld[i][j][k + 1] & (int)wholeWorld[i][j][k - 1]) != 0)return FALSE;
	return TRUE;
}
inline bool inRect(int x, int y, int rx, int ry, int width, int height) {
	if (x >= rx&&x < rx + width&&y >= ry&&y < ry + height)return TRUE;
	else return FALSE;
}
inline GLfloat calcDist(struct threeVect v1, struct threeVect v2) {
	return sqrt(((v1.x) - (v2.x))*((v1.x) - (v2.x)) + ((v1.y) - (v2.y))*((v1.y) - (v2.y)) + ((v1.z) - (v2.z))*((v1.z) - (v2.z)));
}

void initPro() {
	int rt;
	LPWSTR rs;
	rt = MultiByteToWideChar(CP_ACP, 0, "Source\\2225476863.bgm", -1, NULL, 0);
	rs = (LPWSTR)malloc(rt * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, "Source\\2225476863.bgm", -1, rs, rt * sizeof(wchar_t));
	PlaySound(rs, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	glShadeModel(GL_FLAT);
	memset(wholeWorld, 0, sizeof(wholeWorld));
	lights[0] = new light(0);
	lights[1] = new light(1);
	lights[2] = new light(2);
	lights[3] = new light(3);
	lights[4] = new light(4);
	lights[5] = new light(5);
	lights[6] = new light(6);
	lights[7] = new light(7);
	gunArry[0] = new gun(0);
	gunArry[1] = new gun(1);
	gunArry[2] = new gun(2);
	gunArry[3] = new gun(3);
	gunArry[4] = new gun(4);
	gunArry[5] = new gun(5);
	for (int i = 0; i < BOMBPOS; i++) {
		enemies[BOMB][i] = new enemy(BOMB, i);
	}
	makeFont();
	allJPG();
	initGV.ent = TRUE;
	welcomeGV.accx = (float)0.0008;
	welcomeGV.accy = (float)0.0040;
	fileGV.isLoaded = -1;
}
void showMsg() {
	GLfloat color[3] = { 0.9, 0.9, 0.9 };
	int curx = 32, cury = winsize[1] - 40;
	if (initGV.time > 10)printString("Press any key to skip.", winsize[0] - 280, 40, color);
	if (initGV.time > 200)printString("Name: ", curx, cury, color);
	if (initGV.time > 280)printString("Super ", curx + 6 * 10, cury, color);
	if (initGV.time > 320)printString("Shoot.", curx + 12 * 10, cury, color);
	curx = 32;
	cury -= 18;
	if (initGV.time > 550)printString("Finished ", curx, cury, color);
	if (initGV.time > 620)printString("at ", curx + 9 * 10, cury, color);
	if (initGV.time > 690)printString("31, ", curx + 12 * 10, cury, color);
	if (initGV.time > 760)printString("12, ", curx + 16 * 10, cury, color);
	if (initGV.time > 830)printString("2016.", curx + 20 * 10, cury, color);
	curx = 32;
	cury -= 40;
	if (initGV.time > 960)printString("If ", curx, cury, color);
	if (initGV.time > 1020)printString("you ", curx + 3 * 10, cury, color);
	if (initGV.time > 1080)printString("are ", curx + 7 * 10, cury, color);
	if (initGV.time > 1140)printString("playing ", curx + 11 * 10, cury, color);
	if (initGV.time > 1200)printString("the ", curx + 19 * 10, cury, color);
	if (initGV.time > 1260)printString("first ", curx + 23 * 10, cury, color);
	if (initGV.time > 1320)printString("time, ", curx + 29 * 10, cury, color);
	curx = 32;
	cury -= 20;
	if (initGV.time > 1430)printString("please ", curx, cury, color);
	if (initGV.time > 1480)printString("read ", curx + 7 * 10, cury, color);
	if (initGV.time > 1530)printString("the ", curx + 12 * 10, cury, color);
	if (initGV.time > 1580)printString("instruction.", curx + 16 * 10, cury, color);
	curx = 32;
	cury -= 40;
	if (initGV.time > 1670)printString("Abstract ", curx, cury, color);
	if (initGV.time > 1710)printString("discription:", curx + 9 * 10, cury, color);
	curx = 32;
	cury -= 20;
	if (initGV.time > 1750)printString("This ", curx, cury, color);
	if (initGV.time > 1790)printString("is ", curx + 5 * 10, cury, color);
	if (initGV.time > 1830)printString("a ", curx + 8 * 10, cury, color);
	if (initGV.time > 1870)printString("FPS ", curx + 10 * 10, cury, color);
	if (initGV.time > 1910)printString("game ", curx + 14 * 10, cury, color);
	if (initGV.time > 1950)printString("derived ", curx + 19 * 10, cury, color);
	if (initGV.time > 1990)printString("from ", curx + 27 * 10, cury, color);
	if (initGV.time > 2030)printString("minecraft. ", curx + 32 * 10, cury, color);
	curx = 32;
	cury -= 20;
	if (initGV.time > 2100)printString("It ", curx, cury, color);
	if (initGV.time > 2130)printString("contains ", curx + 3 * 10, cury, color);
	if (initGV.time > 2160)printString("most ", curx + 12 * 10, cury, color);
	if (initGV.time > 2190)printString("elements ", curx + 17 * 10, cury, color);
	if (initGV.time > 2220)printString("that ", curx + 26 * 10, cury, color);
	if (initGV.time > 2250)printString("appeared ", curx + 31 * 10, cury, color);
	if (initGV.time > 2280)printString("in ", curx + 40 * 10, cury, color);
	if (initGV.time > 2310)printString("MC.", curx + 43 * 10, cury, color);
	curx = 32;
	cury -= 20;
	if (initGV.time > 2360)printString("Additionally, ", curx, cury, color);
	if (initGV.time > 2380)printString("we ", curx + 14 * 10, cury, color);
	if (initGV.time > 2400)printString("can ", curx + 17 * 10, cury, color);
	if (initGV.time > 2420)printString("use ", curx + 21 * 10, cury, color);
	if (initGV.time > 2440)printString("different ", curx + 25 * 10, cury, color);
	if (initGV.time > 2460)printString("weapons ", curx + 35 * 10, cury, color);
	if (initGV.time > 2480)printString("to ", curx + 43 * 10, cury, color);
	if (initGV.time > 2500)printString("attact ", curx + 46 * 10, cury, color);
	if (initGV.time > 2520)printString("enemies.", curx + 53 * 10, cury, color);
	curx = 32;
	cury -= 20;
	if (initGV.time > 2550)printString("The ", curx, cury, color);
	if (initGV.time > 2565)printString("usage ", curx + 4 * 10, cury, color);
	if (initGV.time > 2580)printString("of ", curx + 10 * 10, cury, color);
	if (initGV.time > 2595)printString("mouse ", curx + 13 * 10, cury, color);
	if (initGV.time > 2610)printString("and ", curx + 19 * 10, cury, color);
	if (initGV.time > 2625)printString("keyboard ", curx + 23 * 10, cury, color);
	if (initGV.time > 2640)printString("increase ", curx + 32 * 10, cury, color);
	if (initGV.time > 2655)printString("its ", curx + 41 * 10, cury, color);
	if (initGV.time > 2670)printString("reality. ", curx + 45 * 10, cury, color);
	curx = 32;
	cury -= 40;
	if (initGV.time > 2700)printString("Warning: ", curx, cury, color);
	curx = 32;
	cury -= 20;
	if (initGV.time > 2710)printString("Do ", curx, cury, color);
	if (initGV.time > 2720)printString("not ", curx + 3 * 10, cury, color);
	if (initGV.time > 2730)printString("indulge ", curx + 7 * 10, cury, color);
	if (initGV.time > 2740)printString("yourself ", curx + 15 * 10, cury, color);
	if (initGV.time > 2750)printString("and ", curx + 24 * 10, cury, color);
	if (initGV.time > 2760)printString("waste ", curx + 28 * 10, cury, color);
	if (initGV.time > 2770)printString("too ", curx + 34 * 10, cury, color);
	if (initGV.time > 2780)printString("much ", curx + 38 * 10, cury, color);
	if (initGV.time > 2790)printString("time ", curx + 43 * 10, cury, color);
	if (initGV.time > 2800)printString("on ", curx + 48 * 10, cury, color);
	if (initGV.time > 2810)printString("it.", curx + 51 * 10, cury, color);
	curx = 32;
	cury -= 40;
	if (initGV.time > 2830)printString("All ", curx, cury, color);
	if (initGV.time > 2835)printString("rights ", curx + 4 * 10, cury, color);
	if (initGV.time > 2840)printString("reserved.", curx + 11 * 10, cury, color);

}
void initSight(int m) {
	if (!m) {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(52, 1.5, 1, 40000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void plainWorld() {
	for (int i = 0; i < 2 * MAXBORDER; i++) {
		for (int j = 0; j < 1; j++) {
			for (int k = 0; k < 2 * MAXBORDER; k++) {
				if (!wholeWorld[i][j][k])wholeWorld[i][j][k] = new block(i, j, k);
				wholeWorld[i][j][k]->buildBlock(1, 0.1, 0.1, 0.1);
			}
		}
	}
	for (int i = 0; i < 2 * MAXBORDER; i++) {
		for (int j = 1; j < 5; j++) {
			for (int k = 0; k < 2 * MAXBORDER; k++) {
				if (!wholeWorld[i][j][k])wholeWorld[i][j][k] = new block(i, j, k);
				wholeWorld[i][j][k]->buildBlock(1, 0.3, 0.3, 0.1);
			}
		}
	}
	for (int i = 0; i < 2 * MAXBORDER; i++) {
		for (int j = 5; j < 6; j++) {
			for (int k = 0; k < 2 * MAXBORDER; k++) {
				if (!wholeWorld[i][j][k])wholeWorld[i][j][k] = new block(i, j, k);
				wholeWorld[i][j][k]->buildBlock(1, (GLfloat)(rand() % 11) / 10, (GLfloat)(rand() % 11) / 10, (GLfloat)(rand() % 11) / 10);
			}
		}
	}
}
void sightLimit() {
	int nx, ny, nz, i, j, k;
	struct threeVect tmpPos = playerEye.getPos(), tmpAt = playerEye.getAt();
	struct twoVect tmpAng = playerEye.getAng();
	nx = (int)tmpPos.x / BLOCKSIZE;
	ny = (int)tmpPos.y / BLOCKSIZE;
	nz = (int)tmpPos.z / BLOCKSIZE;
	nx /= 10;
	ny /= 10;
	nz /= 10;
	//glBegin(GL_QUADS);
	if (!(tmpAng.theta > PIE * 3 / 4 && tmpAng.theta < PIE * 7 / 4)) {
		for (i = (nx + 1) * 10; i < (nx + 3) * 10; i++) {
			for (j = (ny - 1) * 10; j < (ny + 2) * 10; j++) {
				for (k = (nz + 1) * 10; k < (nz + 3) * 10; k++) {
					if (checkFace(i, j, k))wholeWorld[i][j][k]->showBlock(tmpPos);
				}
			}
		}
	}
	if (tmpAng.theta > PIE / 4 && tmpAng.theta < PIE * 5 / 4) {
		for (i = (nx - 2) * 10; i < nx * 10; i++) {
			for (j = (ny - 1) * 10; j < (ny + 2) * 10; j++) {
				for (k = (nz + 1) * 10; k < (nz + 3) * 10; k++) {
					if (checkFace(i, j, k))wholeWorld[i][j][k]->showBlock(tmpPos);
				}
			}
		}
	}
	if (tmpAng.theta > PIE * 3 / 4 && tmpAng.theta < PIE * 7 / 4) {
		for (i = (nx - 2) * 10; i < nx * 10; i++) {
			for (j = (ny - 1) * 10; j < (ny + 2) * 10; j++) {
				for (k = (nz - 2) * 10; k < nz * 10; k++) {
					if (checkFace(i, j, k))wholeWorld[i][j][k]->showBlock(tmpPos);
				}
			}
		}
	}
	if (!(tmpAng.theta > PIE / 4 && tmpAng.theta < PIE * 5 / 4)) {
		for (i = (nx + 1) * 10; i < (nx + 3) * 10; i++) {
			for (j = (ny - 1) * 10; j < (ny + 2) * 10; j++) {
				for (k = (nz - 2) * 10; k < nz* 10; k++) {
					if (checkFace(i, j, k))wholeWorld[i][j][k]->showBlock(tmpPos);
				}
			}
		}
	}

	for (i = nx * 10; i < (nx + 1) * 10; i++) {
		for (j = (ny - 1) * 10; j < (ny + 2) * 10; j++) {
			for (k = nz * 10; k < (nz + 1) * 10; k++) {
				if (checkFace(i, j, k))wholeWorld[i][j][k]->showBlock(tmpPos);
			}
		}
	}

	if (!(tmpAng.theta > PIE * 3 / 4 && tmpAng.theta < PIE * 5 / 4)) {
		for (i = (nx + 1) * 10; i < (nx + 4) * 10; i++) {
			for (j = (ny - 1) * 10; j < (ny + 2) * 10; j++) {
				for (k = nz * 10; k < (nz + 1) * 10; k++) {
					if (checkFace(i, j, k))wholeWorld[i][j][k]->showBlock(tmpPos);
				}
			}
		}
	}
	if (tmpAng.theta > PIE * 1 / 4 && tmpAng.theta < PIE * 7 / 4) {
		for (i = (nx - 3) * 10; i < nx * 10; i++) {
			for (j = (ny - 1) * 10; j < (ny + 2) * 10; j++) {
				for (k = nz * 10; k < (nz + 1) * 10; k++) {
					if (checkFace(i, j, k))wholeWorld[i][j][k]->showBlock(tmpPos);
				}
			}
		}
	}
	if (!(tmpAng.theta > PIE *  5/ 4 && tmpAng.theta < PIE * 7 / 4)) {
		for (i = nx * 10; i < (nx + 1) * 10; i++) {
			for (j = (ny - 1) * 10; j < (ny + 2) * 10; j++) {
				for (k = (nz + 1) * 10; k < (nz + 4) * 10; k++) {
					if (checkFace(i, j, k))wholeWorld[i][j][k]->showBlock(tmpPos);
				}
			}
		}
	}
	if (!(tmpAng.theta > PIE * 1 / 4 && tmpAng.theta < PIE * 3 / 4)) {
		for (i = nx * 10; i < (nx + 1) * 10; i++) {
			for (j = (ny - 1) * 10; j < (ny + 2) * 10; j++) {
				for (k = (nz - 3) * 10; k < nz * 10; k++) {
					if (checkFace(i, j, k))wholeWorld[i][j][k]->showBlock(tmpPos);
				}
			}
		}
	}
	//glEnd();

}

void putBlock() {
	threeVect tmp = playerEye.getAt();
	if (tmp.y >= 0) {
		if (tmp.z >= 0) {
			if (tmp.x >= 0)putOctant(1);
			else putOctant(2);
		}
		else {
			if (tmp.x >= 0)putOctant(4);
			else putOctant(3);
		}
	}
	else {
		if (tmp.z >= 0) {
			if (tmp.x >= 0)putOctant(5);
			else putOctant(6);
		}
		else {
			if (tmp.x >= 0)putOctant(8);
			else putOctant(7);
		}
	}
}
void disBlock() {
	threeVect tmp = playerEye.getAt();
	if (tmp.y >= 0) {
		if (tmp.z >= 0) {
			if (tmp.x >= 0)disOctant(1);
			else disOctant(2);
		}
		else {
			if (tmp.x >= 0)disOctant(4);
			else disOctant(3);
		}
	}
	else {
		if (tmp.z >= 0) {
			if (tmp.x >= 0)disOctant(5);
			else disOctant(6);
		}
		else {
			if (tmp.x >= 0)disOctant(8);
			else disOctant(7);
		}
	}
}
void putOctant(int octant) {
	threeVect tmp = playerEye.getPos();
	int i = tmp.x / BLOCKSIZE;
	int j = tmp.y / BLOCKSIZE;
	int k = tmp.z / BLOCKSIZE;
	switch (octant) {
	case 1:
		if (creatBlock(i + 1, j, k, 0, 1))return;
		if (creatBlock(i, j, k + 1, 0, 1))return;
		if (creatBlock(i, j + 1, k, 0, 1))return;
		if (creatBlock(i + 1, j + 1, k, 0, 1))return;
		if (creatBlock(i, j + 1, k + 1, 0, 1))return;
		if (creatBlock(i + 1, j, k + 1, 0, 1))return;
		if (creatBlock(i + 1, j + 1, k + 1, 0, 1))return;
		if (creatBlock(i + 2, j, k, 0, 1))return;
		if (creatBlock(i + 2, j, k + 1, 0, 1))return;
		if (creatBlock(i, j, k + 2, 0, 1))return;
		if (creatBlock(i + 1, j, k + 2, 0, 1))return;
		if (creatBlock(i + 2, j, k + 2, 0, 1))return;
		if (creatBlock(i + 2, j + 1, k, 0, 1))return;
		if (creatBlock(i + 2, j + 1, k + 1, 0, 1))return;
		if (creatBlock(i, j + 1, k + 2, 0, 1))return;
		if (creatBlock(i + 1, j + 1, k + 2, 0, 1))return;
		if (creatBlock(i + 2, j + 1, k + 2, 0, 1))return;
		if (creatBlock(i, j + 2, k, 0, 1))return;
		if (creatBlock(i + 1, j + 2, k, 0, 1))return;
		if (creatBlock(i, j + 2, k + 1, 0, 1))return;
		if (creatBlock(i + 1, j + 2, k + 1, 0, 1))return;
		if (creatBlock(i + 2, j + 2, k, 0, 1))return;
		if (creatBlock(i + 2, j + 2, k + 1, 0, 1))return;
		if (creatBlock(i, j + 2, k + 2, 0, 1))return;
		if (creatBlock(i + 1, j + 2, k + 2, 0, 1))return;
		if (creatBlock(i + 2, j + 2, k + 2, 0, 1))return;
		if (creatBlock(i + 3, j, k, 0, 1))return;
		if (creatBlock(i + 3, j, k + 1, 0, 1))return;
		if (creatBlock(i + 3, j, k + 2, 0, 1))return;
		if (creatBlock(i, j, k + 3, 0, 1))return;
		if (creatBlock(i + 1, j, k + 3, 0, 1))return;
		if (creatBlock(i + 2, j, k + 3, 0, 1))return;
		if (creatBlock(i + 3, j + 1, k, 0, 1))return;
		if (creatBlock(i + 3, j + 1, k + 1, 0, 1))return;
		if (creatBlock(i + 3, j + 1, k + 2, 0, 1))return;
		if (creatBlock(i, j + 1, k + 3, 0, 1))return;
		if (creatBlock(i + 1, j + 1, k + 3, 0, 1))return;
		if (creatBlock(i + 2, j + 1, k + 3, 0, 1))return;
		if (creatBlock(i + 3, j + 2, k, 0, 1))return;
		if (creatBlock(i + 3, j + 2, k + 1, 0, 1))return;
		if (creatBlock(i + 3, j + 2, k + 2, 0, 1))return;
		if (creatBlock(i, j + 2, k + 3, 0, 1))return;
		if (creatBlock(i + 1, j + 2, k + 3, 0, 1))return;
		if (creatBlock(i + 2, j + 2, k + 3, 0, 1))return;
		if (creatBlock(i + 3, j, k + 3, 0, 1))return;
		if (creatBlock(i + 3, j + 1, k + 3, 0, 1))return;
		if (creatBlock(i + 3, j + 2, k + 3, 0, 1))return;
		if (creatBlock(i, j + 3, k, 0, 1))return;
		if (creatBlock(i + 1, j + 3, k, 0, 1))return;
		if (creatBlock(i, j + 3, k + 1, 0, 1))return;
		if (creatBlock(i + 1, j + 3, k + 1, 0, 1))return;
		if (creatBlock(i + 2, j + 3, k, 0, 1))return;
		if (creatBlock(i + 2, j + 3, k + 1, 0, 1))return;
		if (creatBlock(i, j + 3, k + 2, 0, 1))return;
		if (creatBlock(i + 1, j + 3, k + 2, 0, 1))return;
		if (creatBlock(i + 2, j + 3, k + 2, 0, 1))return;
		if (creatBlock(i, j + 3, k + 3, 0, 1))return;
		if (creatBlock(i + 1, j + 3, k + 3, 0, 1))return;
		if (creatBlock(i + 2, j + 3, k + 3, 0, 1))return;
		if (creatBlock(i + 3, j + 3, k, 0, 1))return;
		if (creatBlock(i + 3, j + 3, k + 1, 0, 1))return;
		if (creatBlock(i + 3, j + 3, k + 2, 0, 1))return;
		if (creatBlock(i + 3, j + 3, k + 3, 0, 1))return;
		break;
	case 2:
		if (creatBlock(i - 1, j, k, 0, 2))return;
		if (creatBlock(i, j, k + 1, 0, 2))return;
		if (creatBlock(i, j + 1, k, 0, 2))return;
		if (creatBlock(i - 1, j + 1, k, 0, 2))return;
		if (creatBlock(i, j + 1, k + 1, 0, 2))return;
		if (creatBlock(i - 1, j, k + 1, 0, 2))return;
		if (creatBlock(i - 1, j + 1, k + 1, 0, 2))return;
		if (creatBlock(i - 2, j, k, 0, 2))return;
		if (creatBlock(i - 2, j, k + 1, 0, 2))return;
		if (creatBlock(i, j, k + 2, 0, 2))return;
		if (creatBlock(i - 1, j, k + 2, 0, 2))return;
		if (creatBlock(i - 2, j, k + 2, 0, 2))return;
		if (creatBlock(i - 2, j + 1, k, 0, 2))return;
		if (creatBlock(i - 2, j + 1, k + 1, 0, 2))return;
		if (creatBlock(i, j + 1, k + 2, 0, 2))return;
		if (creatBlock(i - 1, j + 1, k + 2, 0, 2))return;
		if (creatBlock(i - 2, j + 1, k + 2, 0, 2))return;
		if (creatBlock(i, j + 2, k, 0, 2))return;
		if (creatBlock(i - 1, j + 2, k, 0, 2))return;
		if (creatBlock(i, j + 2, k + 1, 0, 2))return;
		if (creatBlock(i - 1, j + 2, k + 1, 0, 2))return;
		if (creatBlock(i - 2, j + 2, k, 0, 2))return;
		if (creatBlock(i - 2, j + 2, k + 1, 0, 2))return;
		if (creatBlock(i, j + 2, k + 2, 0, 2))return;
		if (creatBlock(i - 1, j + 2, k + 2, 0, 2))return;
		if (creatBlock(i - 2, j + 2, k + 2, 0, 2))return;
		if (creatBlock(i - 3, j, k, 0, 2))return;
		if (creatBlock(i - 3, j, k + 1, 0, 2))return;
		if (creatBlock(i - 3, j, k + 2, 0, 2))return;
		if (creatBlock(i, j, k + 3, 0, 2))return;
		if (creatBlock(i - 1, j, k + 3, 0, 2))return;
		if (creatBlock(i - 2, j, k + 3, 0, 2))return;
		if (creatBlock(i - 3, j + 1, k, 0, 2))return;
		if (creatBlock(i - 3, j + 1, k + 1, 0, 2))return;
		if (creatBlock(i - 3, j + 1, k + 2, 0, 2))return;
		if (creatBlock(i, j + 1, k + 3, 0, 2))return;
		if (creatBlock(i - 1, j + 1, k + 3, 0, 2))return;
		if (creatBlock(i - 2, j + 1, k + 3, 0, 2))return;
		if (creatBlock(i - 3, j + 2, k, 0, 2))return;
		if (creatBlock(i - 3, j + 2, k + 1, 0, 2))return;
		if (creatBlock(i - 3, j + 2, k + 2, 0, 2))return;
		if (creatBlock(i, j + 2, k + 3, 0, 2))return;
		if (creatBlock(i - 1, j + 2, k + 3, 0, 2))return;
		if (creatBlock(i - 2, j + 2, k + 3, 0, 2))return;
		if (creatBlock(i - 3, j, k + 3, 0, 2))return;
		if (creatBlock(i - 3, j + 1, k + 3, 0, 2))return;
		if (creatBlock(i - 3, j + 2, k + 3, 0, 2))return;
		if (creatBlock(i, j + 3, k, 0, 2))return;
		if (creatBlock(i - 1, j + 3, k, 0, 2))return;
		if (creatBlock(i, j + 3, k + 1, 0, 2))return;
		if (creatBlock(i - 1, j + 3, k + 1, 0, 2))return;
		if (creatBlock(i - 2, j + 3, k, 0, 2))return;
		if (creatBlock(i - 2, j + 3, k + 1, 0, 2))return;
		if (creatBlock(i, j - 3, k + 2, 0, 2))return;
		if (creatBlock(i - 1, j + 3, k + 2, 0, 2))return;
		if (creatBlock(i - 2, j + 3, k + 2, 0, 2))return;
		if (creatBlock(i, j + 3, k + 3, 0, 2))return;
		if (creatBlock(i - 1, j + 3, k + 3, 0, 2))return;
		if (creatBlock(i - 2, j + 3, k + 3, 0, 2))return;
		if (creatBlock(i - 3, j + 3, k, 0, 2))return;
		if (creatBlock(i - 3, j + 3, k + 1, 0, 2))return;
		if (creatBlock(i - 3, j + 3, k + 2, 0, 2))return;
		if (creatBlock(i - 3, j + 3, k + 3, 0, 2))return;
		break;
	case 3:
		if (creatBlock(i - 1, j, k, 0, 3))return;
		if (creatBlock(i, j, k - 1, 0, 3))return;
		if (creatBlock(i, j + 1, k, 0, 3))return;
		if (creatBlock(i - 1, j + 1, k, 0, 3))return;
		if (creatBlock(i, j + 1, k - 1, 0, 3))return;
		if (creatBlock(i - 1, j, k - 1, 0, 3))return;
		if (creatBlock(i - 1, j + 1, k - 1, 0, 3))return;
		if (creatBlock(i - 2, j, k, 0, 3))return;
		if (creatBlock(i - 2, j, k - 1, 0, 3))return;
		if (creatBlock(i, j, k - 2, 0, 3))return;
		if (creatBlock(i - 1, j, k - 2, 0, 3))return;
		if (creatBlock(i - 2, j, k - 2, 0, 3))return;
		if (creatBlock(i - 2, j + 1, k, 0, 3))return;
		if (creatBlock(i - 2, j + 1, k - 1, 0, 3))return;
		if (creatBlock(i, j + 1, k - 2, 0, 3))return;
		if (creatBlock(i - 1, j + 1, k - 2, 0, 3))return;
		if (creatBlock(i - 2, j + 1, k - 2, 0, 3))return;
		if (creatBlock(i, j + 2, k, 0, 3))return;
		if (creatBlock(i - 1, j + 2, k, 0, 3))return;
		if (creatBlock(i, j + 2, k - 1, 0, 3))return;
		if (creatBlock(i - 1, j + 2, k - 1, 0, 3))return;
		if (creatBlock(i - 2, j + 2, k, 0, 3))return;
		if (creatBlock(i - 2, j + 2, k - 1, 0, 3))return;
		if (creatBlock(i, j + 2, k - 2, 0, 3))return;
		if (creatBlock(i - 1, j + 2, k - 2, 0, 3))return;
		if (creatBlock(i - 2, j + 2, k - 2, 0, 3))return;
		if (creatBlock(i - 3, j, k, 0, 3))return;
		if (creatBlock(i - 3, j, k - 1, 0, 3))return;
		if (creatBlock(i - 3, j, k - 2, 0, 3))return;
		if (creatBlock(i, j, k - 3, 0, 3))return;
		if (creatBlock(i - 1, j, k - 3, 0, 3))return;
		if (creatBlock(i - 2, j, k - 3, 0, 3))return;
		if (creatBlock(i - 3, j + 1, k, 0, 3))return;
		if (creatBlock(i - 3, j + 1, k - 1, 0, 3))return;
		if (creatBlock(i - 3, j + 1, k - 2, 0, 3))return;
		if (creatBlock(i, j + 1, k - 3, 0, 3))return;
		if (creatBlock(i - 1, j + 1, k - 3, 0, 3))return;
		if (creatBlock(i - 2, j + 1, k - 3, 0, 3))return;
		if (creatBlock(i - 3, j + 2, k, 0, 3))return;
		if (creatBlock(i - 3, j + 2, k - 1, 0, 3))return;
		if (creatBlock(i - 3, j + 2, k - 2, 0, 3))return;
		if (creatBlock(i, j + 2, k - 3, 0, 3))return;
		if (creatBlock(i - 1, j + 2, k - 3, 0, 3))return;
		if (creatBlock(i - 2, j + 2, k - 3, 0, 3))return;
		if (creatBlock(i - 3, j, k - 3, 0, 3))return;
		if (creatBlock(i - 3, j + 1, k - 3, 0, 3))return;
		if (creatBlock(i - 3, j + 2, k - 3, 0, 3))return;
		if (creatBlock(i, j + 3, k, 0, 3))return;
		if (creatBlock(i - 1, j + 3, k, 0, 3))return;
		if (creatBlock(i, j + 3, k - 1, 0, 3))return;
		if (creatBlock(i - 1, j + 3, k - 1, 0, 3))return;
		if (creatBlock(i - 2, j + 3, k, 0, 3))return;
		if (creatBlock(i - 2, j + 3, k - 1, 0, 3))return;
		if (creatBlock(i, j + 3, k - 2, 0, 3))return;
		if (creatBlock(i - 1, j + 3, k - 2, 0, 3))return;
		if (creatBlock(i - 2, j + 3, k - 2, 0, 3))return;
		if (creatBlock(i, j + 3, k - 3, 0, 3))return;
		if (creatBlock(i - 1, j + 3, k - 3, 0, 3))return;
		if (creatBlock(i - 2, j + 3, k - 3, 0, 3))return;
		if (creatBlock(i - 3, j + 3, k, 0, 3))return;
		if (creatBlock(i - 3, j + 3, k - 1, 0, 3))return;
		if (creatBlock(i - 3, j + 3, k - 2, 0, 3))return;
		if (creatBlock(i - 3, j + 3, k - 3, 0, 3))return;
		break;
	case 4:
		if (creatBlock(i + 1, j, k, 0, 4))return;
		if (creatBlock(i, j, k - 1, 0, 4))return;
		if (creatBlock(i, j + 1, k, 0, 4))return;
		if (creatBlock(i + 1, j + 1, k, 0, 4))return;
		if (creatBlock(i, j + 1, k - 1, 0, 4))return;
		if (creatBlock(i + 1, j, k - 1, 0, 4))return;
		if (creatBlock(i + 1, j + 1, k - 1, 0, 4))return;
		if (creatBlock(i + 2, j, k, 0, 4))return;
		if (creatBlock(i + 2, j, k - 1, 0, 4))return;
		if (creatBlock(i, j, k - 2, 0, 4))return;
		if (creatBlock(i + 1, j, k - 2, 0, 4))return;
		if (creatBlock(i + 2, j, k - 2, 0, 4))return;
		if (creatBlock(i + 2, j + 1, k, 0, 4))return;
		if (creatBlock(i + 2, j + 1, k - 1, 0, 4))return;
		if (creatBlock(i, j + 1, k - 2, 0, 4))return;
		if (creatBlock(i + 1, j + 1, k - 2, 0, 4))return;
		if (creatBlock(i + 2, j + 1, k - 2, 0, 4))return;
		if (creatBlock(i, j + 2, k, 0, 4))return;
		if (creatBlock(i + 1, j + 2, k, 0, 4))return;
		if (creatBlock(i, j + 2, k - 1, 0, 4))return;
		if (creatBlock(i + 1, j + 2, k - 1, 0, 4))return;
		if (creatBlock(i + 2, j + 2, k, 0, 4))return;
		if (creatBlock(i + 2, j + 2, k - 1, 0, 4))return;
		if (creatBlock(i, j + 2, k - 2, 0, 4))return;
		if (creatBlock(i + 1, j + 2, k - 2, 0, 4))return;
		if (creatBlock(i + 2, j + 2, k - 2, 0, 4))return;
		if (creatBlock(i + 3, j, k, 0, 4))return;
		if (creatBlock(i + 3, j, k - 1, 0, 4))return;
		if (creatBlock(i + 3, j, k - 2, 0, 4))return;
		if (creatBlock(i, j, k - 3, 0, 4))return;
		if (creatBlock(i + 1, j, k - 3, 0, 4))return;
		if (creatBlock(i + 2, j, k - 3, 0, 4))return;
		if (creatBlock(i + 3, j + 1, k, 0, 4))return;
		if (creatBlock(i + 3, j + 1, k - 1, 0, 4))return;
		if (creatBlock(i + 3, j + 1, k - 2, 0, 4))return;
		if (creatBlock(i, j + 1, k - 3, 0, 4))return;
		if (creatBlock(i + 1, j + 1, k - 3, 0, 4))return;
		if (creatBlock(i + 2, j + 1, k - 3, 0, 4))return;
		if (creatBlock(i + 3, j + 2, k, 0, 4))return;
		if (creatBlock(i + 3, j + 2, k - 1, 0, 4))return;
		if (creatBlock(i + 3, j + 2, k - 2, 0, 4))return;
		if (creatBlock(i, j + 2, k - 3, 0, 4))return;
		if (creatBlock(i + 1, j + 2, k - 3, 0, 4))return;
		if (creatBlock(i + 2, j + 2, k - 3, 0, 4))return;
		if (creatBlock(i + 3, j, k - 3, 0, 4))return;
		if (creatBlock(i + 3, j + 1, k - 3, 0, 4))return;
		if (creatBlock(i + 3, j + 2, k - 3, 0, 4))return;
		if (creatBlock(i, j + 3, k, 0, 4))return;
		if (creatBlock(i + 1, j + 3, k, 0, 4))return;
		if (creatBlock(i, j + 3, k - 1, 0, 4))return;
		if (creatBlock(i + 1, j + 3, k - 1, 0, 4))return;
		if (creatBlock(i + 2, j + 3, k, 0, 4))return;
		if (creatBlock(i + 2, j + 3, k - 1, 0, 4))return;
		if (creatBlock(i, j + 3, k - 2, 0, 4))return;
		if (creatBlock(i + 1, j + 3, k - 2, 0, 4))return;
		if (creatBlock(i + 2, j + 3, k - 2, 0, 4))return;
		if (creatBlock(i, j + 3, k - 3, 0, 4))return;
		if (creatBlock(i + 1, j + 3, k - 3, 0, 4))return;
		if (creatBlock(i + 2, j + 3, k - 3, 0, 4))return;
		if (creatBlock(i + 3, j + 3, k, 0, 4))return;
		if (creatBlock(i + 3, j + 3, k - 1, 0, 4))return;
		if (creatBlock(i + 3, j + 3, k - 2, 0, 4))return;
		if (creatBlock(i + 3, j + 3, k - 3, 0, 4))return;
		break;
	case 5:
		if (creatBlock(i + 1, j, k, 0, 5))return;
		if (creatBlock(i, j, k + 1, 0, 5))return;
		if (creatBlock(i + 1, j - 1, k, 0, 5))return;
		if (creatBlock(i, j - 1, k + 1, 0, 5))return;
		if (creatBlock(i + 1, j, k + 1, 0, 5))return;
		if (creatBlock(i + 1, j - 1, k + 1, 0, 5))return;
		if (creatBlock(i + 2, j, k, 0, 5))return;
		if (creatBlock(i + 2, j, k + 1, 0, 5))return;
		if (creatBlock(i, j, k + 2, 0, 5))return;
		if (creatBlock(i + 1, j, k + 2, 0, 5))return;
		if (creatBlock(i + 2, j, k + 2, 0, 5))return;
		if (creatBlock(i + 2, j - 1, k, 0, 5))return;
		if (creatBlock(i + 2, j - 1, k + 1, 0, 5))return;
		if (creatBlock(i, j - 1, k + 2, 0, 5))return;
		if (creatBlock(i + 1, j - 1, k + 2, 0, 5))return;
		if (creatBlock(i + 2, j - 1, k + 2, 0, 5))return;
		if (creatBlock(i, j - 2, k, 0, 5))return;
		if (creatBlock(i + 1, j - 2, k, 0, 5))return;
		if (creatBlock(i, j - 2, k + 1, 0, 5))return;
		if (creatBlock(i + 1, j - 2, k + 1, 0, 5))return;
		if (creatBlock(i + 2, j - 2, k, 0, 5))return;
		if (creatBlock(i + 2, j - 2, k + 1, 0, 5))return;
		if (creatBlock(i, j - 2, k + 2, 0, 5))return;
		if (creatBlock(i + 1, j - 2, k + 2, 0, 5))return;
		if (creatBlock(i + 2, j - 2, k + 2, 0, 5))return;
		if (creatBlock(i + 3, j, k, 0, 5))return;
		if (creatBlock(i + 3, j, k + 1, 0, 5))return;
		if (creatBlock(i + 3, j, k + 2, 0, 5))return;
		if (creatBlock(i, j, k + 3, 0, 5))return;
		if (creatBlock(i + 1, j, k + 3, 0, 5))return;
		if (creatBlock(i + 2, j, k + 3, 0, 5))return;
		if (creatBlock(i + 3, j - 1, k, 0, 5))return;
		if (creatBlock(i + 3, j - 1, k + 1, 0, 5))return;
		if (creatBlock(i + 3, j - 1, k + 2, 0, 5))return;
		if (creatBlock(i, j - 1, k + 3, 0, 5))return;
		if (creatBlock(i + 1, j - 1, k + 3, 0, 5))return;
		if (creatBlock(i + 2, j - 1, k + 3, 0, 5))return;
		if (creatBlock(i + 3, j - 2, k, 0, 5))return;
		if (creatBlock(i + 3, j - 2, k + 1, 0, 5))return;
		if (creatBlock(i + 3, j - 2, k + 2, 0, 5))return;
		if (creatBlock(i, j - 2, k + 3, 0, 5))return;
		if (creatBlock(i + 1, j - 2, k + 3, 0, 5))return;
		if (creatBlock(i + 2, j - 2, k + 3, 0, 5))return;
		if (creatBlock(i + 3, j, k + 3, 0, 5))return;
		if (creatBlock(i + 3, j - 1, k + 3, 0, 5))return;
		if (creatBlock(i + 3, j - 2, k + 3, 0, 5))return;
		if (creatBlock(i, j - 3, k, 0, 5))return;
		if (creatBlock(i + 1, j - 3, k, 0, 5))return;
		if (creatBlock(i, j - 3, k + 1, 0, 5))return;
		if (creatBlock(i + 1, j - 3, k + 1, 0, 5))return;
		if (creatBlock(i + 2, j - 3, k, 0, 5))return;
		if (creatBlock(i + 2, j - 3, k + 1, 0, 5))return;
		if (creatBlock(i, j - 3, k + 2, 0, 5))return;
		if (creatBlock(i + 1, j - 3, k + 2, 0, 5))return;
		if (creatBlock(i + 2, j - 3, k + 2, 0, 5))return;
		if (creatBlock(i, j - 3, k + 3, 0, 5))return;
		if (creatBlock(i + 1, j - 3, k + 3, 0, 5))return;
		if (creatBlock(i + 2, j - 3, k + 3, 0, 5))return;
		if (creatBlock(i + 3, j - 3, k, 0, 5))return;
		if (creatBlock(i + 3, j - 3, k + 1, 0, 5))return;
		if (creatBlock(i + 3, j - 3, k + 2, 0, 5))return;
		if (creatBlock(i + 3, j - 3, k + 3, 0, 5))return;
		break;
	case 6:
		if (creatBlock(i - 1, j, k, 0, 6))return;
		if (creatBlock(i, j, k + 1, 0, 6))return;
		if (creatBlock(i - 1, j - 1, k, 0, 6))return;
		if (creatBlock(i, j - 1, k + 1, 0, 6))return;
		if (creatBlock(i - 1, j, k + 1, 0, 6))return;
		if (creatBlock(i - 1, j - 1, k + 1, 0, 6))return;
		if (creatBlock(i - 2, j, k, 0, 6))return;
		if (creatBlock(i - 2, j, k + 1, 0, 6))return;
		if (creatBlock(i, j, k + 2, 0, 6))return;
		if (creatBlock(i - 1, j, k + 2, 0, 6))return;
		if (creatBlock(i - 2, j, k + 2, 0, 6))return;
		if (creatBlock(i - 2, j - 1, k, 0, 6))return;
		if (creatBlock(i - 2, j - 1, k + 1, 0, 6))return;
		if (creatBlock(i, j - 1, k + 2, 0, 6))return;
		if (creatBlock(i - 1, j - 1, k + 2, 0, 6))return;
		if (creatBlock(i - 2, j - 1, k + 2, 0, 6))return;
		if (creatBlock(i, j - 2, k, 0, 6))return;
		if (creatBlock(i - 1, j - 2, k, 0, 6))return;
		if (creatBlock(i, j - 2, k + 1, 0, 6))return;
		if (creatBlock(i - 1, j - 2, k + 1, 0, 6))return;
		if (creatBlock(i - 2, j - 2, k, 0, 6))return;
		if (creatBlock(i - 2, j - 2, k + 1, 0, 6))return;
		if (creatBlock(i, j - 2, k + 2, 0, 6))return;
		if (creatBlock(i - 1, j - 2, k + 2, 0, 6))return;
		if (creatBlock(i - 2, j - 2, k + 2, 0, 6))return;
		if (creatBlock(i - 3, j, k, 0, 6))return;
		if (creatBlock(i - 3, j, k + 1, 0, 6))return;
		if (creatBlock(i - 3, j, k + 2, 0, 6))return;
		if (creatBlock(i, j, k + 3, 0, 6))return;
		if (creatBlock(i - 1, j, k + 3, 0, 6))return;
		if (creatBlock(i - 2, j, k + 3, 0, 6))return;
		if (creatBlock(i - 3, j - 1, k, 0, 6))return;
		if (creatBlock(i - 3, j - 1, k + 1, 0, 6))return;
		if (creatBlock(i - 3, j - 1, k + 2, 0, 6))return;
		if (creatBlock(i, j - 1, k + 3, 0, 6))return;
		if (creatBlock(i - 1, j - 1, k + 3, 0, 6))return;
		if (creatBlock(i - 2, j - 1, k + 3, 0, 6))return;
		if (creatBlock(i - 3, j - 2, k, 0, 6))return;
		if (creatBlock(i - 3, j - 2, k + 1, 0, 6))return;
		if (creatBlock(i - 3, j - 2, k + 2, 0, 6))return;
		if (creatBlock(i, j - 2, k + 3, 0, 6))return;
		if (creatBlock(i - 1, j - 2, k + 3, 0, 6))return;
		if (creatBlock(i - 2, j - 2, k + 3, 0, 6))return;
		if (creatBlock(i - 3, j, k + 3, 0, 6))return;
		if (creatBlock(i - 3, j - 1, k + 3, 0, 6))return;
		if (creatBlock(i - 3, j - 2, k + 3, 0, 6))return;
		if (creatBlock(i, j - 3, k, 0, 6))return;
		if (creatBlock(i - 1, j - 3, k, 0, 6))return;
		if (creatBlock(i, j - 3, k + 1, 0, 6))return;
		if (creatBlock(i - 1, j - 3, k + 1, 0, 6))return;
		if (creatBlock(i - 2, j - 3, k, 0, 6))return;
		if (creatBlock(i - 2, j - 3, k + 1, 0, 6))return;
		if (creatBlock(i, j - 3, k + 2, 0, 6))return;
		if (creatBlock(i - 1, j - 3, k + 2, 0, 6))return;
		if (creatBlock(i - 2, j - 3, k + 2, 0, 6))return;
		if (creatBlock(i, j - 3, k + 3, 0, 6))return;
		if (creatBlock(i - 1, j - 3, k + 3, 0, 6))return;
		if (creatBlock(i - 2, j - 3, k + 3, 0, 6))return;
		if (creatBlock(i - 3, j - 3, k, 0, 6))return;
		if (creatBlock(i - 3, j - 3, k + 1, 0, 6))return;
		if (creatBlock(i - 3, j - 3, k + 2, 0, 6))return;
		if (creatBlock(i - 3, j - 3, k + 3, 0, 6))return;
		break;
	case 7:
		if (creatBlock(i - 1, j, k, 0, 7))return;
		if (creatBlock(i, j, k - 1, 0, 7))return;
		if (creatBlock(i - 1, j - 1, k, 0, 7))return;
		if (creatBlock(i, j - 1, k - 1, 0, 7))return;
		if (creatBlock(i - 1, j, k - 1, 0, 7))return;
		if (creatBlock(i - 1, j - 1, k - 1, 0, 7))return;
		if (creatBlock(i - 2, j, k, 0, 7))return;
		if (creatBlock(i - 2, j, k - 1, 0, 7))return;
		if (creatBlock(i, j, k - 2, 0, 7))return;
		if (creatBlock(i - 1, j, k - 2, 0, 7))return;
		if (creatBlock(i - 2, j, k - 2, 0, 7))return;
		if (creatBlock(i - 2, j - 1, k, 0, 7))return;
		if (creatBlock(i - 2, j - 1, k - 1, 0, 7))return;
		if (creatBlock(i, j - 1, k - 2, 0, 7))return;
		if (creatBlock(i - 1, j - 1, k - 2, 0, 7))return;
		if (creatBlock(i - 2, j - 1, k - 2, 0, 7))return;
		if (creatBlock(i, j - 2, k, 0, 7))return;
		if (creatBlock(i - 1, j - 2, k, 0, 7))return;
		if (creatBlock(i, j - 2, k - 1, 0, 7))return;
		if (creatBlock(i - 1, j - 2, k - 1, 0, 7))return;
		if (creatBlock(i - 2, j - 2, k, 0, 7))return;
		if (creatBlock(i - 2, j - 2, k - 1, 0, 7))return;
		if (creatBlock(i, j - 2, k - 2, 0, 7))return;
		if (creatBlock(i - 1, j - 2, k - 2, 0, 7))return;
		if (creatBlock(i - 2, j - 2, k - 2, 0, 7))return;
		if (creatBlock(i - 3, j, k, 0, 7))return;
		if (creatBlock(i - 3, j, k - 1, 0, 7))return;
		if (creatBlock(i - 3, j, k - 2, 0, 7))return;
		if (creatBlock(i, j, k - 3, 0, 7))return;
		if (creatBlock(i - 1, j, k - 3, 0, 7))return;
		if (creatBlock(i - 2, j, k - 3, 0, 7))return;
		if (creatBlock(i - 3, j - 1, k, 0, 7))return;
		if (creatBlock(i - 3, j - 1, k - 1, 0, 7))return;
		if (creatBlock(i - 3, j - 1, k - 2, 0, 7))return;
		if (creatBlock(i, j - 1, k - 3, 0, 7))return;
		if (creatBlock(i - 1, j - 1, k - 3, 0, 7))return;
		if (creatBlock(i - 2, j - 1, k - 3, 0, 7))return;
		if (creatBlock(i - 3, j - 2, k, 0, 7))return;
		if (creatBlock(i - 3, j - 2, k - 1, 0, 7))return;
		if (creatBlock(i - 3, j - 2, k - 2, 0, 7))return;
		if (creatBlock(i, j - 2, k - 3, 0, 7))return;
		if (creatBlock(i - 1, j - 2, k - 3, 0, 7))return;
		if (creatBlock(i - 2, j - 2, k - 3, 0, 7))return;
		if (creatBlock(i - 3, j, k - 3, 0, 7))return;
		if (creatBlock(i - 3, j - 1, k - 3, 0, 7))return;
		if (creatBlock(i - 3, j - 2, k - 3, 0, 7))return;
		if (creatBlock(i, j - 3, k, 0, 7))return;
		if (creatBlock(i - 1, j - 3, k, 0, 7))return;
		if (creatBlock(i, j - 3, k - 1, 0, 7))return;
		if (creatBlock(i - 1, j - 3, k - 1, 0, 7))return;
		if (creatBlock(i - 2, j - 3, k, 0, 7))return;
		if (creatBlock(i - 2, j - 3, k - 1, 0, 7))return;
		if (creatBlock(i, j - 3, k - 2, 0, 7))return;
		if (creatBlock(i - 1, j - 3, k - 2, 0, 7))return;
		if (creatBlock(i - 2, j - 3, k - 2, 0, 7))return;
		if (creatBlock(i, j - 3, k - 3, 0, 7))return;
		if (creatBlock(i - 1, j - 3, k - 3, 0, 7))return;
		if (creatBlock(i - 2, j - 3, k - 3, 0, 7))return;
		if (creatBlock(i - 3, j - 3, k, 0, 7))return;
		if (creatBlock(i - 3, j - 3, k - 1, 0, 7))return;
		if (creatBlock(i - 3, j - 3, k - 2, 0, 7))return;
		if (creatBlock(i - 3, j - 3, k - 3, 0, 7))return;
		break;
	case 8:
		if (creatBlock(i + 1, j, k, 0, 8))return;
		if (creatBlock(i, j, k - 1, 0, 8))return;
		if (creatBlock(i + 1, j - 1, k, 0, 8))return;
		if (creatBlock(i, j - 1, k - 1, 0, 8))return;
		if (creatBlock(i + 1, j, k - 1, 0, 8))return;
		if (creatBlock(i + 1, j - 1, k - 1, 0, 8))return;
		if (creatBlock(i + 2, j, k, 0, 8))return;
		if (creatBlock(i + 2, j, k - 1, 0, 8))return;
		if (creatBlock(i, j, k - 2, 0, 8))return;
		if (creatBlock(i + 1, j, k - 2, 0, 8))return;
		if (creatBlock(i + 2, j, k - 2, 0, 8))return;
		if (creatBlock(i + 2, j - 1, k, 0, 8))return;
		if (creatBlock(i + 2, j - 1, k - 1, 0, 8))return;
		if (creatBlock(i, j - 1, k - 2, 0, 8))return;
		if (creatBlock(i + 1, j - 1, k - 2, 0, 8))return;
		if (creatBlock(i + 2, j - 1, k - 2, 0, 8))return;
		if (creatBlock(i, j - 2, k, 0, 8))return;
		if (creatBlock(i + 1, j - 2, k, 0, 8))return;
		if (creatBlock(i, j - 2, k - 1, 0, 8))return;
		if (creatBlock(i + 1, j - 2, k - 1, 0, 8))return;
		if (creatBlock(i + 2, j - 2, k, 0, 8))return;
		if (creatBlock(i + 2, j - 2, k - 1, 0, 8))return;
		if (creatBlock(i, j - 2, k - 2, 0, 8))return;
		if (creatBlock(i + 1, j - 2, k - 2, 0, 8))return;
		if (creatBlock(i + 2, j - 2, k - 2, 0, 8))return;
		if (creatBlock(i + 3, j, k, 0, 8))return;
		if (creatBlock(i + 3, j, k - 1, 0, 8))return;
		if (creatBlock(i + 3, j, k - 2, 0, 8))return;
		if (creatBlock(i, j, k - 3, 0, 8))return;
		if (creatBlock(i + 1, j, k - 3, 0, 8))return;
		if (creatBlock(i + 2, j, k - 3, 0, 8))return;
		if (creatBlock(i + 3, j - 1, k, 0, 8))return;
		if (creatBlock(i + 3, j - 1, k - 1, 0, 8))return;
		if (creatBlock(i + 3, j - 1, k - 2, 0, 8))return;
		if (creatBlock(i, j - 1, k - 3, 0, 8))return;
		if (creatBlock(i + 1, j - 1, k - 3, 0, 8))return;
		if (creatBlock(i + 2, j - 1, k - 3, 0, 8))return;
		if (creatBlock(i + 3, j - 2, k, 0, 8))return;
		if (creatBlock(i + 3, j - 2, k - 1, 0, 8))return;
		if (creatBlock(i + 3, j - 2, k - 2, 0, 8))return;
		if (creatBlock(i, j - 2, k - 3, 0, 8))return;
		if (creatBlock(i + 1, j - 2, k - 3, 0, 8))return;
		if (creatBlock(i + 2, j - 2, k - 3, 0, 8))return;
		if (creatBlock(i + 3, j, k - 3, 0, 8))return;
		if (creatBlock(i + 3, j - 1, k - 3, 0, 8))return;
		if (creatBlock(i + 3, j - 2, k - 3, 0, 8))return;
		if (creatBlock(i, j - 3, k, 0, 8))return;
		if (creatBlock(i + 1, j - 3, k, 0, 8))return;
		if (creatBlock(i, j - 3, k - 1, 0, 8))return;
		if (creatBlock(i + 1, j - 3, k - 1, 0, 8))return;
		if (creatBlock(i + 2, j - 3, k, 0, 8))return;
		if (creatBlock(i + 2, j - 3, k - 1, 0, 8))return;
		if (creatBlock(i, j - 3, k - 2, 0, 8))return;
		if (creatBlock(i + 1, j - 3, k - 2, 0, 8))return;
		if (creatBlock(i + 2, j - 3, k - 2, 0, 8))return;
		if (creatBlock(i, j - 3, k - 3, 0, 8))return;
		if (creatBlock(i + 1, j - 3, k - 3, 0, 8))return;
		if (creatBlock(i + 2, j - 3, k - 3, 0, 8))return;
		if (creatBlock(i + 3, j - 3, k, 0, 8))return;
		if (creatBlock(i + 3, j - 3, k - 1, 0, 8))return;
		if (creatBlock(i + 3, j - 3, k - 2, 0, 8))return;
		if (creatBlock(i + 3, j - 3, k - 3, 0, 8))return;
		break;
	}
}
void disOctant(int octant) {
	threeVect tmp = playerEye.getPos();
	int i = tmp.x / BLOCKSIZE;
	int j = tmp.y / BLOCKSIZE;
	int k = tmp.z / BLOCKSIZE;
	switch (octant) {
	case 1:
		if (clearBlock(i + 1, j, k, 1))return;
		if (clearBlock(i, j, k + 1, 1))return;
		if (clearBlock(i, j + 1, k, 1))return;
		if (clearBlock(i + 1, j + 1, k, 1))return;
		if (clearBlock(i, j + 1, k + 1, 1))return;
		if (clearBlock(i + 1, j, k + 1, 1))return;
		if (clearBlock(i + 1, j + 1, k + 1, 1))return;
		if (clearBlock(i + 2, j, k, 1))return;
		if (clearBlock(i + 2, j, k + 1, 1))return;
		if (clearBlock(i, j, k + 2, 1))return;
		if (clearBlock(i + 1, j, k + 2, 1))return;
		if (clearBlock(i + 2, j, k + 2, 1))return;
		if (clearBlock(i + 2, j + 1, k, 1))return;
		if (clearBlock(i + 2, j + 1, k + 1, 1))return;
		if (clearBlock(i, j + 1, k + 2, 1))return;
		if (clearBlock(i + 1, j + 1, k + 2, 1))return;
		if (clearBlock(i + 2, j + 1, k + 2, 1))return;
		if (clearBlock(i, j + 2, k, 1))return;
		if (clearBlock(i + 1, j + 2, k, 1))return;
		if (clearBlock(i, j + 2, k + 1, 1))return;
		if (clearBlock(i + 1, j + 2, k + 1, 1))return;
		if (clearBlock(i + 2, j + 2, k, 1))return;
		if (clearBlock(i + 2, j + 2, k + 1, 1))return;
		if (clearBlock(i, j + 2, k + 2, 1))return;
		if (clearBlock(i + 1, j + 2, k + 2, 1))return;
		if (clearBlock(i + 2, j + 2, k + 2, 1))return;
		if (clearBlock(i + 3, j, k, 1))return;
		if (clearBlock(i + 3, j, k + 1, 1))return;
		if (clearBlock(i + 3, j, k + 2, 1))return;
		if (clearBlock(i, j, k + 3, 1))return;
		if (clearBlock(i + 1, j, k + 3, 1))return;
		if (clearBlock(i + 2, j, k + 3, 1))return;
		if (clearBlock(i + 3, j + 1, k, 1))return;
		if (clearBlock(i + 3, j + 1, k + 1, 1))return;
		if (clearBlock(i + 3, j + 1, k + 2, 1))return;
		if (clearBlock(i, j + 1, k + 3, 1))return;
		if (clearBlock(i + 1, j + 1, k + 3, 1))return;
		if (clearBlock(i + 2, j + 1, k + 3, 1))return;
		if (clearBlock(i + 3, j + 2, k, 1))return;
		if (clearBlock(i + 3, j + 2, k + 1, 1))return;
		if (clearBlock(i + 3, j + 2, k + 2, 1))return;
		if (clearBlock(i, j + 2, k + 3, 1))return;
		if (clearBlock(i + 1, j + 2, k + 3, 1))return;
		if (clearBlock(i + 2, j + 2, k + 3, 1))return;
		if (clearBlock(i + 3, j, k + 3, 1))return;
		if (clearBlock(i + 3, j + 1, k + 3, 1))return;
		if (clearBlock(i + 3, j + 2, k + 3, 1))return;
		if (clearBlock(i, j + 3, k, 1))return;
		if (clearBlock(i + 1, j + 3, k, 1))return;
		if (clearBlock(i, j + 3, k + 1, 1))return;
		if (clearBlock(i + 1, j + 3, k + 1, 1))return;
		if (clearBlock(i + 2, j + 3, k, 1))return;
		if (clearBlock(i + 2, j + 3, k + 1, 1))return;
		if (clearBlock(i, j + 3, k + 2, 1))return;
		if (clearBlock(i + 1, j + 3, k + 2, 1))return;
		if (clearBlock(i + 2, j + 3, k + 2, 1))return;
		if (clearBlock(i, j + 3, k + 3, 1))return;
		if (clearBlock(i + 1, j + 3, k + 3, 1))return;
		if (clearBlock(i + 2, j + 3, k + 3, 1))return;
		if (clearBlock(i + 3, j + 3, k, 1))return;
		if (clearBlock(i + 3, j + 3, k + 1, 1))return;
		if (clearBlock(i + 3, j + 3, k + 2, 1))return;
		if (clearBlock(i + 3, j + 3, k + 3, 1))return;
		break;
	case 2:
		if (clearBlock(i - 1, j, k, 2))return;
		if (clearBlock(i, j, k + 1, 2))return;
		if (clearBlock(i, j + 1, k, 2))return;
		if (clearBlock(i - 1, j + 1, k, 2))return;
		if (clearBlock(i, j + 1, k + 1, 2))return;
		if (clearBlock(i - 1, j, k + 1, 2))return;
		if (clearBlock(i - 1, j + 1, k + 1, 2))return;
		if (clearBlock(i - 2, j, k, 2))return;
		if (clearBlock(i - 2, j, k + 1, 2))return;
		if (clearBlock(i, j, k + 2, 2))return;
		if (clearBlock(i - 1, j, k + 2, 2))return;
		if (clearBlock(i - 2, j, k + 2, 2))return;
		if (clearBlock(i - 2, j + 1, k, 2))return;
		if (clearBlock(i - 2, j + 1, k + 1, 2))return;
		if (clearBlock(i, j + 1, k + 2, 2))return;
		if (clearBlock(i - 1, j + 1, k + 2, 2))return;
		if (clearBlock(i - 2, j + 1, k + 2, 2))return;
		if (clearBlock(i, j + 2, k, 2))return;
		if (clearBlock(i - 1, j + 2, k, 2))return;
		if (clearBlock(i, j + 2, k + 1, 2))return;
		if (clearBlock(i - 1, j + 2, k + 1, 2))return;
		if (clearBlock(i - 2, j + 2, k, 2))return;
		if (clearBlock(i - 2, j + 2, k + 1, 2))return;
		if (clearBlock(i, j + 2, k + 2, 2))return;
		if (clearBlock(i - 1, j + 2, k + 2, 2))return;
		if (clearBlock(i - 2, j + 2, k + 2, 2))return;
		if (clearBlock(i - 3, j, k, 2))return;
		if (clearBlock(i - 3, j, k + 1, 2))return;
		if (clearBlock(i - 3, j, k + 2, 2))return;
		if (clearBlock(i, j, k + 3, 2))return;
		if (clearBlock(i - 1, j, k + 3, 2))return;
		if (clearBlock(i - 2, j, k + 3, 2))return;
		if (clearBlock(i - 3, j + 1, k, 2))return;
		if (clearBlock(i - 3, j + 1, k + 1, 2))return;
		if (clearBlock(i - 3, j + 1, k + 2, 2))return;
		if (clearBlock(i, j + 1, k + 3, 2))return;
		if (clearBlock(i - 1, j + 1, k + 3, 2))return;
		if (clearBlock(i - 2, j + 1, k + 3, 2))return;
		if (clearBlock(i - 3, j + 2, k, 2))return;
		if (clearBlock(i - 3, j + 2, k + 1, 2))return;
		if (clearBlock(i - 3, j + 2, k + 2, 2))return;
		if (clearBlock(i, j + 2, k + 3, 2))return;
		if (clearBlock(i - 1, j + 2, k + 3, 2))return;
		if (clearBlock(i - 2, j + 2, k + 3, 2))return;
		if (clearBlock(i - 3, j, k + 3, 2))return;
		if (clearBlock(i - 3, j + 1, k + 3, 2))return;
		if (clearBlock(i - 3, j + 2, k + 3, 2))return;
		if (clearBlock(i, j + 3, k, 2))return;
		if (clearBlock(i - 1, j + 3, k, 2))return;
		if (clearBlock(i, j + 3, k + 1, 2))return;
		if (clearBlock(i - 1, j + 3, k + 1, 2))return;
		if (clearBlock(i - 2, j + 3, k, 2))return;
		if (clearBlock(i - 2, j + 3, k + 1, 2))return;
		if (clearBlock(i, j - 3, k + 2, 2))return;
		if (clearBlock(i - 1, j + 3, k + 2, 2))return;
		if (clearBlock(i - 2, j + 3, k + 2, 2))return;
		if (clearBlock(i, j + 3, k + 3, 2))return;
		if (clearBlock(i - 1, j + 3, k + 3, 2))return;
		if (clearBlock(i - 2, j + 3, k + 3, 2))return;
		if (clearBlock(i - 3, j + 3, k, 2))return;
		if (clearBlock(i - 3, j + 3, k + 1, 2))return;
		if (clearBlock(i - 3, j + 3, k + 2, 2))return;
		if (clearBlock(i - 3, j + 3, k + 3, 2))return;
		break;
	case 3:
		if (clearBlock(i - 1, j, k, 3))return;
		if (clearBlock(i, j, k - 1, 3))return;
		if (clearBlock(i, j + 1, k, 3))return;
		if (clearBlock(i - 1, j + 1, k, 3))return;
		if (clearBlock(i, j + 1, k - 1, 3))return;
		if (clearBlock(i - 1, j, k - 1, 3))return;
		if (clearBlock(i - 1, j + 1, k - 1, 3))return;
		if (clearBlock(i - 2, j, k, 3))return;
		if (clearBlock(i - 2, j, k - 1, 3))return;
		if (clearBlock(i, j, k - 2, 3))return;
		if (clearBlock(i - 1, j, k - 2, 3))return;
		if (clearBlock(i - 2, j, k - 2, 3))return;
		if (clearBlock(i - 2, j + 1, k, 3))return;
		if (clearBlock(i - 2, j + 1, k - 1, 3))return;
		if (clearBlock(i, j + 1, k - 2, 3))return;
		if (clearBlock(i - 1, j + 1, k - 2, 3))return;
		if (clearBlock(i - 2, j + 1, k - 2, 3))return;
		if (clearBlock(i, j + 2, k, 3))return;
		if (clearBlock(i - 1, j + 2, k, 3))return;
		if (clearBlock(i, j + 2, k - 1, 3))return;
		if (clearBlock(i - 1, j + 2, k - 1, 3))return;
		if (clearBlock(i - 2, j + 2, k, 3))return;
		if (clearBlock(i - 2, j + 2, k - 1, 3))return;
		if (clearBlock(i, j + 2, k - 2, 3))return;
		if (clearBlock(i - 1, j + 2, k - 2, 3))return;
		if (clearBlock(i - 2, j + 2, k - 2, 3))return;
		if (clearBlock(i - 3, j, k, 3))return;
		if (clearBlock(i - 3, j, k - 1, 3))return;
		if (clearBlock(i - 3, j, k - 2, 3))return;
		if (clearBlock(i, j, k - 3, 3))return;
		if (clearBlock(i - 1, j, k - 3, 3))return;
		if (clearBlock(i - 2, j, k - 3, 3))return;
		if (clearBlock(i - 3, j + 1, k, 3))return;
		if (clearBlock(i - 3, j + 1, k - 1, 3))return;
		if (clearBlock(i - 3, j + 1, k - 2, 3))return;
		if (clearBlock(i, j + 1, k - 3, 3))return;
		if (clearBlock(i - 1, j + 1, k - 3, 3))return;
		if (clearBlock(i - 2, j + 1, k - 3, 3))return;
		if (clearBlock(i - 3, j + 2, k, 3))return;
		if (clearBlock(i - 3, j + 2, k - 1, 3))return;
		if (clearBlock(i - 3, j + 2, k - 2, 3))return;
		if (clearBlock(i, j + 2, k - 3, 3))return;
		if (clearBlock(i - 1, j + 2, k - 3, 3))return;
		if (clearBlock(i - 2, j + 2, k - 3, 3))return;
		if (clearBlock(i - 3, j, k - 3, 3))return;
		if (clearBlock(i - 3, j + 1, k - 3, 3))return;
		if (clearBlock(i - 3, j + 2, k - 3, 3))return;
		if (clearBlock(i, j + 3, k, 3))return;
		if (clearBlock(i - 1, j + 3, k, 3))return;
		if (clearBlock(i, j + 3, k - 1, 3))return;
		if (clearBlock(i - 1, j + 3, k - 1, 3))return;
		if (clearBlock(i - 2, j + 3, k, 3))return;
		if (clearBlock(i - 2, j + 3, k - 1, 3))return;
		if (clearBlock(i, j + 3, k - 2, 3))return;
		if (clearBlock(i - 1, j + 3, k - 2, 3))return;
		if (clearBlock(i - 2, j + 3, k - 2, 3))return;
		if (clearBlock(i, j + 3, k - 3, 3))return;
		if (clearBlock(i - 1, j + 3, k - 3, 3))return;
		if (clearBlock(i - 2, j + 3, k - 3, 3))return;
		if (clearBlock(i - 3, j + 3, k, 3))return;
		if (clearBlock(i - 3, j + 3, k - 1, 3))return;
		if (clearBlock(i - 3, j + 3, k - 2, 3))return;
		if (clearBlock(i - 3, j + 3, k - 3, 3))return;
		break;
	case 4:
		if (clearBlock(i + 1, j, k, 4))return;
		if (clearBlock(i, j, k - 1, 4))return;
		if (clearBlock(i, j + 1, k, 4))return;
		if (clearBlock(i + 1, j + 1, k, 4))return;
		if (clearBlock(i, j + 1, k - 1, 4))return;
		if (clearBlock(i + 1, j, k - 1, 4))return;
		if (clearBlock(i + 1, j + 1, k - 1, 4))return;
		if (clearBlock(i + 2, j, k, 4))return;
		if (clearBlock(i + 2, j, k - 1, 4))return;
		if (clearBlock(i, j, k - 2, 4))return;
		if (clearBlock(i + 1, j, k - 2, 4))return;
		if (clearBlock(i + 2, j, k - 2, 4))return;
		if (clearBlock(i + 2, j + 1, k, 4))return;
		if (clearBlock(i + 2, j + 1, k - 1, 4))return;
		if (clearBlock(i, j + 1, k - 2, 4))return;
		if (clearBlock(i + 1, j + 1, k - 2, 4))return;
		if (clearBlock(i + 2, j + 1, k - 2, 4))return;
		if (clearBlock(i, j + 2, k, 4))return;
		if (clearBlock(i + 1, j + 2, k, 4))return;
		if (clearBlock(i, j + 2, k - 1, 4))return;
		if (clearBlock(i + 1, j + 2, k - 1, 4))return;
		if (clearBlock(i + 2, j + 2, k, 4))return;
		if (clearBlock(i + 2, j + 2, k - 1, 4))return;
		if (clearBlock(i, j + 2, k - 2, 4))return;
		if (clearBlock(i + 1, j + 2, k - 2, 4))return;
		if (clearBlock(i + 2, j + 2, k - 2, 4))return;
		if (clearBlock(i + 3, j, k, 4))return;
		if (clearBlock(i + 3, j, k - 1, 4))return;
		if (clearBlock(i + 3, j, k - 2, 4))return;
		if (clearBlock(i, j, k - 3, 4))return;
		if (clearBlock(i + 1, j, k - 3, 4))return;
		if (clearBlock(i + 2, j, k - 3, 4))return;
		if (clearBlock(i + 3, j + 1, k, 4))return;
		if (clearBlock(i + 3, j + 1, k - 1, 4))return;
		if (clearBlock(i + 3, j + 1, k - 2, 4))return;
		if (clearBlock(i, j + 1, k - 3, 4))return;
		if (clearBlock(i + 1, j + 1, k - 3, 4))return;
		if (clearBlock(i + 2, j + 1, k - 3, 4))return;
		if (clearBlock(i + 3, j + 2, k, 4))return;
		if (clearBlock(i + 3, j + 2, k - 1, 4))return;
		if (clearBlock(i + 3, j + 2, k - 2, 4))return;
		if (clearBlock(i, j + 2, k - 3, 4))return;
		if (clearBlock(i + 1, j + 2, k - 3, 4))return;
		if (clearBlock(i + 2, j + 2, k - 3, 4))return;
		if (clearBlock(i + 3, j, k - 3, 4))return;
		if (clearBlock(i + 3, j + 1, k - 3, 4))return;
		if (clearBlock(i + 3, j + 2, k - 3, 4))return;
		if (clearBlock(i, j + 3, k, 4))return;
		if (clearBlock(i + 1, j + 3, k, 4))return;
		if (clearBlock(i, j + 3, k - 1, 4))return;
		if (clearBlock(i + 1, j + 3, k - 1, 4))return;
		if (clearBlock(i + 2, j + 3, k, 4))return;
		if (clearBlock(i + 2, j + 3, k - 1, 4))return;
		if (clearBlock(i, j + 3, k - 2, 4))return;
		if (clearBlock(i + 1, j + 3, k - 2, 4))return;
		if (clearBlock(i + 2, j + 3, k - 2, 4))return;
		if (clearBlock(i, j + 3, k - 3, 4))return;
		if (clearBlock(i + 1, j + 3, k - 3, 4))return;
		if (clearBlock(i + 2, j + 3, k - 3, 4))return;
		if (clearBlock(i + 3, j + 3, k, 4))return;
		if (clearBlock(i + 3, j + 3, k - 1, 4))return;
		if (clearBlock(i + 3, j + 3, k - 2, 4))return;
		if (clearBlock(i + 3, j + 3, k - 3, 4))return;
		break;
	case 5:
		if (clearBlock(i + 1, j, k, 5))return;
		if (clearBlock(i, j, k + 1, 5))return;
		if (clearBlock(i + 1, j - 1, k, 5))return;
		if (clearBlock(i, j - 1, k + 1, 5))return;
		if (clearBlock(i + 1, j, k + 1, 5))return;
		if (clearBlock(i + 1, j - 1, k + 1, 5))return;
		if (clearBlock(i + 2, j, k, 5))return;
		if (clearBlock(i + 2, j, k + 1, 5))return;
		if (clearBlock(i, j, k + 2, 5))return;
		if (clearBlock(i + 1, j, k + 2, 5))return;
		if (clearBlock(i + 2, j, k + 2, 5))return;
		if (clearBlock(i + 2, j - 1, k, 5))return;
		if (clearBlock(i + 2, j - 1, k + 1, 5))return;
		if (clearBlock(i, j - 1, k + 2, 5))return;
		if (clearBlock(i + 1, j - 1, k + 2, 5))return;
		if (clearBlock(i + 2, j - 1, k + 2, 5))return;
		if (clearBlock(i, j - 2, k, 5))return;
		if (clearBlock(i + 1, j - 2, k, 5))return;
		if (clearBlock(i, j - 2, k + 1, 5))return;
		if (clearBlock(i + 1, j - 2, k + 1, 5))return;
		if (clearBlock(i + 2, j - 2, k, 5))return;
		if (clearBlock(i + 2, j - 2, k + 1, 5))return;
		if (clearBlock(i, j - 2, k + 2, 5))return;
		if (clearBlock(i + 1, j - 2, k + 2, 5))return;
		if (clearBlock(i + 2, j - 2, k + 2, 5))return;
		if (clearBlock(i + 3, j, k, 5))return;
		if (clearBlock(i + 3, j, k + 1, 5))return;
		if (clearBlock(i + 3, j, k + 2, 5))return;
		if (clearBlock(i, j, k + 3, 5))return;
		if (clearBlock(i + 1, j, k + 3, 5))return;
		if (clearBlock(i + 2, j, k + 3, 5))return;
		if (clearBlock(i + 3, j - 1, k, 5))return;
		if (clearBlock(i + 3, j - 1, k + 1, 5))return;
		if (clearBlock(i + 3, j - 1, k + 2, 5))return;
		if (clearBlock(i, j - 1, k + 3, 5))return;
		if (clearBlock(i + 1, j - 1, k + 3, 5))return;
		if (clearBlock(i + 2, j - 1, k + 3, 5))return;
		if (clearBlock(i + 3, j - 2, k, 5))return;
		if (clearBlock(i + 3, j - 2, k + 1, 5))return;
		if (clearBlock(i + 3, j - 2, k + 2, 5))return;
		if (clearBlock(i, j - 2, k + 3, 5))return;
		if (clearBlock(i + 1, j - 2, k + 3, 5))return;
		if (clearBlock(i + 2, j - 2, k + 3, 5))return;
		if (clearBlock(i + 3, j, k + 3, 5))return;
		if (clearBlock(i + 3, j - 1, k + 3, 5))return;
		if (clearBlock(i + 3, j - 2, k + 3, 5))return;
		if (clearBlock(i, j - 3, k, 5))return;
		if (clearBlock(i + 1, j - 3, k, 5))return;
		if (clearBlock(i, j - 3, k + 1, 5))return;
		if (clearBlock(i + 1, j - 3, k + 1, 5))return;
		if (clearBlock(i + 2, j - 3, k, 5))return;
		if (clearBlock(i + 2, j - 3, k + 1, 5))return;
		if (clearBlock(i, j - 3, k + 2, 5))return;
		if (clearBlock(i + 1, j - 3, k + 2, 5))return;
		if (clearBlock(i + 2, j - 3, k + 2, 5))return;
		if (clearBlock(i, j - 3, k + 3, 5))return;
		if (clearBlock(i + 1, j - 3, k + 3, 5))return;
		if (clearBlock(i + 2, j - 3, k + 3, 5))return;
		if (clearBlock(i + 3, j - 3, k, 5))return;
		if (clearBlock(i + 3, j - 3, k + 1, 5))return;
		if (clearBlock(i + 3, j - 3, k + 2, 5))return;
		if (clearBlock(i + 3, j - 3, k + 3, 5))return;
		break;
	case 6:
		if (clearBlock(i - 1, j, k, 6))return;
		if (clearBlock(i, j, k + 1, 6))return;
		if (clearBlock(i - 1, j - 1, k, 6))return;
		if (clearBlock(i, j - 1, k + 1, 6))return;
		if (clearBlock(i - 1, j, k + 1, 6))return;
		if (clearBlock(i - 1, j - 1, k + 1, 6))return;
		if (clearBlock(i - 2, j, k, 6))return;
		if (clearBlock(i - 2, j, k + 1, 6))return;
		if (clearBlock(i, j, k + 2, 6))return;
		if (clearBlock(i - 1, j, k + 2, 6))return;
		if (clearBlock(i - 2, j, k + 2, 6))return;
		if (clearBlock(i - 2, j - 1, k, 6))return;
		if (clearBlock(i - 2, j - 1, k + 1, 6))return;
		if (clearBlock(i, j - 1, k + 2, 6))return;
		if (clearBlock(i - 1, j - 1, k + 2, 6))return;
		if (clearBlock(i - 2, j - 1, k + 2, 6))return;
		if (clearBlock(i, j - 2, k, 6))return;
		if (clearBlock(i - 1, j - 2, k, 6))return;
		if (clearBlock(i, j - 2, k + 1, 6))return;
		if (clearBlock(i - 1, j - 2, k + 1, 6))return;
		if (clearBlock(i - 2, j - 2, k, 6))return;
		if (clearBlock(i - 2, j - 2, k + 1, 6))return;
		if (clearBlock(i, j - 2, k + 2, 6))return;
		if (clearBlock(i - 1, j - 2, k + 2, 6))return;
		if (clearBlock(i - 2, j - 2, k + 2, 6))return;
		if (clearBlock(i - 3, j, k, 6))return;
		if (clearBlock(i - 3, j, k + 1, 6))return;
		if (clearBlock(i - 3, j, k + 2, 6))return;
		if (clearBlock(i, j, k + 3, 6))return;
		if (clearBlock(i - 1, j, k + 3, 6))return;
		if (clearBlock(i - 2, j, k + 3, 6))return;
		if (clearBlock(i - 3, j - 1, k, 6))return;
		if (clearBlock(i - 3, j - 1, k + 1, 6))return;
		if (clearBlock(i - 3, j - 1, k + 2, 6))return;
		if (clearBlock(i, j - 1, k + 3, 6))return;
		if (clearBlock(i - 1, j - 1, k + 3, 6))return;
		if (clearBlock(i - 2, j - 1, k + 3, 6))return;
		if (clearBlock(i - 3, j - 2, k, 6))return;
		if (clearBlock(i - 3, j - 2, k + 1, 6))return;
		if (clearBlock(i - 3, j - 2, k + 2, 6))return;
		if (clearBlock(i, j - 2, k + 3, 6))return;
		if (clearBlock(i - 1, j - 2, k + 3, 6))return;
		if (clearBlock(i - 2, j - 2, k + 3, 6))return;
		if (clearBlock(i - 3, j, k + 3, 6))return;
		if (clearBlock(i - 3, j - 1, k + 3, 6))return;
		if (clearBlock(i - 3, j - 2, k + 3, 6))return;
		if (clearBlock(i, j - 3, k, 6))return;
		if (clearBlock(i - 1, j - 3, k, 6))return;
		if (clearBlock(i, j - 3, k + 1, 6))return;
		if (clearBlock(i - 1, j - 3, k + 1, 6))return;
		if (clearBlock(i - 2, j - 3, k, 6))return;
		if (clearBlock(i - 2, j - 3, k + 1, 6))return;
		if (clearBlock(i, j - 3, k + 2, 6))return;
		if (clearBlock(i - 1, j - 3, k + 2, 6))return;
		if (clearBlock(i - 2, j - 3, k + 2, 6))return;
		if (clearBlock(i, j - 3, k + 3, 6))return;
		if (clearBlock(i - 1, j - 3, k + 3, 6))return;
		if (clearBlock(i - 2, j - 3, k + 3, 6))return;
		if (clearBlock(i - 3, j - 3, k, 6))return;
		if (clearBlock(i - 3, j - 3, k + 1, 6))return;
		if (clearBlock(i - 3, j - 3, k + 2, 6))return;
		if (clearBlock(i - 3, j - 3, k + 3, 6))return;
		break;
	case 7:
		if (clearBlock(i - 1, j, k, 7))return;
		if (clearBlock(i, j, k - 1, 7))return;
		if (clearBlock(i - 1, j - 1, k, 7))return;
		if (clearBlock(i, j - 1, k - 1, 7))return;
		if (clearBlock(i - 1, j, k - 1, 7))return;
		if (clearBlock(i - 1, j - 1, k - 1, 7))return;
		if (clearBlock(i - 2, j, k, 7))return;
		if (clearBlock(i - 2, j, k - 1, 7))return;
		if (clearBlock(i, j, k - 2, 7))return;
		if (clearBlock(i - 1, j, k - 2, 7))return;
		if (clearBlock(i - 2, j, k - 2, 7))return;
		if (clearBlock(i - 2, j - 1, k, 7))return;
		if (clearBlock(i - 2, j - 1, k - 1, 7))return;
		if (clearBlock(i, j - 1, k - 2, 7))return;
		if (clearBlock(i - 1, j - 1, k - 2, 7))return;
		if (clearBlock(i - 2, j - 1, k - 2, 7))return;
		if (clearBlock(i, j - 2, k, 7))return;
		if (clearBlock(i - 1, j - 2, k, 7))return;
		if (clearBlock(i, j - 2, k - 1, 7))return;
		if (clearBlock(i - 1, j - 2, k - 1, 7))return;
		if (clearBlock(i - 2, j - 2, k, 7))return;
		if (clearBlock(i - 2, j - 2, k - 1, 7))return;
		if (clearBlock(i, j - 2, k - 2, 7))return;
		if (clearBlock(i - 1, j - 2, k - 2, 7))return;
		if (clearBlock(i - 2, j - 2, k - 2, 7))return;
		if (clearBlock(i - 3, j, k, 7))return;
		if (clearBlock(i - 3, j, k - 1, 7))return;
		if (clearBlock(i - 3, j, k - 2, 7))return;
		if (clearBlock(i, j, k - 3, 7))return;
		if (clearBlock(i - 1, j, k - 3, 7))return;
		if (clearBlock(i - 2, j, k - 3, 7))return;
		if (clearBlock(i - 3, j - 1, k, 7))return;
		if (clearBlock(i - 3, j - 1, k - 1, 7))return;
		if (clearBlock(i - 3, j - 1, k - 2, 7))return;
		if (clearBlock(i, j - 1, k - 3, 7))return;
		if (clearBlock(i - 1, j - 1, k - 3, 7))return;
		if (clearBlock(i - 2, j - 1, k - 3, 7))return;
		if (clearBlock(i - 3, j - 2, k, 7))return;
		if (clearBlock(i - 3, j - 2, k - 1, 7))return;
		if (clearBlock(i - 3, j - 2, k - 2, 7))return;
		if (clearBlock(i, j - 2, k - 3, 7))return;
		if (clearBlock(i - 1, j - 2, k - 3, 7))return;
		if (clearBlock(i - 2, j - 2, k - 3, 7))return;
		if (clearBlock(i - 3, j, k - 3, 7))return;
		if (clearBlock(i - 3, j - 1, k - 3, 7))return;
		if (clearBlock(i - 3, j - 2, k - 3, 7))return;
		if (clearBlock(i, j - 3, k, 7))return;
		if (clearBlock(i - 1, j - 3, k, 7))return;
		if (clearBlock(i, j - 3, k - 1, 7))return;
		if (clearBlock(i - 1, j - 3, k - 1, 7))return;
		if (clearBlock(i - 2, j - 3, k, 7))return;
		if (clearBlock(i - 2, j - 3, k - 1, 7))return;
		if (clearBlock(i, j - 3, k - 2, 7))return;
		if (clearBlock(i - 1, j - 3, k - 2, 7))return;
		if (clearBlock(i - 2, j - 3, k - 2, 7))return;
		if (clearBlock(i, j - 3, k - 3, 7))return;
		if (clearBlock(i - 1, j - 3, k - 3, 7))return;
		if (clearBlock(i - 2, j - 3, k - 3, 7))return;
		if (clearBlock(i - 3, j - 3, k, 7))return;
		if (clearBlock(i - 3, j - 3, k - 1, 7))return;
		if (clearBlock(i - 3, j - 3, k - 2, 7))return;
		if (clearBlock(i - 3, j - 3, k - 3, 7))return;
		break;
	case 8:
		if (clearBlock(i + 1, j, k, 8))return;
		if (clearBlock(i, j, k - 1, 8))return;
		if (clearBlock(i + 1, j - 1, k, 8))return;
		if (clearBlock(i, j - 1, k - 1, 8))return;
		if (clearBlock(i + 1, j, k - 1, 8))return;
		if (clearBlock(i + 1, j - 1, k - 1, 8))return;
		if (clearBlock(i + 2, j, k, 8))return;
		if (clearBlock(i + 2, j, k - 1, 8))return;
		if (clearBlock(i, j, k - 2, 8))return;
		if (clearBlock(i + 1, j, k - 2, 8))return;
		if (clearBlock(i + 2, j, k - 2, 8))return;
		if (clearBlock(i + 2, j - 1, k, 8))return;
		if (clearBlock(i + 2, j - 1, k - 1, 8))return;
		if (clearBlock(i, j - 1, k - 2, 8))return;
		if (clearBlock(i + 1, j - 1, k - 2, 8))return;
		if (clearBlock(i + 2, j - 1, k - 2, 8))return;
		if (clearBlock(i, j - 2, k, 8))return;
		if (clearBlock(i + 1, j - 2, k, 8))return;
		if (clearBlock(i, j - 2, k - 1, 8))return;
		if (clearBlock(i + 1, j - 2, k - 1, 8))return;
		if (clearBlock(i + 2, j - 2, k, 8))return;
		if (clearBlock(i + 2, j - 2, k - 1, 8))return;
		if (clearBlock(i, j - 2, k - 2, 8))return;
		if (clearBlock(i + 1, j - 2, k - 2, 8))return;
		if (clearBlock(i + 2, j - 2, k - 2, 8))return;
		if (clearBlock(i + 3, j, k, 8))return;
		if (clearBlock(i + 3, j, k - 1, 8))return;
		if (clearBlock(i + 3, j, k - 2, 8))return;
		if (clearBlock(i, j, k - 3, 8))return;
		if (clearBlock(i + 1, j, k - 3, 8))return;
		if (clearBlock(i + 2, j, k - 3, 8))return;
		if (clearBlock(i + 3, j - 1, k, 8))return;
		if (clearBlock(i + 3, j - 1, k - 1, 8))return;
		if (clearBlock(i + 3, j - 1, k - 2, 8))return;
		if (clearBlock(i, j - 1, k - 3, 8))return;
		if (clearBlock(i + 1, j - 1, k - 3, 8))return;
		if (clearBlock(i + 2, j - 1, k - 3, 8))return;
		if (clearBlock(i + 3, j - 2, k, 8))return;
		if (clearBlock(i + 3, j - 2, k - 1, 8))return;
		if (clearBlock(i + 3, j - 2, k - 2, 8))return;
		if (clearBlock(i, j - 2, k - 3, 8))return;
		if (clearBlock(i + 1, j - 2, k - 3, 8))return;
		if (clearBlock(i + 2, j - 2, k - 3, 8))return;
		if (clearBlock(i + 3, j, k - 3, 8))return;
		if (clearBlock(i + 3, j - 1, k - 3, 8))return;
		if (clearBlock(i + 3, j - 2, k - 3, 8))return;
		if (clearBlock(i, j - 3, k, 8))return;
		if (clearBlock(i + 1, j - 3, k, 8))return;
		if (clearBlock(i, j - 3, k - 1, 8))return;
		if (clearBlock(i + 1, j - 3, k - 1, 8))return;
		if (clearBlock(i + 2, j - 3, k, 8))return;
		if (clearBlock(i + 2, j - 3, k - 1, 8))return;
		if (clearBlock(i, j - 3, k - 2, 8))return;
		if (clearBlock(i + 1, j - 3, k - 2, 8))return;
		if (clearBlock(i + 2, j - 3, k - 2, 8))return;
		if (clearBlock(i, j - 3, k - 3, 8))return;
		if (clearBlock(i + 1, j - 3, k - 3, 8))return;
		if (clearBlock(i + 2, j - 3, k - 3, 8))return;
		if (clearBlock(i + 3, j - 3, k, 8))return;
		if (clearBlock(i + 3, j - 3, k - 1, 8))return;
		if (clearBlock(i + 3, j - 3, k - 2, 8))return;
		if (clearBlock(i + 3, j - 3, k - 3, 8))return;
		break;
	}
}
bool creatBlock(int i, int j, int k, int type, int o) {
	enum directList dir;
	threeVect tmp = playerEye.getPos();
	if (wholeWorld[i][j][k] == NULL)return FALSE;
	if (dir = wholeWorld[i][j][k]->isChosen(o)) {
		switch (dir) {
		case UP:
			if ((tmp.y - EYEHEIGHT) / BLOCKSIZE < j + 2 && (int)tmp.x / BLOCKSIZE == i && (int)tmp.z / BLOCKSIZE == k)return TRUE;
			wholeWorld[i][j + 1][k] = new block(i, j + 1, k);
			wholeWorld[i][j + 1][k]->buildBlock(1, gunArry[BLOCK]->RGB[0], gunArry[BLOCK]->RGB[1], gunArry[BLOCK]->RGB[2]);
			if (j + 1 > fileGV.explored.b2)fileGV.explored.b2 = j + 1;
			return TRUE;
		case DOWN:
			if (tmp.y / BLOCKSIZE > j - 1 && (int)tmp.x / BLOCKSIZE == i && (int)tmp.z / BLOCKSIZE == k)return TRUE;
			wholeWorld[i][j - 1][k] = new block(i, j - 1, k);
			wholeWorld[i][j - 1][k]->buildBlock(1, gunArry[BLOCK]->RGB[0], gunArry[BLOCK]->RGB[1], gunArry[BLOCK]->RGB[2]);
			if (j - 1 < fileGV.explored.b1)fileGV.explored.b1 = j - 1;
			return TRUE;
		case LEFT:
			if (tmp.x / BLOCKSIZE > i - 1 && ((int)tmp.y / BLOCKSIZE == j + 1 || (int)tmp.y / BLOCKSIZE == j) && (int)tmp.z / BLOCKSIZE == k)return TRUE;
			wholeWorld[i - 1][j][k] = new block(i - 1, j, k);
			wholeWorld[i - 1][j][k]->buildBlock(1, gunArry[BLOCK]->RGB[0], gunArry[BLOCK]->RGB[1], gunArry[BLOCK]->RGB[2]);
			if (i - 1 < fileGV.explored.a1)fileGV.explored.a1 = i - 1;
			return TRUE;
		case RIGHT:
			if (tmp.x / BLOCKSIZE < i + 2 && ((int)tmp.y / BLOCKSIZE == j + 1 || (int)tmp.y / BLOCKSIZE == j) && (int)tmp.z / BLOCKSIZE == k)return TRUE;
			wholeWorld[i + 1][j][k] = new block(i + 1, j, k);
			wholeWorld[i + 1][j][k]->buildBlock(1, gunArry[BLOCK]->RGB[0], gunArry[BLOCK]->RGB[1], gunArry[BLOCK]->RGB[2]);
			if (i + 1 > fileGV.explored.a2)fileGV.explored.a2 = i + 1;
			return TRUE;
		case FRONT:
			if (tmp.z / BLOCKSIZE < k + 2 && ((int)tmp.y / BLOCKSIZE == j + 1 || (int)tmp.y / BLOCKSIZE == j) && (int)tmp.x / BLOCKSIZE == i)return TRUE;
			wholeWorld[i][j][k + 1] = new block(i, j, k + 1);
			wholeWorld[i][j][k + 1]->buildBlock(1, gunArry[BLOCK]->RGB[0], gunArry[BLOCK]->RGB[1], gunArry[BLOCK]->RGB[2]);
			if (k + 1 > fileGV.explored.c2)fileGV.explored.c2 = k + 1;
			return TRUE;
		case BACK:
			if (tmp.z / BLOCKSIZE > k - 1 && ((int)tmp.y / BLOCKSIZE == j + 1 || (int)tmp.y / BLOCKSIZE == j) && (int)tmp.x / BLOCKSIZE == i)return TRUE;
			wholeWorld[i][j][k - 1] = new block(i, j, k - 1);
			wholeWorld[i][j][k - 1]->buildBlock(1, gunArry[BLOCK]->RGB[0], gunArry[BLOCK]->RGB[1], gunArry[BLOCK]->RGB[2]);
			if (k - 1 < fileGV.explored.c1)fileGV.explored.c1 = k - 1;
			return TRUE;
		}
	}
	return FALSE;
}
bool clearBlock(int i, int j, int k, int o) {
	enum directList dir;
	threeVect tmp = playerEye.getPos();
	if (wholeWorld[i][j][k] == NULL)return FALSE;
	if (dir = wholeWorld[i][j][k]->isChosen(o)) {
		delete wholeWorld[i][j][k];
		wholeWorld[i][j][k] = NULL;
		if (i < fileGV.explored.a1)fileGV.explored.a1 = i;
		if (i > fileGV.explored.a2)fileGV.explored.a2 = i;
		if (j < fileGV.explored.b1)fileGV.explored.b1 = j;
		if (j > fileGV.explored.b2)fileGV.explored.b2 = j;
		if (k < fileGV.explored.c1)fileGV.explored.c1 = k;
		if (k > fileGV.explored.c2)fileGV.explored.c2 = k;
		return TRUE;
	}
	return FALSE;
}

void changeHand() {
	threeVect tmp = playerEye.getAt();
	if (tmp.y >= 0) {
		if (tmp.z >= 0) {
			if (tmp.x >= 0)typeOctant(1);
			else typeOctant(2);
		}
		else {
			if (tmp.x >= 0)typeOctant(4);
			else typeOctant(3);
		}
	}
	else {
		if (tmp.z >= 0) {
			if (tmp.x >= 0)typeOctant(5);
			else typeOctant(6);
		}
		else {
			if (tmp.x >= 0)typeOctant(8);
			else typeOctant(7);
		}
	}
}
void typeOctant(int octant) {
	threeVect tmp = playerEye.getPos();
	int i = tmp.x / BLOCKSIZE;
	int j = tmp.y / BLOCKSIZE;
	int k = tmp.z / BLOCKSIZE;
	switch (octant) {
	case 1:
		if (typeHand(i + 1, j, k, 1))return;
		if (typeHand(i, j, k + 1, 1))return;
		if (typeHand(i, j + 1, k, 1))return;
		if (typeHand(i + 1, j + 1, k, 1))return;
		if (typeHand(i, j + 1, k + 1, 1))return;
		if (typeHand(i + 1, j, k + 1, 1))return;
		if (typeHand(i + 1, j + 1, k + 1, 1))return;
		if (typeHand(i + 2, j, k, 1))return;
		if (typeHand(i + 2, j, k + 1, 1))return;
		if (typeHand(i, j, k + 2, 1))return;
		if (typeHand(i + 1, j, k + 2, 1))return;
		if (typeHand(i + 2, j, k + 2, 1))return;
		if (typeHand(i + 2, j + 1, k, 1))return;
		if (typeHand(i + 2, j + 1, k + 1, 1))return;
		if (typeHand(i, j + 1, k + 2, 1))return;
		if (typeHand(i + 1, j + 1, k + 2, 1))return;
		if (typeHand(i + 2, j + 1, k + 2, 1))return;
		if (typeHand(i, j + 2, k, 1))return;
		if (typeHand(i + 1, j + 2, k, 1))return;
		if (typeHand(i, j + 2, k + 1, 1))return;
		if (typeHand(i + 1, j + 2, k + 1, 1))return;
		if (typeHand(i + 2, j + 2, k, 1))return;
		if (typeHand(i + 2, j + 2, k + 1, 1))return;
		if (typeHand(i, j + 2, k + 2, 1))return;
		if (typeHand(i + 1, j + 2, k + 2, 1))return;
		if (typeHand(i + 2, j + 2, k + 2, 1))return;
		if (typeHand(i + 3, j, k, 1))return;
		if (typeHand(i + 3, j, k + 1, 1))return;
		if (typeHand(i + 3, j, k + 2, 1))return;
		if (typeHand(i, j, k + 3, 1))return;
		if (typeHand(i + 1, j, k + 3, 1))return;
		if (typeHand(i + 2, j, k + 3, 1))return;
		if (typeHand(i + 3, j + 1, k, 1))return;
		if (typeHand(i + 3, j + 1, k + 1, 1))return;
		if (typeHand(i + 3, j + 1, k + 2, 1))return;
		if (typeHand(i, j + 1, k + 3, 1))return;
		if (typeHand(i + 1, j + 1, k + 3, 1))return;
		if (typeHand(i + 2, j + 1, k + 3, 1))return;
		if (typeHand(i + 3, j + 2, k, 1))return;
		if (typeHand(i + 3, j + 2, k + 1, 1))return;
		if (typeHand(i + 3, j + 2, k + 2, 1))return;
		if (typeHand(i, j + 2, k + 3, 1))return;
		if (typeHand(i + 1, j + 2, k + 3, 1))return;
		if (typeHand(i + 2, j + 2, k + 3, 1))return;
		if (typeHand(i + 3, j, k + 3, 1))return;
		if (typeHand(i + 3, j + 1, k + 3, 1))return;
		if (typeHand(i + 3, j + 2, k + 3, 1))return;
		if (typeHand(i, j + 3, k, 1))return;
		if (typeHand(i + 1, j + 3, k, 1))return;
		if (typeHand(i, j + 3, k + 1, 1))return;
		if (typeHand(i + 1, j + 3, k + 1, 1))return;
		if (typeHand(i + 2, j + 3, k, 1))return;
		if (typeHand(i + 2, j + 3, k + 1, 1))return;
		if (typeHand(i, j + 3, k + 2, 1))return;
		if (typeHand(i + 1, j + 3, k + 2, 1))return;
		if (typeHand(i + 2, j + 3, k + 2, 1))return;
		if (typeHand(i, j + 3, k + 3, 1))return;
		if (typeHand(i + 1, j + 3, k + 3, 1))return;
		if (typeHand(i + 2, j + 3, k + 3, 1))return;
		if (typeHand(i + 3, j + 3, k, 1))return;
		if (typeHand(i + 3, j + 3, k + 1, 1))return;
		if (typeHand(i + 3, j + 3, k + 2, 1))return;
		if (typeHand(i + 3, j + 3, k + 3, 1))return;
		break;
	case 2:
		if (typeHand(i - 1, j, k, 2))return;
		if (typeHand(i, j, k + 1, 2))return;
		if (typeHand(i, j + 1, k, 2))return;
		if (typeHand(i - 1, j + 1, k, 2))return;
		if (typeHand(i, j + 1, k + 1, 2))return;
		if (typeHand(i - 1, j, k + 1, 2))return;
		if (typeHand(i - 1, j + 1, k + 1, 2))return;
		if (typeHand(i - 2, j, k, 2))return;
		if (typeHand(i - 2, j, k + 1, 2))return;
		if (typeHand(i, j, k + 2, 2))return;
		if (typeHand(i - 1, j, k + 2, 2))return;
		if (typeHand(i - 2, j, k + 2, 2))return;
		if (typeHand(i - 2, j + 1, k, 2))return;
		if (typeHand(i - 2, j + 1, k + 1, 2))return;
		if (typeHand(i, j + 1, k + 2, 2))return;
		if (typeHand(i - 1, j + 1, k + 2, 2))return;
		if (typeHand(i - 2, j + 1, k + 2, 2))return;
		if (typeHand(i, j + 2, k, 2))return;
		if (typeHand(i - 1, j + 2, k, 2))return;
		if (typeHand(i, j + 2, k + 1, 2))return;
		if (typeHand(i - 1, j + 2, k + 1, 2))return;
		if (typeHand(i - 2, j + 2, k, 2))return;
		if (typeHand(i - 2, j + 2, k + 1, 2))return;
		if (typeHand(i, j + 2, k + 2, 2))return;
		if (typeHand(i - 1, j + 2, k + 2, 2))return;
		if (typeHand(i - 2, j + 2, k + 2, 2))return;
		if (typeHand(i - 3, j, k, 2))return;
		if (typeHand(i - 3, j, k + 1, 2))return;
		if (typeHand(i - 3, j, k + 2, 2))return;
		if (typeHand(i, j, k + 3, 2))return;
		if (typeHand(i - 1, j, k + 3, 2))return;
		if (typeHand(i - 2, j, k + 3, 2))return;
		if (typeHand(i - 3, j + 1, k, 2))return;
		if (typeHand(i - 3, j + 1, k + 1, 2))return;
		if (typeHand(i - 3, j + 1, k + 2, 2))return;
		if (typeHand(i, j + 1, k + 3, 2))return;
		if (typeHand(i - 1, j + 1, k + 3, 2))return;
		if (typeHand(i - 2, j + 1, k + 3, 2))return;
		if (typeHand(i - 3, j + 2, k, 2))return;
		if (typeHand(i - 3, j + 2, k + 1, 2))return;
		if (typeHand(i - 3, j + 2, k + 2, 2))return;
		if (typeHand(i, j + 2, k + 3, 2))return;
		if (typeHand(i - 1, j + 2, k + 3, 2))return;
		if (typeHand(i - 2, j + 2, k + 3, 2))return;
		if (typeHand(i - 3, j, k + 3, 2))return;
		if (typeHand(i - 3, j + 1, k + 3, 2))return;
		if (typeHand(i - 3, j + 2, k + 3, 2))return;
		if (typeHand(i, j + 3, k, 2))return;
		if (typeHand(i - 1, j + 3, k, 2))return;
		if (typeHand(i, j + 3, k + 1, 2))return;
		if (typeHand(i - 1, j + 3, k + 1, 2))return;
		if (typeHand(i - 2, j + 3, k, 2))return;
		if (typeHand(i - 2, j + 3, k + 1, 2))return;
		if (typeHand(i, j - 3, k + 2, 2))return;
		if (typeHand(i - 1, j + 3, k + 2, 2))return;
		if (typeHand(i - 2, j + 3, k + 2, 2))return;
		if (typeHand(i, j + 3, k + 3, 2))return;
		if (typeHand(i - 1, j + 3, k + 3, 2))return;
		if (typeHand(i - 2, j + 3, k + 3, 2))return;
		if (typeHand(i - 3, j + 3, k, 2))return;
		if (typeHand(i - 3, j + 3, k + 1, 2))return;
		if (typeHand(i - 3, j + 3, k + 2, 2))return;
		if (typeHand(i - 3, j + 3, k + 3, 2))return;
		break;
	case 3:
		if (typeHand(i - 1, j, k, 3))return;
		if (typeHand(i, j, k - 1, 3))return;
		if (typeHand(i, j + 1, k, 3))return;
		if (typeHand(i - 1, j + 1, k, 3))return;
		if (typeHand(i, j + 1, k - 1, 3))return;
		if (typeHand(i - 1, j, k - 1, 3))return;
		if (typeHand(i - 1, j + 1, k - 1, 3))return;
		if (typeHand(i - 2, j, k, 3))return;
		if (typeHand(i - 2, j, k - 1, 3))return;
		if (typeHand(i, j, k - 2, 3))return;
		if (typeHand(i - 1, j, k - 2, 3))return;
		if (typeHand(i - 2, j, k - 2, 3))return;
		if (typeHand(i - 2, j + 1, k, 3))return;
		if (typeHand(i - 2, j + 1, k - 1, 3))return;
		if (typeHand(i, j + 1, k - 2, 3))return;
		if (typeHand(i - 1, j + 1, k - 2, 3))return;
		if (typeHand(i - 2, j + 1, k - 2, 3))return;
		if (typeHand(i, j + 2, k, 3))return;
		if (typeHand(i - 1, j + 2, k, 3))return;
		if (typeHand(i, j + 2, k - 1, 3))return;
		if (typeHand(i - 1, j + 2, k - 1, 3))return;
		if (typeHand(i - 2, j + 2, k, 3))return;
		if (typeHand(i - 2, j + 2, k - 1, 3))return;
		if (typeHand(i, j + 2, k - 2, 3))return;
		if (typeHand(i - 1, j + 2, k - 2, 3))return;
		if (typeHand(i - 2, j + 2, k - 2, 3))return;
		if (typeHand(i - 3, j, k, 3))return;
		if (typeHand(i - 3, j, k - 1, 3))return;
		if (typeHand(i - 3, j, k - 2, 3))return;
		if (typeHand(i, j, k - 3, 3))return;
		if (typeHand(i - 1, j, k - 3, 3))return;
		if (typeHand(i - 2, j, k - 3, 3))return;
		if (typeHand(i - 3, j + 1, k, 3))return;
		if (typeHand(i - 3, j + 1, k - 1, 3))return;
		if (typeHand(i - 3, j + 1, k - 2, 3))return;
		if (typeHand(i, j + 1, k - 3, 3))return;
		if (typeHand(i - 1, j + 1, k - 3, 3))return;
		if (typeHand(i - 2, j + 1, k - 3, 3))return;
		if (typeHand(i - 3, j + 2, k, 3))return;
		if (typeHand(i - 3, j + 2, k - 1, 3))return;
		if (typeHand(i - 3, j + 2, k - 2, 3))return;
		if (typeHand(i, j + 2, k - 3, 3))return;
		if (typeHand(i - 1, j + 2, k - 3, 3))return;
		if (typeHand(i - 2, j + 2, k - 3, 3))return;
		if (typeHand(i - 3, j, k - 3, 3))return;
		if (typeHand(i - 3, j + 1, k - 3, 3))return;
		if (typeHand(i - 3, j + 2, k - 3, 3))return;
		if (typeHand(i, j + 3, k, 3))return;
		if (typeHand(i - 1, j + 3, k, 3))return;
		if (typeHand(i, j + 3, k - 1, 3))return;
		if (typeHand(i - 1, j + 3, k - 1, 3))return;
		if (typeHand(i - 2, j + 3, k, 3))return;
		if (typeHand(i - 2, j + 3, k - 1, 3))return;
		if (typeHand(i, j + 3, k - 2, 3))return;
		if (typeHand(i - 1, j + 3, k - 2, 3))return;
		if (typeHand(i - 2, j + 3, k - 2, 3))return;
		if (typeHand(i, j + 3, k - 3, 3))return;
		if (typeHand(i - 1, j + 3, k - 3, 3))return;
		if (typeHand(i - 2, j + 3, k - 3, 3))return;
		if (typeHand(i - 3, j + 3, k, 3))return;
		if (typeHand(i - 3, j + 3, k - 1, 3))return;
		if (typeHand(i - 3, j + 3, k - 2, 3))return;
		if (typeHand(i - 3, j + 3, k - 3, 3))return;
		break;
	case 4:
		if (typeHand(i + 1, j, k, 4))return;
		if (typeHand(i, j, k - 1, 4))return;
		if (typeHand(i, j + 1, k, 4))return;
		if (typeHand(i + 1, j + 1, k, 4))return;
		if (typeHand(i, j + 1, k - 1, 4))return;
		if (typeHand(i + 1, j, k - 1, 4))return;
		if (typeHand(i + 1, j + 1, k - 1, 4))return;
		if (typeHand(i + 2, j, k, 4))return;
		if (typeHand(i + 2, j, k - 1, 4))return;
		if (typeHand(i, j, k - 2, 4))return;
		if (typeHand(i + 1, j, k - 2, 4))return;
		if (typeHand(i + 2, j, k - 2, 4))return;
		if (typeHand(i + 2, j + 1, k, 4))return;
		if (typeHand(i + 2, j + 1, k - 1, 4))return;
		if (typeHand(i, j + 1, k - 2, 4))return;
		if (typeHand(i + 1, j + 1, k - 2, 4))return;
		if (typeHand(i + 2, j + 1, k - 2, 4))return;
		if (typeHand(i, j + 2, k, 4))return;
		if (typeHand(i + 1, j + 2, k, 4))return;
		if (typeHand(i, j + 2, k - 1, 4))return;
		if (typeHand(i + 1, j + 2, k - 1, 4))return;
		if (typeHand(i + 2, j + 2, k, 4))return;
		if (typeHand(i + 2, j + 2, k - 1, 4))return;
		if (typeHand(i, j + 2, k - 2, 4))return;
		if (typeHand(i + 1, j + 2, k - 2, 4))return;
		if (typeHand(i + 2, j + 2, k - 2, 4))return;
		if (typeHand(i + 3, j, k, 4))return;
		if (typeHand(i + 3, j, k - 1, 4))return;
		if (typeHand(i + 3, j, k - 2, 4))return;
		if (typeHand(i, j, k - 3, 4))return;
		if (typeHand(i + 1, j, k - 3, 4))return;
		if (typeHand(i + 2, j, k - 3, 4))return;
		if (typeHand(i + 3, j + 1, k, 4))return;
		if (typeHand(i + 3, j + 1, k - 1, 4))return;
		if (typeHand(i + 3, j + 1, k - 2, 4))return;
		if (typeHand(i, j + 1, k - 3, 4))return;
		if (typeHand(i + 1, j + 1, k - 3, 4))return;
		if (typeHand(i + 2, j + 1, k - 3, 4))return;
		if (typeHand(i + 3, j + 2, k, 4))return;
		if (typeHand(i + 3, j + 2, k - 1, 4))return;
		if (typeHand(i + 3, j + 2, k - 2, 4))return;
		if (typeHand(i, j + 2, k - 3, 4))return;
		if (typeHand(i + 1, j + 2, k - 3, 4))return;
		if (typeHand(i + 2, j + 2, k - 3, 4))return;
		if (typeHand(i + 3, j, k - 3, 4))return;
		if (typeHand(i + 3, j + 1, k - 3, 4))return;
		if (typeHand(i + 3, j + 2, k - 3, 4))return;
		if (typeHand(i, j + 3, k, 4))return;
		if (typeHand(i + 1, j + 3, k, 4))return;
		if (typeHand(i, j + 3, k - 1, 4))return;
		if (typeHand(i + 1, j + 3, k - 1, 4))return;
		if (typeHand(i + 2, j + 3, k, 4))return;
		if (typeHand(i + 2, j + 3, k - 1, 4))return;
		if (typeHand(i, j + 3, k - 2, 4))return;
		if (typeHand(i + 1, j + 3, k - 2, 4))return;
		if (typeHand(i + 2, j + 3, k - 2, 4))return;
		if (typeHand(i, j + 3, k - 3, 4))return;
		if (typeHand(i + 1, j + 3, k - 3, 4))return;
		if (typeHand(i + 2, j + 3, k - 3, 4))return;
		if (typeHand(i + 3, j + 3, k, 4))return;
		if (typeHand(i + 3, j + 3, k - 1, 4))return;
		if (typeHand(i + 3, j + 3, k - 2, 4))return;
		if (typeHand(i + 3, j + 3, k - 3, 4))return;
		break;
	case 5:
		if (typeHand(i + 1, j, k, 5))return;
		if (typeHand(i, j, k + 1, 5))return;
		if (typeHand(i + 1, j - 1, k, 5))return;
		if (typeHand(i, j - 1, k + 1, 5))return;
		if (typeHand(i + 1, j, k + 1, 5))return;
		if (typeHand(i + 1, j - 1, k + 1, 5))return;
		if (typeHand(i + 2, j, k, 5))return;
		if (typeHand(i + 2, j, k + 1, 5))return;
		if (typeHand(i, j, k + 2, 5))return;
		if (typeHand(i + 1, j, k + 2, 5))return;
		if (typeHand(i + 2, j, k + 2, 5))return;
		if (typeHand(i + 2, j - 1, k, 5))return;
		if (typeHand(i + 2, j - 1, k + 1, 5))return;
		if (typeHand(i, j - 1, k + 2, 5))return;
		if (typeHand(i + 1, j - 1, k + 2, 5))return;
		if (typeHand(i + 2, j - 1, k + 2, 5))return;
		if (typeHand(i, j - 2, k, 5))return;
		if (typeHand(i + 1, j - 2, k, 5))return;
		if (typeHand(i, j - 2, k + 1, 5))return;
		if (typeHand(i + 1, j - 2, k + 1, 5))return;
		if (typeHand(i + 2, j - 2, k, 5))return;
		if (typeHand(i + 2, j - 2, k + 1, 5))return;
		if (typeHand(i, j - 2, k + 2, 5))return;
		if (typeHand(i + 1, j - 2, k + 2, 5))return;
		if (typeHand(i + 2, j - 2, k + 2, 5))return;
		if (typeHand(i + 3, j, k, 5))return;
		if (typeHand(i + 3, j, k + 1, 5))return;
		if (typeHand(i + 3, j, k + 2, 5))return;
		if (typeHand(i, j, k + 3, 5))return;
		if (typeHand(i + 1, j, k + 3, 5))return;
		if (typeHand(i + 2, j, k + 3, 5))return;
		if (typeHand(i + 3, j - 1, k, 5))return;
		if (typeHand(i + 3, j - 1, k + 1, 5))return;
		if (typeHand(i + 3, j - 1, k + 2, 5))return;
		if (typeHand(i, j - 1, k + 3, 5))return;
		if (typeHand(i + 1, j - 1, k + 3, 5))return;
		if (typeHand(i + 2, j - 1, k + 3, 5))return;
		if (typeHand(i + 3, j - 2, k, 5))return;
		if (typeHand(i + 3, j - 2, k + 1, 5))return;
		if (typeHand(i + 3, j - 2, k + 2, 5))return;
		if (typeHand(i, j - 2, k + 3, 5))return;
		if (typeHand(i + 1, j - 2, k + 3, 5))return;
		if (typeHand(i + 2, j - 2, k + 3, 5))return;
		if (typeHand(i + 3, j, k + 3, 5))return;
		if (typeHand(i + 3, j - 1, k + 3, 5))return;
		if (typeHand(i + 3, j - 2, k + 3, 5))return;
		if (typeHand(i, j - 3, k, 5))return;
		if (typeHand(i + 1, j - 3, k, 5))return;
		if (typeHand(i, j - 3, k + 1, 5))return;
		if (typeHand(i + 1, j - 3, k + 1, 5))return;
		if (typeHand(i + 2, j - 3, k, 5))return;
		if (typeHand(i + 2, j - 3, k + 1, 5))return;
		if (typeHand(i, j - 3, k + 2, 5))return;
		if (typeHand(i + 1, j - 3, k + 2, 5))return;
		if (typeHand(i + 2, j - 3, k + 2, 5))return;
		if (typeHand(i, j - 3, k + 3, 5))return;
		if (typeHand(i + 1, j - 3, k + 3, 5))return;
		if (typeHand(i + 2, j - 3, k + 3, 5))return;
		if (typeHand(i + 3, j - 3, k, 5))return;
		if (typeHand(i + 3, j - 3, k + 1, 5))return;
		if (typeHand(i + 3, j - 3, k + 2, 5))return;
		if (typeHand(i + 3, j - 3, k + 3, 5))return;
		break;
	case 6:
		if (typeHand(i - 1, j, k, 6))return;
		if (typeHand(i, j, k + 1, 6))return;
		if (typeHand(i - 1, j - 1, k, 6))return;
		if (typeHand(i, j - 1, k + 1, 6))return;
		if (typeHand(i - 1, j, k + 1, 6))return;
		if (typeHand(i - 1, j - 1, k + 1, 6))return;
		if (typeHand(i - 2, j, k, 6))return;
		if (typeHand(i - 2, j, k + 1, 6))return;
		if (typeHand(i, j, k + 2, 6))return;
		if (typeHand(i - 1, j, k + 2, 6))return;
		if (typeHand(i - 2, j, k + 2, 6))return;
		if (typeHand(i - 2, j - 1, k, 6))return;
		if (typeHand(i - 2, j - 1, k + 1, 6))return;
		if (typeHand(i, j - 1, k + 2, 6))return;
		if (typeHand(i - 1, j - 1, k + 2, 6))return;
		if (typeHand(i - 2, j - 1, k + 2, 6))return;
		if (typeHand(i, j - 2, k, 6))return;
		if (typeHand(i - 1, j - 2, k, 6))return;
		if (typeHand(i, j - 2, k + 1, 6))return;
		if (typeHand(i - 1, j - 2, k + 1, 6))return;
		if (typeHand(i - 2, j - 2, k, 6))return;
		if (typeHand(i - 2, j - 2, k + 1, 6))return;
		if (typeHand(i, j - 2, k + 2, 6))return;
		if (typeHand(i - 1, j - 2, k + 2, 6))return;
		if (typeHand(i - 2, j - 2, k + 2, 6))return;
		if (typeHand(i - 3, j, k, 6))return;
		if (typeHand(i - 3, j, k + 1, 6))return;
		if (typeHand(i - 3, j, k + 2, 6))return;
		if (typeHand(i, j, k + 3, 6))return;
		if (typeHand(i - 1, j, k + 3, 6))return;
		if (typeHand(i - 2, j, k + 3, 6))return;
		if (typeHand(i - 3, j - 1, k, 6))return;
		if (typeHand(i - 3, j - 1, k + 1, 6))return;
		if (typeHand(i - 3, j - 1, k + 2, 6))return;
		if (typeHand(i, j - 1, k + 3, 6))return;
		if (typeHand(i - 1, j - 1, k + 3, 6))return;
		if (typeHand(i - 2, j - 1, k + 3, 6))return;
		if (typeHand(i - 3, j - 2, k, 6))return;
		if (typeHand(i - 3, j - 2, k + 1, 6))return;
		if (typeHand(i - 3, j - 2, k + 2, 6))return;
		if (typeHand(i, j - 2, k + 3, 6))return;
		if (typeHand(i - 1, j - 2, k + 3, 6))return;
		if (typeHand(i - 2, j - 2, k + 3, 6))return;
		if (typeHand(i - 3, j, k + 3, 6))return;
		if (typeHand(i - 3, j - 1, k + 3, 6))return;
		if (typeHand(i - 3, j - 2, k + 3, 6))return;
		if (typeHand(i, j - 3, k, 6))return;
		if (typeHand(i - 1, j - 3, k, 6))return;
		if (typeHand(i, j - 3, k + 1, 6))return;
		if (typeHand(i - 1, j - 3, k + 1, 6))return;
		if (typeHand(i - 2, j - 3, k, 6))return;
		if (typeHand(i - 2, j - 3, k + 1, 6))return;
		if (typeHand(i, j - 3, k + 2, 6))return;
		if (typeHand(i - 1, j - 3, k + 2, 6))return;
		if (typeHand(i - 2, j - 3, k + 2, 6))return;
		if (typeHand(i, j - 3, k + 3, 6))return;
		if (typeHand(i - 1, j - 3, k + 3, 6))return;
		if (typeHand(i - 2, j - 3, k + 3, 6))return;
		if (typeHand(i - 3, j - 3, k, 6))return;
		if (typeHand(i - 3, j - 3, k + 1, 6))return;
		if (typeHand(i - 3, j - 3, k + 2, 6))return;
		if (typeHand(i - 3, j - 3, k + 3, 6))return;
		break;
	case 7:
		if (typeHand(i - 1, j, k, 7))return;
		if (typeHand(i, j, k - 1, 7))return;
		if (typeHand(i - 1, j - 1, k, 7))return;
		if (typeHand(i, j - 1, k - 1, 7))return;
		if (typeHand(i - 1, j, k - 1, 7))return;
		if (typeHand(i - 1, j - 1, k - 1, 7))return;
		if (typeHand(i - 2, j, k, 7))return;
		if (typeHand(i - 2, j, k - 1, 7))return;
		if (typeHand(i, j, k - 2, 7))return;
		if (typeHand(i - 1, j, k - 2, 7))return;
		if (typeHand(i - 2, j, k - 2, 7))return;
		if (typeHand(i - 2, j - 1, k, 7))return;
		if (typeHand(i - 2, j - 1, k - 1, 7))return;
		if (typeHand(i, j - 1, k - 2, 7))return;
		if (typeHand(i - 1, j - 1, k - 2, 7))return;
		if (typeHand(i - 2, j - 1, k - 2, 7))return;
		if (typeHand(i, j - 2, k, 7))return;
		if (typeHand(i - 1, j - 2, k, 7))return;
		if (typeHand(i, j - 2, k - 1, 7))return;
		if (typeHand(i - 1, j - 2, k - 1, 7))return;
		if (typeHand(i - 2, j - 2, k, 7))return;
		if (typeHand(i - 2, j - 2, k - 1, 7))return;
		if (typeHand(i, j - 2, k - 2, 7))return;
		if (typeHand(i - 1, j - 2, k - 2, 7))return;
		if (typeHand(i - 2, j - 2, k - 2, 7))return;
		if (typeHand(i - 3, j, k, 7))return;
		if (typeHand(i - 3, j, k - 1, 7))return;
		if (typeHand(i - 3, j, k - 2, 7))return;
		if (typeHand(i, j, k - 3, 7))return;
		if (typeHand(i - 1, j, k - 3, 7))return;
		if (typeHand(i - 2, j, k - 3, 7))return;
		if (typeHand(i - 3, j - 1, k, 7))return;
		if (typeHand(i - 3, j - 1, k - 1, 7))return;
		if (typeHand(i - 3, j - 1, k - 2, 7))return;
		if (typeHand(i, j - 1, k - 3, 7))return;
		if (typeHand(i - 1, j - 1, k - 3, 7))return;
		if (typeHand(i - 2, j - 1, k - 3, 7))return;
		if (typeHand(i - 3, j - 2, k, 7))return;
		if (typeHand(i - 3, j - 2, k - 1, 7))return;
		if (typeHand(i - 3, j - 2, k - 2, 7))return;
		if (typeHand(i, j - 2, k - 3, 7))return;
		if (typeHand(i - 1, j - 2, k - 3, 7))return;
		if (typeHand(i - 2, j - 2, k - 3, 7))return;
		if (typeHand(i - 3, j, k - 3, 7))return;
		if (typeHand(i - 3, j - 1, k - 3, 7))return;
		if (typeHand(i - 3, j - 2, k - 3, 7))return;
		if (typeHand(i, j - 3, k, 7))return;
		if (typeHand(i - 1, j - 3, k, 7))return;
		if (typeHand(i, j - 3, k - 1, 7))return;
		if (typeHand(i - 1, j - 3, k - 1, 7))return;
		if (typeHand(i - 2, j - 3, k, 7))return;
		if (typeHand(i - 2, j - 3, k - 1, 7))return;
		if (typeHand(i, j - 3, k - 2, 7))return;
		if (typeHand(i - 1, j - 3, k - 2, 7))return;
		if (typeHand(i - 2, j - 3, k - 2, 7))return;
		if (typeHand(i, j - 3, k - 3, 7))return;
		if (typeHand(i - 1, j - 3, k - 3, 7))return;
		if (typeHand(i - 2, j - 3, k - 3, 7))return;
		if (typeHand(i - 3, j - 3, k, 7))return;
		if (typeHand(i - 3, j - 3, k - 1, 7))return;
		if (typeHand(i - 3, j - 3, k - 2, 7))return;
		if (typeHand(i - 3, j - 3, k - 3, 7))return;
		break;
	case 8:
		if (typeHand(i + 1, j, k, 8))return;
		if (typeHand(i, j, k - 1, 8))return;
		if (typeHand(i + 1, j - 1, k, 8))return;
		if (typeHand(i, j - 1, k - 1, 8))return;
		if (typeHand(i + 1, j, k - 1, 8))return;
		if (typeHand(i + 1, j - 1, k - 1, 8))return;
		if (typeHand(i + 2, j, k, 8))return;
		if (typeHand(i + 2, j, k - 1, 8))return;
		if (typeHand(i, j, k - 2, 8))return;
		if (typeHand(i + 1, j, k - 2, 8))return;
		if (typeHand(i + 2, j, k - 2, 8))return;
		if (typeHand(i + 2, j - 1, k, 8))return;
		if (typeHand(i + 2, j - 1, k - 1, 8))return;
		if (typeHand(i, j - 1, k - 2, 8))return;
		if (typeHand(i + 1, j - 1, k - 2, 8))return;
		if (typeHand(i + 2, j - 1, k - 2, 8))return;
		if (typeHand(i, j - 2, k, 8))return;
		if (typeHand(i + 1, j - 2, k, 8))return;
		if (typeHand(i, j - 2, k - 1, 8))return;
		if (typeHand(i + 1, j - 2, k - 1, 8))return;
		if (typeHand(i + 2, j - 2, k, 8))return;
		if (typeHand(i + 2, j - 2, k - 1, 8))return;
		if (typeHand(i, j - 2, k - 2, 8))return;
		if (typeHand(i + 1, j - 2, k - 2, 8))return;
		if (typeHand(i + 2, j - 2, k - 2, 8))return;
		if (typeHand(i + 3, j, k, 8))return;
		if (typeHand(i + 3, j, k - 1, 8))return;
		if (typeHand(i + 3, j, k - 2, 8))return;
		if (typeHand(i, j, k - 3, 8))return;
		if (typeHand(i + 1, j, k - 3, 8))return;
		if (typeHand(i + 2, j, k - 3, 8))return;
		if (typeHand(i + 3, j - 1, k, 8))return;
		if (typeHand(i + 3, j - 1, k - 1, 8))return;
		if (typeHand(i + 3, j - 1, k - 2, 8))return;
		if (typeHand(i, j - 1, k - 3, 8))return;
		if (typeHand(i + 1, j - 1, k - 3, 8))return;
		if (typeHand(i + 2, j - 1, k - 3, 8))return;
		if (typeHand(i + 3, j - 2, k, 8))return;
		if (typeHand(i + 3, j - 2, k - 1, 8))return;
		if (typeHand(i + 3, j - 2, k - 2, 8))return;
		if (typeHand(i, j - 2, k - 3, 8))return;
		if (typeHand(i + 1, j - 2, k - 3, 8))return;
		if (typeHand(i + 2, j - 2, k - 3, 8))return;
		if (typeHand(i + 3, j, k - 3, 8))return;
		if (typeHand(i + 3, j - 1, k - 3, 8))return;
		if (typeHand(i + 3, j - 2, k - 3, 8))return;
		if (typeHand(i, j - 3, k, 8))return;
		if (typeHand(i + 1, j - 3, k, 8))return;
		if (typeHand(i, j - 3, k - 1, 8))return;
		if (typeHand(i + 1, j - 3, k - 1, 8))return;
		if (typeHand(i + 2, j - 3, k, 8))return;
		if (typeHand(i + 2, j - 3, k - 1, 8))return;
		if (typeHand(i, j - 3, k - 2, 8))return;
		if (typeHand(i + 1, j - 3, k - 2, 8))return;
		if (typeHand(i + 2, j - 3, k - 2, 8))return;
		if (typeHand(i, j - 3, k - 3, 8))return;
		if (typeHand(i + 1, j - 3, k - 3, 8))return;
		if (typeHand(i + 2, j - 3, k - 3, 8))return;
		if (typeHand(i + 3, j - 3, k, 8))return;
		if (typeHand(i + 3, j - 3, k - 1, 8))return;
		if (typeHand(i + 3, j - 3, k - 2, 8))return;
		if (typeHand(i + 3, j - 3, k - 3, 8))return;
		break;
	}
}
bool typeHand(int i, int j, int k, int o) {
	enum directList dir;
	threeVect tmp = playerEye.getPos();
	if (wholeWorld[i][j][k] == NULL)return FALSE;
	if (dir = wholeWorld[i][j][k]->isChosen(o)) {
		gunArry[BLOCK]->RGB[0] = wholeWorld[i][j][k]->RGB[0];
		gunArry[BLOCK]->RGB[1] = wholeWorld[i][j][k]->RGB[1];
		gunArry[BLOCK]->RGB[2] = wholeWorld[i][j][k]->RGB[2];
		return TRUE;
	}
	return FALSE;
}

void quitGame(int m) {
	exit(m);
}
