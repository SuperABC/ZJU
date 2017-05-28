#include "player.h"
player::player() {
	name = (char *)malloc(100 * sizeof(char));
	blood = 100;
	status = EYE;
	level = 0;
	exp = 0;
}
player::~player() {
	free(name);
}
void player::showMsg() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glColor3f(0.5, 0.5, 0.2);
	gluLookAt(0, 0, 60, 0, 0, 0, 0, 1, 0);
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.2, 0.0);
	glVertex3f(-44, 30, 0);
	glVertex3f(-44, 14, 0);
	glVertex3f(-20, 14, 0);
	glVertex3f(-20, 30, 0);
	glColor3f(0.2, 0.1, 0.0);
	glVertex3f(-20, 30, 0);
	glVertex3f(-20, 14, 0);
	glVertex3f(-20, 14, -2);
	glVertex3f(-20, 30, -2);
	glColor3f(0.1, 0.05, 0.0);
	glVertex3f(-44, 14, 0);
	glVertex3f(-44, 14, -2);
	glVertex3f(-20, 14, -2);
	glVertex3f(-20, 14, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void player::isAttacked(int type) {
	switch (type) {
	case BOMB:
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
void player::addExp(int type) {
	switch (type) {
	case BOMB:
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
