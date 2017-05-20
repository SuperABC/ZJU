#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define FREEGLUT_STATIC
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <atlimage.h>
#include "GL/freeglut.h"
#include <GL/gl.h>
#include <GL/glaux.h> 
#include <GL/glext.h>
#pragma comment(lib, "legacy_stdio_definitions.lib")
#ifndef GL_Lib
#ifdef _DEBUG
#define GL_Lib(name) name "d.lib"
#else
#define GL_Lib(name) name ".lib"
#endif
#endif
#pragma comment(lib, GL_Lib("freeglut_static"))

#define BLOCKSIZE 100
#define EYEHEIGHT 180
#define CROUCHHEIGHT 80
#define FIGUREHIGHT 190
#define FIGUREWIDTH 60
#define PIE 3.1415927
#define NORMALSPEED 0.01
#define GROUNDLEVEL 6
#define MAXBORDER 240
#define MAXHEIGHT 40
#define EYESIGHT 2000
#define MAPTOMETER 0.01

#define ABS(a) ((a)>0?(a):(-(a)))

struct sixVect {
	GLfloat a1, a2, b1, b2, c1, c2;
};
struct fourVect {
	GLfloat x, y, z, w;
};
struct threeVect {
	GLfloat x, y, z;
};
struct twoVect {
	GLfloat theta, fy;
};
struct mousePos {
	GLfloat mx, my;
};

enum directList{
	NONE,
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
enum startSelect {
	START = 1,
	CONTINUE,
	HELP,
	QUIT
};
enum gunList {
	HAND,
	KNIFE,
	RIFLE,
	PISTOL,
	ROCKET,
	BLOCK
};
enum playerStatus {
	EYE,
	GROUND
};
enum processStatus {
	INIT,
	LOADING,
	WELCOME,
	INSTRUCT,
	ARCHIVE,
	PLAYING,
	PAUSE,
	DEAD,
	SHOP,
	INFORMATION
};
enum gameMode {
	CONSTRUCT,
	SHOOT
};

typedef struct {
	processStatus type = INIT;
	bool ent = FALSE;
	long time = 0;
}initGlobal;
typedef struct {
	processStatus type = LOADING;
	bool ent = FALSE;
	long time = 0;
}loadingGlobal;
typedef struct {
	processStatus type = WELCOME;
	bool ent = FALSE;
	long time = 0;
	GLfloat accx, accy;
	int selected = START;
	bool chm = FALSE;
	int mode = CONSTRUCT;
}welcomeGlobal;
typedef struct {
	processStatus type = INSTRUCT;
	bool ent = FALSE;
	long time = -1;
}instructGlobal;
typedef struct {
	processStatus type = ARCHIVE;
	bool ent = FALSE;
	long time = -1;
}archiveGlobal;
typedef struct {
	processStatus type = PLAYING;
	bool ent = FALSE;
	long time = 0;
	long moti = 0;
	mousePos tmpms = { -1,-1 };
	int speedX = 0, speedY = 0, speedZ = 0;
	bool enXp = 0, enXn = 0, enZp = 0, enZn = 0, enYp = 0, enYn = 0;
	int enY = 0;
	int tmpGun = RIFLE;
	bool crouch = FALSE;
	int mode;
}playingGlobal;
typedef struct {
	processStatus type = PAUSE;
	bool ent = FALSE;
	long time = 0;
	int mode;
}pauseGlobal;
typedef struct {
	processStatus type = DEAD;
	bool ent = FALSE;
	long time = 0;
	int mode;
}deadGlobal;
typedef struct {
	processStatus type = SHOP;
	bool ent = FALSE;
	long time = 0;
	mousePos tmpms = { -1,-1 };
	int mode;
}shopGlobal;
typedef struct {
	processStatus type = INFORMATION;
	bool ent = FALSE;
	long time = 0;
}informationGlobal;
typedef struct {
	int isLoaded;
	sixVect explored;
}fileGlobal;

inline bool checkFace(int i, int j, int k);
inline bool inRect(int x, int y, int rx, int ry, int width, int height);
inline GLfloat calcDist(struct threeVect v1, struct threeVect v2);

void initPro();
void showMsg();
void initSight(int m = 0);
void plainWorld();
void sightLimit();
void putBlock();
void disBlock();
void putOctant(int octant);
void disOctant(int octant);
bool creatBlock(int i, int j, int k, int type, int o);
bool clearBlock(int i, int j, int k, int o);
void changeHand();
void typeOctant(int octant);
bool typeHand(int i, int j, int k, int o);
void quitGame(int m);
