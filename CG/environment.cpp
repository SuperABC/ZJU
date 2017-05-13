#include "environment.h"
#include "eye.h"
#include "light.h"
#include "texture.h"
#include "particle.h"
int md[2][12] = { { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
						{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };
extern eye playerEye;
extern light *lights[8];
extern dt timeClock;
extern systemp *Rain;
planet::planet(int t) {
	type = t;
	switch (t) {
	case SUN:
		Pos_x = MAXBORDER*BLOCKSIZE;
		Pos_y = 0;
		Pos_z = MAXBORDER*BLOCKSIZE;
		Vert_x = 0;
		Vert_y = 0;
		Vert_z = 1;
		Ang = 0;
		Dist = 500000;
		break;
	case MOON:
		Pos_x = MAXBORDER*BLOCKSIZE;
		Pos_y = 0;
		Pos_z = MAXBORDER*BLOCKSIZE;
		Vert_x = 0;
		Vert_y = 0;
		Vert_z = 1;
		Ang = 180;
		Dist = 50000;
		break;
	case SKY:
		break;
	}
}
void planet::secPass() {
	Ang += (GLfloat)1800/86400;
	if (Ang >= 360)Ang -= 360;
}
void planet::show() {
	switch (type) {
	case SUN:
		playerEye.lookTo();
		if (timeClock.inRange(7, 0, 0, 16, 59, 59))glColor3f(1.0, 1.0, 0.6);
		else if (timeClock.inRange(5, 0, 0, 6, 59, 59))
			glColor3f(1.0, 0.2 + 0.8 / 120 * ((timeClock.hour - 5) * 60 + timeClock.min), 0.1 + 0.5 / 120 * ((timeClock.hour - 5) * 60 + timeClock.min));
		else if (timeClock.inRange(17, 0, 0, 18, 59, 59))
			glColor3f(1.0, 1.0 - 0.8 / 120 * ((timeClock.hour - 17) * 60 + timeClock.min), 0.6 - 0.5 / 120 * ((timeClock.hour - 17) * 60 + timeClock.min));
		else return;
		glTranslatef(MAXBORDER*BLOCKSIZE, 0, MAXBORDER*BLOCKSIZE);
		glRotatef(Ang, Vert_x, Vert_y, Vert_z);
		glTranslatef(Dist, 0, 0);
		glutSolidSphere(50000, 20, 20);
		break;
	case MOON:
		playerEye.lookTo();
		glTranslatef(MAXBORDER*BLOCKSIZE, 0, MAXBORDER*BLOCKSIZE);
		glRotatef(Ang, Vert_x, Vert_y, Vert_z);
		glTranslatef(Dist, 0, 0);
		glColor3f(0.8, 0.8, 0.5);
		glutSolidSphere(2000, 20, 20);
		break;
	case SKY:
		if (timeClock.inRange(7, 0, 0, 16, 59, 59)) {
			glColor3f(0.4, 0.8, 0.8);
		}
		else if (timeClock.inRange(5, 0, 0, 6, 59, 59))
			glColor3f(0.02 + 0.38 / 120 * ((timeClock.hour - 5) * 60 + timeClock.min), 0.02 + 0.78 / 120 * ((timeClock.hour - 5) * 60 + timeClock.min), 0.1 + 0.7 / 120 * ((timeClock.hour - 5) * 60 + timeClock.min));
		else if (timeClock.inRange(17, 0, 0, 18, 59, 59))
			glColor3f(0.4 - 0.38 / 120 * ((timeClock.hour - 17) * 60 + timeClock.min), 0.8 - 0.78 / 120 * ((timeClock.hour - 17) * 60 + timeClock.min), 0.8 - 0.7 / 120 * ((timeClock.hour - 17) * 60 + timeClock.min));
		else glColor3f(0.02, 0.02, 0.1);
		glutSolidSphere(800000, 20, 20);
	}
}
dt::dt() {
	hour = 6;
	min = 0;
	sec = 0;
	year = 2020;
	month = 1;
	day = 1;
}
void dt::oneSec(planet &s, planet &m) {
	int tmp;
	sec+=5;
	if (sec > 59) {
		sec -= 60;
		min++;
	}
	if (min > 59) {
		min -= 60;
		hour++;
	}
	if (hour > 23) {
		hour -= 24;
		day++;
	}
	if (day > (tmp = md[(year % 4 == 0 && year % 100 != 0) || year % 400 == 0][month-1] - 1)) {
		day -= tmp;
		month++;
	}
	if (month > 11) {
		month -= 12;
		year++;
	}
	s.secPass();
	m.secPass();
	for (int i = 0; i < 8; i++) {
		lights[i]->update();
	}
}
bool dt::inRange(int hour1, int min1, int sec1, int hour2, int min2, int sec2) {
	if (hour > hour1&&hour < hour2)return TRUE;
	if (hour == hour1&&hour == hour2) {
		if (min > min1&&min < min2)return TRUE;
		if (min == min1&&min == min2) {
			if (sec >= sec1&&sec <= sec2)return TRUE;
			else return FALSE;
		}
		if (min == min1)return sec >= sec1;
		if (min == min2)return sec <= sec2;
		return FALSE;
	}
	if (hour == hour1) {
		if (min > min1)return TRUE;
		if (min == min1)return sec >= sec1;
		return FALSE;
	}
	if (hour == hour2) {
		if (min < min2)return TRUE;
		if (min == min2)return sec <= sec2;
		return FALSE;
	}
	return FALSE;
}
fog::fog() {
	fogMode = GL_EXP;
	RGBA[0] = 0.5;
	RGBA[1] = 0.5;
	RGBA[2] = 0.5;
	RGBA[3] = 1.0;
	dense = 0.00000001;
	start = 1000;
	end = 3000;
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, fogMode);
	glFogfv(GL_FOG_COLOR, RGBA);
	glFogf(GL_FOG_DENSITY, dense);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, start);
	glFogf(GL_FOG_END, end);
}
void fog::update() {
	if (Rain&&dense <= 0.0004) {
		dense *= 1.02;
		glFogf(GL_FOG_DENSITY, dense);
	}
	if (!Rain&&dense > 0.00000002) {
		dense /= 1.02;
		glFogf(GL_FOG_DENSITY, dense);
	}
}
