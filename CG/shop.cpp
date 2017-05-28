#include "shop.h"
#include "eye.h"
extern playingGlobal playingGV;
extern eye playerEye;
extern processStatus pro;
eye shopEye;
shop::shop() {
	flySpeed = 1.6;
}
void shop::inTo() {
	twoVect playerTmp = playerEye.getAng();
	shopEye.setEye(-1200, -100, 1600, 5.36, playerTmp.fy);
	int delta = 1040 - playingGV.time;
	playerEye.moveEye(0, 0, delta*delta*flySpeed);
	shopEye.moveEye(0, 0, -flySpeed*delta*delta*delta*delta*0.01);
	showHouse();
}
void shop::outOf() {
	twoVect playerTmp = playerEye.getAng();
	twoVect shopTmp = shopEye.getAng();
	shopEye.setEye(-1200, -100, 1600, shopTmp.theta, playerTmp.fy);
	int delta = playingGV.time - 1040;
	playerEye.moveEye(0, 0, -delta*delta*flySpeed);
	shopEye.moveEye(0, 0, -flySpeed*delta*delta*delta*delta*0.01);
	showHouse();
}
void shop::showHouse() {
	glLoadIdentity();
	shopEye.lookTo();
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3i(-2000 / 2, 1600 / 2, 0);
	glVertex3i(2000 / 2, 1600 / 2, 0);
	glVertex3i(2000 / 2, -1600 / 2, 0);
	glVertex3i(-2000 / 2, -1600 / 2, 0);

	glVertex3i(2000 / 2, -1600 / 2, 0);
	glVertex3i(-2000 / 2, -1600 / 2, 0);
	glVertex3i(-2000 / 2, -1600 / 2, 200);
	glVertex3i(2000 / 2, -1600 / 2, 200);

	glVertex3i(-2000 / 2, -1600 / 2, 200);
	glVertex3i(2000 / 2, -1600 / 2, 200);
	glVertex3i(2000 / 2, 1600 / 2, 200);
	glVertex3i(-2000 / 2, 1600 / 2, 200);

	glVertex3i(2000 / 2, 1600 / 2, 200);
	glVertex3i(-2000 / 2, 1600 / 2, 200);
	glVertex3i(-2000 / 2, 1600 / 2, 0);
	glVertex3i(2000 / 2, 1600 / 2, 0);
	glEnd();

	glColor3f(0.2, 0.7, 0.7);
	glBegin(GL_QUADS);
	glVertex3i(2000 / 2, 1600 / 2, 0);
	glVertex3i(2000 / 2, -1600 / 2, 0);
	glVertex3i(2000 / 2, -1600 / 2, 200);
	glVertex3i(2000 / 2, 1600 / 2, 200);

	glVertex3i(-2000 / 2, 1600 / 2, 0);
	glVertex3i(-2000 / 2, -1600 / 2, 0);
	glVertex3i(-2000 / 2, -1600 / 2, 200);
	glVertex3i(-2000 / 2, 1600 / 2, 200);
	glEnd();
	glLoadIdentity();
}
void shop::stayIn() {
	showHouse();
}
