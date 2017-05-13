#include "enemy.h"
#include "eye.h"
#include "world.h"
#include "particle.h"
#include "gun.h"
#include "main.h"
int bombArray[][3] = {
	23400, 1040, 25600,
	23100, 640, 20800,
	25900, 640, 25000,
	27000, 640, 25500,
	27100, 640, 24600,
	26000, 640, 24500,
	26200, 640, 25500,
	27100, 640, 24800,
	26900, 640, 23900,
	27500, 640, 24600,
	26100, 640, 24400,
	26800, 640, 25500,
	27000, 640, 23400,
	26800, 640, 25400,
	26500, 640, 23500,
	27200, 640, 24800,
	26200, 640, 24900,
	26000, 640, 25100,
	27100, 640, 23500,
	26200, 640, 25200,
};
float bombColor[][3] = {
	0.0, 0.0, 0.0,
	1.0, 0.3, 0.1,
	0.9, 0.3, 0.2,
	0.8, 0.3, 0.3,
	0.7, 0.2, 0.4,
	0.6, 0.2, 0.5,
	0.5, 0.2, 0.6,
	0.4, 0.1, 0.7,
	0.3, 0.1, 0.8,
	0.2, 0.1, 0.9,
	0.2, 0.1, 1.0
};
extern eye playerEye;
extern gun *gunArry[6];
extern block *wholeWorld[2 * MAXBORDER][MAXHEIGHT][2 * MAXBORDER];
extern playingGlobal playingGV;
systemp *Blast;
enemy::enemy(int t, int p) {
	type = t;
	appear = FALSE;
	switch (t) {
	case BOMB:
		blood = 10;
		ex = bombArray[p][0];
		ey = bombArray[p][1];
		ez = bombArray[p][2];
		face_ang = (rand() % 360) / 180 * PIE;
		face_x = cos(face_ang);
		face_y = 0;
		face_z = sin(face_ang);
		changing = FALSE;
		changeDir = 0;
		break;
	case SOLDIER:
		break;
	case KNIGHT:
		break;
	case MOUSE:
		break;
	case SUPER:
		break;
	case TRANSF:
		break;
	case BOSS:
		break;
	}
}
void enemy::showEnemy() {
	//if (!appear)return;
	glPushMatrix();
	glLoadIdentity();
	playerEye.lookTo();
	glTranslatef(ex, ey, ez);
	glRotatef(-face_ang*180/PIE, 0, 1, 0);
	switch (type) {
	case BOMB:
		glShadeModel(GL_SMOOTH);
		glColor3f(bombColor[blood][0], bombColor[blood][1], bombColor[blood][2]);
		glPushMatrix();
		glTranslatef(40, 20, 40);
		glRotatef(30, 0, 0, 1);
		glRotatef(-90, 0, 1, 0);
		glutSolidTeaspoon(100);
		glPopMatrix();
		glutSolidTeapot(40);
		break;
	case SOLDIER:
		break;
	case KNIGHT:
		break;
	case MOUSE:
		break;
	case SUPER:
		break;
	case TRANSF:
		break;
	case BOSS:
		break;
	case DEATH:
		Blast->systemLoop();
		break;
	}
	glPopMatrix();
}
void enemy::randMove() {
	face_x = cos(face_ang);
	face_y = 0;
	face_z = sin(face_ang);
	ex += face_x * 10;
	ey += face_y * 10;
	ez += face_z * 10;
	if (wholeWorld[(int)(ex + face_x * 140) / BLOCKSIZE][(int)(ey + face_y * 140) / BLOCKSIZE][(int)(ez + face_z * 140) / BLOCKSIZE]) {
		if (!changing) {
			changeDir = rand() & 1;
			changing = TRUE;
		}
	}
	else if(!(rand()%10))changing = FALSE;
	if (wholeWorld[(int)(ex - 80) / BLOCKSIZE][(int)(ey) / BLOCKSIZE][(int)(ez) / BLOCKSIZE] ||
		 wholeWorld[(int)(ex + 80) / BLOCKSIZE][(int)(ey) / BLOCKSIZE][(int)(ez) / BLOCKSIZE] ||
		 wholeWorld[(int)(ex) / BLOCKSIZE][(int)(ey) / BLOCKSIZE][(int)(ez - 80) / BLOCKSIZE] ||
		 wholeWorld[(int)(ex) / BLOCKSIZE][(int)(ey) / BLOCKSIZE][(int)(ez + 80) / BLOCKSIZE]) {
		ex -= face_x * 10;
		ey -= face_y * 10;
		ez -= face_z * 10;
		if (!changing) {
			changeDir = rand() & 1;
			changing = TRUE;
		}
	}
	else if (!(rand() % 10))changing = FALSE;
	if ((!changing) && !(rand()%40)) {
		changeDir = rand() & 1;
		changing = TRUE;
	}
	if (changeDir&&changing)face_ang += 0.2;
	else if (changing) face_ang -= 0.2;
}
inline bool enemy::inRange(int x, int y, int z) {
	return x<ex + 60 && x>ex - 60 && y<ey + 60 && y>ey - 60 && z<ez + 60 && z>ez - 60;
}
bool enemy::beKilled() {
	for (int i = 0; i < 20; i++) {
		if (gunArry[playingGV.tmpGun]->outBullet >= gunArry[playingGV.tmpGun]->endBullet ? (i >= gunArry[playingGV.tmpGun]->endBullet&&i < gunArry[playingGV.tmpGun]->outBullet) : (i < gunArry[playingGV.tmpGun]->outBullet || i >= gunArry[playingGV.tmpGun]->endBullet)) {
			if (inRange(gunArry[playingGV.tmpGun]->bulletPos[i].x, gunArry[playingGV.tmpGun]->bulletPos[i].y, gunArry[playingGV.tmpGun]->bulletPos[i].z)) {
				if (blood > 1) {
					blood--;
					return 0;
				}
				int xpos1[] = { ex };
				int ypos1[] = { ey };
				int zpos1[] = { ez };
				delete Blast;
				Blast = new systemp(xpos1, ypos1, zpos1, BLAST, 1);
				delete this;
				return 1;
			}
		}
	}
	return 0;
}
