#include "gun.h"
#include "eye.h"
#include "obj.h"
objModel objRifle[4];
extern int winsize[2];
extern eye playerEye;
gun::gun(int t) {
	switch (t) {
	case HAND:
		buildHand();
		break;
	case KNIFE:
		//buildKnife();
		break;
	case RIFLE:
		buildRifle();
		break;
	case PISTOL:
		//buildPistol();
		break;
	case ROCKET:
		//buildRocket();
		break;
	case BLOCK:
		buildBlock();
		break;
	}
}
void gun::show() {
	showStar();
	glLoadIdentity();
	gluLookAt(-200, 50, -50, 200, 0, 0, 0, 1, 0);
	switch (type) {
	case HAND:
		break;
	case KNIFE:
		break;
	case RIFLE:
		showRifle();
		break;
	case PISTOL:
		break;
	case ROCKET:
		break;
	case BLOCK:
		showBlock();
		break;
	}
}
void gun::showStar() {
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(0, 0, 60, 0, 0, 0, 0, 1, 0);
	switch (type) {
	case HAND:
		break;
	case KNIFE:
		break;
	case RIFLE:
		glLineWidth(3.0);
		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_LINES);
		glVertex3f(-1, 0, 0);
		glVertex3f(-0.2, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(0.2, 0, 0);
		glVertex3f(0, -1.3, 0);
		glVertex3f(0, -0.30, 0);
		glVertex3f(0, 1.3, 0);
		glVertex3f(0, 0.30, 0);
		glEnd();
		break;
	case PISTOL:
		break;
	case ROCKET:
		break;
	case BLOCK:
		glLineWidth(3.0);
		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_LINE_STRIP);
		for (float i = 0; i < 2 * PIE; i+=0.1*PIE) {
			glVertex3f(cos(i), sin(i), 0);
		}
		glVertex3f(1, 0, 0);
		glEnd();
		break;
	}
	glPopMatrix();
}

void gun::buildHand() {
	type = HAND;
	totalBullet = 0;
	clipVol = 0;
	bulletLeft = 0;
}
void gun::showHand() {

}

void gun::buildRifle() {
	type = RIFLE;
	totalBullet = 180;
	clipVol = 20;
	bulletLeft = 20;
	outBullet = 0;
	for (int i = 0; i < 10; i++) {
		bulletPos[i].x = 0;
		bulletPos[i].y = 0;
		bulletPos[i].z = 0;
	}
	objRifle[0].parse("Source\\625743531.obj");
	objRifle[1].parse("Source\\625743532.obj");
	objRifle[2].parse("Source\\625743533.obj");
	objRifle[3].parse("Source\\625743534.obj");
}
void gun::showRifle() {
	glDisable(GL_DEPTH_TEST);
	glTranslatef(-60, 0, 0);
	glScalef(0.6, 0.6, 0.6);
	if (fireIcon) {
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.6, 0.0);
		glVertex3f(50, 5, 3);
		glVertex3f(50, -5, 3);
		glVertex3f(80, 0, 0);
		glVertex3f(50, 5, 3);
		glVertex3f(50, 5, -3);
		glVertex3f(80, 0, 0);
		glVertex3f(50, -5, -3);
		glVertex3f(50, -5, 3);
		glVertex3f(80, 0, 0);
		glVertex3f(80, 0, 0);
		glVertex3f(50, 5, -3);
		glVertex3f(50, -5, -3);
		glEnd();
		fireIcon++;
		if (fireIcon > 2)fireIcon = 0;
	}
	glColor3f(0.8, 0.8, 0.8);
	objRifle[0].draw();
	glColor3f(0.2, 0.2, 0.2);
	objRifle[1].draw();
	glColor3f(0.5, 0.5, 0.5);
	objRifle[2].draw();
	glColor3f(0.2, 0.2, 0.2);
	objRifle[3].draw();
	glBegin(GL_QUADS);
	/*glColor3f(0.8, 0.8, 0.8);
	glVertex3f(50, 5, 3);
	glVertex3f(50, -5, 3);
	glVertex3f(50, -5, -3);
	glVertex3f(50, 5, -3);
	glVertex3f(50, 5, 3);
	glVertex3f(50, -5, 3);
	glVertex3f(-50, -5, 3);
	glVertex3f(-50, 5, 3);
	glVertex3f(50, 5, 3);
	glVertex3f(50, 5, -3);
	glVertex3f(-50, 5, -3);
	glVertex3f(-50, 5, 3);
	glVertex3f(-50, -5, -3);
	glVertex3f(-50, 5, -3);
	glVertex3f(-50, 5, 3);
	glVertex3f(-50, -5, 3);
	glVertex3f(-50, -5, -3);
	glVertex3f(50, -5, -3);
	glVertex3f(50, -5, 3);
	glVertex3f(-50, -5, 3);
	glVertex3f(-50, -5, -3);
	glVertex3f(-50, 5, -3);
	glVertex3f(50, 5, -3);
	glVertex3f(50, -5, -3);

	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-50, -10, -3);
	glVertex3f(-50, -50, -3);
	glVertex3f(-50, -50, 3);
	glVertex3f(-50, -10, 3);
	glVertex3f(-50, -10, -3);
	glVertex3f(-60, -10, -3);
	glVertex3f(-60, -10, 3);
	glVertex3f(-50, -10, 3);
	glVertex3f(-50, -10, -3);
	glVertex3f(-60, -10, -3);
	glVertex3f(-60, -50, -3);
	glVertex3f(-50, -50, -3);
	glVertex3f(-60, -50, 3);
	glVertex3f(-60, -10, 3);
	glVertex3f(-60, -10, -3);
	glVertex3f(-60, -50, -3);
	glVertex3f(-60, -50, 3);
	glVertex3f(-50, -50, 3);
	glVertex3f(-50, -50, -3);
	glVertex3f(-60, -50, -3);
	glVertex3f(-60, -50, 3);
	glVertex3f(-50, -50, 3);
	glVertex3f(-50, -10, 3);
	glVertex3f(-60, -10, 3);

	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-50, 8, -4);
	glVertex3f(-50, 8, 4);
	glVertex3f(-50, -10, 4);
	glVertex3f(-50, -10, -4);
	glVertex3f(-50, 8, 4);
	glVertex3f(-80, 8, 4);
	glVertex3f(-80, -10, 4);
	glVertex3f(-50, -10, 4);
	glVertex3f(-50, 8, 4);
	glVertex3f(-50, 8, -4);
	glVertex3f(-80, 8, -4);
	glVertex3f(-80, 8, 4);
	glVertex3f(-80, -10, -4);
	glVertex3f(-80, -10, 4);
	glVertex3f(-80, 8, 4);
	glVertex3f(-80, 8, -4);
	glVertex3f(-80, -10, -4);
	glVertex3f(-50, -10, -4);
	glVertex3f(-50, 8, -4);
	glVertex3f(-80, 8, -4);
	glVertex3f(-80, -10, -4);
	glVertex3f(-50, -10, -4);
	glVertex3f(-50, -10, 4);
	glVertex3f(-80, -10, 4);

	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-80, 8, 4);
	glVertex3f(-150, 8, 4);
	glVertex3f(-150, -30, 4);
	glVertex3f(-80, -10, 4);
	glVertex3f(-80, 8, 4);
	glVertex3f(-150, 8, 4);
	glVertex3f(-150, 8, -4);
	glVertex3f(-80, 8, -4);
	glVertex3f(-80, 8, 4);
	glVertex3f(-80, -10, 4);
	glVertex3f(-80, -10, -4);
	glVertex3f(-80, 8, -4);
	glVertex3f(-150, -30, 4);
	glVertex3f(-150, 8, 4);
	glVertex3f(-150, 8, -4);
	glVertex3f(-150, -30, -4);
	glVertex3f(-150, -30, 4);
	glVertex3f(-80, -10, 4);
	glVertex3f(-80, -8, 4);
	glVertex3f(-150, -8, 4);
	glVertex3f(-150, -30, 4);
	glVertex3f(-150, -30, -4);
	glVertex3f(-80, -10, -4);
	glVertex3f(-80, -10, 4);*/
	glEnd();

	for (int i = 0; i < 20; i++) {
		if (bulletDist[i] >= 2000) {
			bulletDist[i] = 0;
			endBullet++;
			if (endBullet > 19)endBullet -= 20;
		}
		if (outBullet >= endBullet ? (i >= endBullet&&i < outBullet) : (i < outBullet || i >= endBullet)) {
			bulletDist[i] += 200;
			bulletPos[i].x += 200 * sin(bulletDir[i].fy)*cos(bulletDir[i].theta);
			bulletPos[i].y += 200 * cos(bulletDir[i].fy);
			bulletPos[i].z += 200 * sin(bulletDir[i].fy)*sin(bulletDir[i].theta);
		}
	}
	glLoadIdentity();
	playerEye.lookTo();
	glEnable(GL_DEPTH_TEST);
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	for (int i = 0; i < 20; i++) {
		if (outBullet >= endBullet ? (i >= endBullet&&i < outBullet) : (i < outBullet || i >= endBullet)) {
			glTranslatef(bulletPos[i].x, bulletPos[i].y, bulletPos[i].z);
			glRotatef(-bulletDir[i].theta / PIE * 180, 0, 1, 0);
			glRotatef(90 - bulletDir[i].fy / PIE * 180, 0, 0, 1);
			glTranslatef(-bulletPos[i].x, -bulletPos[i].y, -bulletPos[i].z);
			glBegin(GL_QUADS);
			glVertex3f(bulletPos[i].x, bulletPos[i].y - 1.2, bulletPos[i].z + 1.2);
			glVertex3f(bulletPos[i].x + 60, bulletPos[i].y - 1.2, bulletPos[i].z + 1.2);
			glVertex3f(bulletPos[i].x + 60, bulletPos[i].y - 1.2, bulletPos[i].z - 1.2);
			glVertex3f(bulletPos[i].x, bulletPos[i].y - 1.2, bulletPos[i].z - 1.2);
			glVertex3f(bulletPos[i].x + 60, bulletPos[i].y - 1.2, bulletPos[i].z - 1.2);
			glVertex3f(bulletPos[i].x, bulletPos[i].y - 1.2, bulletPos[i].z - 1.2);
			glVertex3f(bulletPos[i].x, bulletPos[i].y + 1.2, bulletPos[i].z - 1.2);
			glVertex3f(bulletPos[i].x + 60, bulletPos[i].y + 1.2, bulletPos[i].z - 1.2);
			glVertex3f(bulletPos[i].x, bulletPos[i].y + 1.2, bulletPos[i].z - 1.2);
			glVertex3f(bulletPos[i].x + 60, bulletPos[i].y + 1.2, bulletPos[i].z - 1.2);
			glVertex3f(bulletPos[i].x + 60, bulletPos[i].y + 1.2, bulletPos[i].z + 1.2);
			glVertex3f(bulletPos[i].x, bulletPos[i].y + 1.2, bulletPos[i].z + 1.2);
			glVertex3f(bulletPos[i].x + 60, bulletPos[i].y + 1.2, bulletPos[i].z + 1.2);
			glVertex3f(bulletPos[i].x, bulletPos[i].y + 1.2, bulletPos[i].z + 1.2);
			glVertex3f(bulletPos[i].x, bulletPos[i].y - 1.2, bulletPos[i].z + 1.2);
			glVertex3f(bulletPos[i].x + 60, bulletPos[i].y - 1.2, bulletPos[i].z + 1.2);
			glEnd();
			glPopMatrix();
			glPushMatrix();
		}
	}
	//glEnable(GL_DEPTH_TEST);
	glPopMatrix();
}

void gun::buildBlock() {
	type = BLOCK;
	totalBullet = 0;
	clipVol = 0;
	bulletLeft = 0;
}
void gun::showBlock() {
	glDisable(GL_DEPTH_TEST);
	glTranslatef(20, 80, 0);
	glRotatef(40, 0, 0, 1);
	glRotatef(10, 1, 0, 0);
	glColor3fv(RGB);
	glBegin(GL_QUADS);
	glVertex3f(-120, 30, 30);
	glVertex3f(-180, 30, 30);
	glVertex3f(-180, 30, -30);
	glVertex3f(-120, 30, -30);
	glVertex3f(-120, 30, 30);
	glVertex3f(-120, -30, 30);
	glVertex3f(-120, -30, -30);
	glVertex3f(-120, 30, -30);
	glVertex3f(-120, 30, 30);
	glVertex3f(-180, 30, 30);
	glVertex3f(-180, -30, 30);
	glVertex3f(-120, -30, 30);
	glVertex3f(-180, -30, -30);
	glVertex3f(-180, 30, -30);
	glVertex3f(-180, 30, 30);
	glVertex3f(-180, -30, 30);
	glVertex3f(-180, -30, -30);
	glVertex3f(-120, -30, -30);
	glVertex3f(-120, -30, 30);
	glVertex3f(-180, -30, 30);
	glVertex3f(-180, -30, -30);
	glVertex3f(-120, -30, -30);
	glVertex3f(-120, 30, -30);
	glVertex3f(-180, 30, -30);
	glEnd();
}

void gun::buildKnife() {

}
void gun::showKnife() {

}

void gun::buildPistol() {

}
void gun::showPistol() {

}

void gun::buildRocket() {

}
void gun::showRocket() {

}

void gun::shoot() {
	threeVect tmpPos = playerEye.getPos();
	twoVect tmpAng = playerEye.getAng();
	/*int rt;
	LPWSTR rs;
	rt = MultiByteToWideChar(CP_ACP, 0, "Source\\74353.eff", -1, NULL, 0);
	rs = (LPWSTR)malloc(rt * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, "Source\\74353.eff", -1, rs, rt * sizeof(wchar_t));
	PlaySound(rs, NULL, SND_FILENAME | SND_ASYNC);*/
	fireIcon = 1;
	GLfloat tmpx = 44.2933425, tmpy = -50, tmpz = -251.0070805;
	bulletPos[outBullet].x = tmpPos.x - (tmpz*cos(tmpAng.theta)*sin(tmpAng.fy) + tmpy*cos(tmpAng.fy)*cos(tmpAng.theta) + tmpx*sin(tmpAng.theta));
	bulletPos[outBullet].y = tmpPos.y + tmpy*sin(tmpAng.fy) - tmpz*cos(tmpAng.fy);
	bulletPos[outBullet].z = tmpPos.z + tmpx*cos(tmpAng.theta) - tmpz*sin(tmpAng.theta)*sin(tmpAng.fy) - tmpy*cos(tmpAng.fy)*sin(tmpAng.theta);
	bulletDir[outBullet].theta = tmpAng.theta - 0.02272336;
	bulletDir[outBullet].fy = tmpAng.fy - 0.02272336;
	bulletDist[outBullet] = 100;
	outBullet++;
	if (outBullet > 19)outBullet -= 20;
}
