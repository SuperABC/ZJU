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

using std::cout;
using std::endl;
using std::cin;

initGlobal initGV;
loadingGlobal loadingGV;
welcomeGlobal welcomeGV;
instructGlobal instructGV;
archiveGlobal archiveGV;
playingGlobal playingGV;
pauseGlobal pauseGV;
deadGlobal deadGV;
shopGlobal shopGV;
informationGlobal informationGV;
fileGlobal fileGV;

start menuTable;
block *wholeWorld[2 * MAXBORDER][MAXHEIGHT][2 * MAXBORDER];
eye playerEye;
player *playerSelf = new player;
gun *gunArry[6];
shop shopHouse;
planet sun(0), moon(1), sky(2);
dt timeClock;
light *lights[8] = { 0 };
enemy *enemies[TOTALENEMY][100];
processStatus pro = INIT;
systemp *Rain = NULL;
extern systemp *Blast;
extern eye shopEye;
extern fog *fogs;
int winsize[2] = { 1200, 600 };

static void myDisplay();
static void myReshape(int w, int h);
static void myMouse(int x, int y);
static void myClick(int button, int state, int x, int y);
static void myWheel(int wheel, int dir, int x, int y);
static void myKeyup(unsigned char cAscii, int x, int y);
static void myKey(unsigned char cAscii, int x, int y);
static void mySpecialup(GLint cAscii, int x, int y);
static void mySpecial(GLint cAscii, int x, int y);
static void myIdle(void);

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	cout << "魔域冲锋：" << endl;
	cout << endl;
	cout << "欢迎来到游戏！盛大的场景、炫酷的特效、逼真的体验等你来发现！" << endl;
	cout << "作者：朱瑞昇 李恒新" << endl;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(40, 20);
	glutInitWindowSize(1200, 600);
	glutCreateWindow("GLHomework");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutMouseFunc(myClick);
	glutMotionFunc(myMouse);
	glutPassiveMotionFunc(myMouse);
	glutMouseWheelFunc(myWheel);
	glutKeyboardFunc(myKey);
	glutKeyboardUpFunc(myKeyup);
	glutSpecialFunc(mySpecial);
	glutSpecialUpFunc(mySpecialup);
	glutIdleFunc(myIdle);
	initPro();
	glutFullScreen();
	glutMainLoop();
}

static void myDisplay() {
	threeVect tmp = playerEye.getPos();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (pro) {
	case INIT:
		showMsg();
		glFlush();
		break;
	case LOADING:
		break;
	case WELCOME:
		initSight();
		menuTable.menu();
		initSight(1);
		menuTable.help();
		initSight(1);
		menuTable.archive();
		glFlush();
		break;
	case INSTRUCT:
		break;
	case ARCHIVE:
		break;
	case PLAYING:
		initSight();
		lights[1]->disable();
		glPushMatrix();
		sun.show();
		glPopMatrix();
		glPushMatrix();
		moon.show();
		glPopMatrix();
		glPushMatrix();
		sky.show();
		glPopMatrix();
		if (playingGV.time > 1000&&playingGV.time < 1040)shopHouse.inTo();
		else if (playingGV.time == 1040) {
			playingGV.ent = FALSE;
			pro = SHOP;
			shopGV.tmpms.mx = -1;
			shopGV.tmpms.my = -1;
			lights[1]->disable();
			shopHouse.stayIn();
		}
		else if (playingGV.time > 1040 && playingGV.time < 1080) {
			if(playingGV.time == 1041)lights[1]->enable();
			shopHouse.outOf();
		}
		else if (playingGV.time == 1080) {
			playingGV.ent = FALSE;
			playingGV.enXn = 0;
			playingGV.enXp = 0;
			playingGV.enZn = 0;
			playingGV.enZp = 0;
			playingGV.time = 0;
		}
		//generateShadow();
		//generateDepth();
		playerEye.lookTo();
		lights[1]->enable();
		if(tmp.y<10000)sightLimit();
		for (int i = 0; i < BOMBPOS; i++) {
			if (enemies[BOMB][i] != NULL)enemies[BOMB][i]->showEnemy();
		}
		if(Rain)Rain->systemLoop();
		if (Blast)Blast->systemLoop();
		gunArry[playingGV.tmpGun]->show();
		playerSelf->showMsg();
		glFlush();
		break;
	case PAUSE:
		break;
	case DEAD:
		break;
	case SHOP:
		initSight();
		shopHouse.stayIn();
		gunArry[playingGV.tmpGun]->show();
		glFlush();
		break;
	case INFORMATION:
		break;
	default:
		cout << "Unknown status" << endl;
		break;
	}
}
static void myReshape(int w, int h) {
	winsize[0] = w;
	winsize[1] = h;
	switch (pro) {
	case INIT:
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		break;
	case LOADING:
		break;
	case WELCOME:
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (w <= h)
			glOrtho(-3, 3, -3 * (GLfloat)h / (GLfloat)w,
				3 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
		else
			glOrtho(-3 * (GLfloat)w / (GLfloat)h,
				3 * (GLfloat)w / (GLfloat)h, -3, 3, -10.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;
	case INSTRUCT:
		break;
	case ARCHIVE:
		break;
	case PLAYING:
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (w <= h)
			glOrtho(-3, 3, -3 * (GLfloat)h / (GLfloat)w,
				3 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
		else
			glOrtho(-3 * (GLfloat)w / (GLfloat)h,
				3 * (GLfloat)w / (GLfloat)h, -3, 3, -10.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;
	case PAUSE:
		break;
	case DEAD:
		break;
	case SHOP:
		break;
	case INFORMATION:
		break;
	default:
		cout << "Unknown status" << endl;
		break;
	}
	myDisplay();
}
static void myMouse(int x, int y) {
	GLint xoffset, yoffset;
	switch (pro) {
	case INIT:
		break;
	case LOADING:
		break;
	case WELCOME:
		break;
	case INSTRUCT:
		break;
	case ARCHIVE:
		break;
	case PLAYING:
		if (playingGV.tmpms.mx<0 || playingGV.tmpms.my<0) {
			playingGV.tmpms.mx = x;
			playingGV.tmpms.my = y;
		}
		if (x > 1278) {
			x = 2;
			SetCursorPos(2, y);
			xoffset = x + 1276 - playingGV.tmpms.mx;
		}
		else if (x < 2) {
			x = 1278;
			SetCursorPos(1278, y);
			xoffset = x - 1276 - playingGV.tmpms.mx;
		}
		else xoffset = x - playingGV.tmpms.mx;
		if (y > 718) {
			y = 2;
			SetCursorPos(x, 2);
			yoffset = playingGV.tmpms.my - y - 716;
		}
		else if (y < 2) {
			y = 718;
			SetCursorPos(x, 718);
			yoffset = playingGV.tmpms.my - y + 716;
		}
		else yoffset = playingGV.tmpms.my - y;
		playingGV.tmpms.mx = x;
		playingGV.tmpms.my = y;
		if (xoffset == 0 && yoffset == 0)return;
		playerEye.rotateEye((float)xoffset / 360 * PIE, (float)-yoffset / 360 * PIE);
		break;
	case PAUSE:
		break;
	case DEAD:
		break;
	case SHOP:
		if (shopGV.tmpms.mx<0 || shopGV.tmpms.my<0) {
			shopGV.tmpms.mx = x;
			shopGV.tmpms.my = y;
		}
		xoffset = x - shopGV.tmpms.mx;
		yoffset = shopGV.tmpms.my - y;
		shopGV.tmpms.mx = x;
		shopGV.tmpms.my = y;
		if (xoffset == 0 && yoffset == 0)return;
		shopEye.rotateEye((float)xoffset / 360 * PIE, (float)-yoffset / 360 * PIE);
		playerEye.rotateEye((float)xoffset / 360 * PIE, (float)-yoffset / 360 * PIE);
		break;
	case INFORMATION:
		break;
	default:
		cout << "Unknown status" << endl;
		break;
	}
	ShowCursor(FALSE);
}
static void myClick(int button, int state, int x, int y) {
	switch (pro) {
	case INIT:
		break;
	case LOADING:
		break;
	case WELCOME:
		break;
	case INSTRUCT:
		break;
	case ARCHIVE:
		break;
	case PLAYING:
		if (playingGV.mode == CONSTRUCT) {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				disBlock();
			}
			if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
				putBlock();
			}
			if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
				changeHand();
			}
		}
		else {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				gunArry[playingGV.tmpGun]->shoot();
			}
		}
		break;
	case PAUSE:
		break;
	case DEAD:
		break;
	case SHOP:
		break;
	case INFORMATION:
		break;
	default:
		cout << "Unknown status" << endl;
		break;
	}
}
static void myWheel(int wheel, int dir, int x, int y) {
	switch (pro) {
	case INIT:
		break;
	case LOADING:
		break;
	case WELCOME:
		break;
	case INSTRUCT:
		break;
	case ARCHIVE:
		break;
	case PLAYING:
		if (playingGV.mode == CONSTRUCT) {
			if (dir > 0) {
				gunArry[BLOCK]->RGB[2] += 0.1;
				if (gunArry[BLOCK]->RGB[2] > 1) {
					gunArry[BLOCK]->RGB[2] -= 1.1;
					gunArry[BLOCK]->RGB[1] += 0.1;
				}
				if (gunArry[BLOCK]->RGB[1] > 1) {
					gunArry[BLOCK]->RGB[1] -= 1.1;
					gunArry[BLOCK]->RGB[0] += 0.1;
				}
				if (gunArry[BLOCK]->RGB[0] > 1) {
					gunArry[BLOCK]->RGB[0] -= 1.1;
				}
			}
			else if (dir < 0) {
				gunArry[BLOCK]->RGB[2] -= 0.1;
				if (gunArry[BLOCK]->RGB[2] < 0) {
					gunArry[BLOCK]->RGB[2] += 1.1;
					gunArry[BLOCK]->RGB[1] -= 0.1;
				}
				if (gunArry[BLOCK]->RGB[1] < 0) {
					gunArry[BLOCK]->RGB[1] += 1.1;
					gunArry[BLOCK]->RGB[0] -= 0.1;
				}
				if (gunArry[BLOCK]->RGB[0] < 0) {
					gunArry[BLOCK]->RGB[0] += 1.1;
				}
			}
		}
		break;
	case PAUSE:
		break;
	case DEAD:
		break;
	case SHOP:
		break;
	case INFORMATION:
		break;
	default:
		cout << "Unknown status" << endl;
		break;
	}
}
static void myKeyup(unsigned char cAscii, int x, int y) {
	switch (pro) {
	case INIT:
		break;
	case LOADING:
		break;
	case WELCOME:
		break;
	case INSTRUCT:
		break;
	case ARCHIVE:
		break;
	case PLAYING:
		switch (cAscii) {
		case 'w':case VK_UP:
			playingGV.enXp = 0;
			break;
		case 's':case VK_DOWN:
			playingGV.enXn = 0;
			break;
		case 'a':case VK_LEFT:
			playingGV.enZn = 0;
			break;
		case 'd':case VK_RIGHT:
			playingGV.enZp = 0;
			break;
		case VK_SPACE:
			playingGV.enYp = FALSE;
			break;
		case 'x':case '/':
			playingGV.enYn = FALSE;
			break;
		}
	case PAUSE:
		break;
	case DEAD:
		break;
	case SHOP:
		break;
	case INFORMATION:
		break;
	default:
		cout << "Unknown status" << endl;
		break;
	}
}
static void myKey(unsigned char cAscii, int x, int y) {
	switch (pro) {
	case INIT:
		pro = LOADING;
		break;
	case LOADING:
		break;
	case WELCOME:
		if (welcomeGV.time > 1000)break;
		if (!welcomeGV.chm) {
			switch (cAscii) {
			case VK_RETURN:
				switch (welcomeGV.selected) {
				case START:
					welcomeGV.chm = TRUE;
					break;
				case CONTINUE:
					welcomeGV.time = 1601;
					welcomeGV.ent = TRUE;
					archiveGV.ent = TRUE;
					break;
				case HELP:
					welcomeGV.time = 1001;
					welcomeGV.ent = TRUE;
					instructGV.ent = TRUE;
					break;
				case QUIT:
					quitGame(0);
					break;
				}
				break;
			case 'w':case VK_UP:
				welcomeGV.selected = (welcomeGV.selected + 2) % 4 + 1;
				break;
			case 's':case VK_DOWN:
				welcomeGV.selected = welcomeGV.selected % 4 + 1;
				break;
			}
		}
		else {
			switch (cAscii) {
			case VK_RETURN:
				if (welcomeGV.mode == SHOOT) {
					playingGV.mode = SHOOT;
					pauseGV.mode = SHOOT;
					shopGV.mode = SHOOT;
					deadGV.mode = SHOOT;
					playingGV.tmpGun = RIFLE;
				}
				else {
					playingGV.mode = CONSTRUCT;
					pauseGV.mode = CONSTRUCT;
					shopGV.mode = CONSTRUCT;
					deadGV.mode = CONSTRUCT;
					playingGV.tmpGun = BLOCK;
				}
				welcomeGV.ent = TRUE;
				break;
			case 'w':
				welcomeGV.mode = welcomeGV.mode == SHOOT ? CONSTRUCT : SHOOT;
				break;
			case 's':
				welcomeGV.mode = welcomeGV.mode == SHOOT ? CONSTRUCT : SHOOT;
				break;
			case VK_ESCAPE:
				welcomeGV.chm = FALSE;
				break;
			}
		}
		break;
	case INSTRUCT:
		switch (cAscii) {
		case VK_ESCAPE:
			pro = WELCOME;
			welcomeGV.ent = TRUE;
			instructGV.ent = TRUE;
		}
		break;
	case ARCHIVE:
		switch (cAscii) {
		case VK_ESCAPE:
			pro = WELCOME;
			welcomeGV.ent = TRUE;
			archiveGV.ent = TRUE;
		}
		break;
	case PLAYING:
		if (playingGV.time > 1000 && playingGV.time < 1080)break;
		switch (cAscii) {
		case VK_ESCAPE:
			welcomeGV.time = 0;
			welcomeGV.ent = TRUE;
			glDisable(GL_LIGHTING);
			glDisable(GL_FOG);
			pro = WELCOME;
			break;
		case 'w':case VK_UP:
			playingGV.enXp = TRUE;
			break;
		case 's':case VK_DOWN:
			playingGV.enXn = TRUE;
			break;
		case 'a':case VK_LEFT:
			playingGV.enZn = TRUE;
			break;
		case 'd':case VK_RIGHT:
			playingGV.enZp = TRUE;
			break;
		case VK_SPACE:
			if (playingGV.mode == SHOOT) {
				if (!playingGV.enY && !playingGV.crouch) {
					playingGV.enY = 1;
					playingGV.speedY = 50;
				}
			}
			else {
				playingGV.enYp = TRUE;
			}
			break;
		case 'x':case '/':
			if (playingGV.mode == CONSTRUCT) {
				playingGV.enYn = TRUE;
			}
			break;
		case 'j':
			playingGV.ent = TRUE;
			playingGV.time = 1001;
			break;
		case 'z':
			playingGV.crouch = !playingGV.crouch;
			playerEye.moveEye(0, 0, playingGV.crouch ? -100 : 100);
			break;
		case 'p':
			saveData(0);
			break;
		case VK_RETURN:
			putBlock();
			break;
		}
		break;
	case PAUSE:
		break;
	case DEAD:
		break;
	case SHOP:
		switch (cAscii) {
		case 'k':
			playingGV.ent = TRUE;
			pro = PLAYING;
			playingGV.tmpms.mx = -1;
			playingGV.tmpms.my = -1;
			playingGV.time = 1041;
		}
		break;
	case INFORMATION:
		break;
	default:
		cout << "Unknown status" << endl;
		break;
	}
}
static void mySpecialup(GLint cAscii, int x, int y) {
	switch (pro) {
	case INIT:
		break;
	case LOADING:
		break;
	case WELCOME:
		break;
	case INSTRUCT:
		break;
	case ARCHIVE:
		break;
	case PLAYING:
		switch (cAscii) {
		case GLUT_KEY_UP:
			playingGV.enXp = 0;
			break;
		case GLUT_KEY_DOWN:
			playingGV.enXn = 0;
			break;
		case GLUT_KEY_LEFT:
			playingGV.enZn = 0;
			break;
		case GLUT_KEY_RIGHT:
			playingGV.enZp = 0;
			break;
		}
	case PAUSE:
		break;
	case DEAD:
		break;
	case SHOP:
		break;
	case INFORMATION:
		break;
	default:
		cout << "Unknown status" << endl;
		break;
	}
}
static void mySpecial(GLint cAscii, int x, int y) {
	switch (pro) {
	case INIT:
		pro = LOADING;
		break;
	case LOADING:
		break;
	case WELCOME:
		if (welcomeGV.time > 1000)break;
		if (!welcomeGV.chm) {
			switch (cAscii) {
			case GLUT_KEY_UP:
				welcomeGV.selected = (welcomeGV.selected + 2) % 4 + 1;
				break;
			case GLUT_KEY_DOWN:
				welcomeGV.selected = welcomeGV.selected % 4 + 1;
				break;
			}
		}
		else {
			switch (cAscii) {
			case GLUT_KEY_UP:
				welcomeGV.mode = welcomeGV.mode == SHOOT ? CONSTRUCT : SHOOT;
				break;
			case GLUT_KEY_DOWN:
				welcomeGV.mode = welcomeGV.mode == SHOOT ? CONSTRUCT : SHOOT;
				break;
			}
		}
		break;
	case INSTRUCT:
		break;
	case ARCHIVE:
		break;
	case PLAYING:
		if (playingGV.time > 1000 && playingGV.time < 1080)break;
		switch (cAscii) {
		case GLUT_KEY_UP:
			playingGV.enXp = TRUE;
			break;
		case GLUT_KEY_DOWN:
			playingGV.enXn = TRUE;
			break;
		case GLUT_KEY_LEFT:
			playingGV.enZn = TRUE;
			break;
		case GLUT_KEY_RIGHT:
			playingGV.enZp = TRUE;
			break;
		}
		break;
	case PAUSE:
		break;
	case DEAD:
		break;
	case SHOP:
		break;
	case INFORMATION:
		break;
	default:
		cout << "Unknown status" << endl;
		break;
	}
}
static void myIdle(void) {
	threeVect tmpPos;
	switch (pro) {
	case INIT:
		if (initGV.ent)initGV.time++;
		if (initGV.time > 4200) {
			pro = LOADING;
			initGV.ent = FALSE;
		}
		break;
	case LOADING:
		if (loadingGV.ent)loadingGV.time++;
		pro = WELCOME;
		welcomeGV.time = 0;
		welcomeGV.ent = TRUE;
		myReshape(winsize[0], winsize[1]);
		break;
	case WELCOME:
		if (welcomeGV.ent)welcomeGV.time++;
		if (instructGV.ent)instructGV.time++;
		if (archiveGV.ent)archiveGV.time++;
		break;
	case INSTRUCT:
		if (instructGV.ent)instructGV.time++;
		break;
	case ARCHIVE:
		if (archiveGV.ent)archiveGV.time++;
		break;
	case PLAYING:
		if (playingGV.ent)playingGV.time++;
		if (playingGV.enXp ==TRUE) {
			if (playingGV.speedX < 30)playingGV.speedX += 3;
		}
		else if (playingGV.enXp == FALSE&&playingGV.speedX > 0) {
			playingGV.speedX -= 3;
		}
		if (playingGV.enXn == TRUE) {
			if (playingGV.speedX > -30)playingGV.speedX -= 3;
		}
		else if (playingGV.enXn == FALSE&&playingGV.speedX < 0) {
			playingGV.speedX += 3;
		}
		if (playingGV.enZn ==TRUE) {
			if (playingGV.speedZ < 30)playingGV.speedZ += 3;
		}
		else if (playingGV.enZn == FALSE && playingGV.speedZ > 0) {
			playingGV.speedZ -= 3;
		}
		if (playingGV.enZp == TRUE) {
			if (playingGV.speedZ > -30)playingGV.speedZ -= 3;
		}
		else if (playingGV.enZp == FALSE && playingGV.speedZ < 0) {
			playingGV.speedZ += 3;
		}
		if (playingGV.time > 1000&&playingGV.time <= 1080)break;
		playerEye.moveEye(playingGV.speedX, playingGV.speedZ, 0, TRUE);
		if (playingGV.mode == SHOOT) {
			tmpPos = playerEye.getPos();
			if (!playingGV.crouch) {
				if (playingGV.enY == FALSE && !wholeWorld[(int)tmpPos.x / BLOCKSIZE][(int)(tmpPos.y - EYEHEIGHT - 1) / BLOCKSIZE][(int)tmpPos.z / BLOCKSIZE]) {
					playingGV.enY = TRUE;
					playingGV.speedY = 0;
				}
			}
			else {
				if (playingGV.enY == FALSE && !wholeWorld[(int)tmpPos.x / BLOCKSIZE][(int)(tmpPos.y - CROUCHHEIGHT - 1) / BLOCKSIZE][(int)tmpPos.z / BLOCKSIZE]) {
					playingGV.enY = TRUE;
					playingGV.speedY = 0;
				}
			}
			if (playingGV.enY == TRUE) {
				if (playingGV.speedY > -120)playingGV.speedY -= 10;
				playerEye.moveEye(0, 0, playingGV.speedY, TRUE);
				tmpPos.y += playingGV.speedY;
				if (wholeWorld[(int)tmpPos.x / BLOCKSIZE][(int)(tmpPos.y - EYEHEIGHT - 1) / BLOCKSIZE][(int)tmpPos.z / BLOCKSIZE]) {
					playingGV.enY = 0;
				}
			}
		}
		else {
			if (playingGV.enYp)playerEye.moveEye(0, 0, 20);
			if(playingGV.enYn)playerEye.moveEye(0, 0, -20);
		}
		timeClock.oneSec(sun, moon);
		for (int i = 0; i < BOMBPOS; i++) {
			if (enemies[BOMB][i] ? !enemies[BOMB][i]->beKilled() : 0)enemies[BOMB][i]->randMove();
			else enemies[BOMB][i] = NULL;
		}
		lights[1]->enable(FALSE);
		if (Rain&&!(rand() % 8000)) {
			delete Rain;
			Rain = NULL;
		}
		if (!Rain && !(rand() % 20000)) {
			tmpPos = playerEye.getPos();
			int xpos1[] = { tmpPos.x };
			int ypos1[] = { 3800};
			int zpos1[] = { tmpPos.z };
			Rain = new systemp(xpos1, ypos1, zpos1, RAIN, 1);
		}
		fogs->update();
		break;
	case PAUSE:
		if (pauseGV.ent)pauseGV.time++;
		break;
	case DEAD:
		if (deadGV.ent)deadGV.time++;
		break;
	case SHOP:
		if (shopGV.ent)shopGV.time++;
		break;
	case INFORMATION:
		if (informationGV.ent)informationGV.time++;
		break;
	default:
		cout << "Unknown status" << endl;
		break;
	}
	glutPostRedisplay();
}
