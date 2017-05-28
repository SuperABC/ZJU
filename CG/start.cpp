#include "start.h"
#include "eye.h"
#include "file.h"
#include "texture.h"
#include "light.h"
#include "shadow.h"
#include "environment.h"
fog *fogs;
extern eye playerEye;
extern welcomeGlobal welcomeGV;
extern instructGlobal instructGV;
extern archiveGlobal archiveGV;
extern fileGlobal fileGV;
extern processStatus pro;
extern GLuint texName;
extern light *lights[8];
void start::buildMenu(int c) {
	switch (c) {
	case 0:
		if (welcomeGV.chm == FALSE) {
			glPicBegin(GL_REPLACE, 1);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 1.0); glVertex3i(-STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
			glTexCoord2f(1.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
			glTexCoord2f(1.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
			glTexCoord2f(0.0, 0.0); glVertex3i(-STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
			glEnd();
			glPicEnd();
			glPicBegin(GL_REPLACE, 2);
			glBegin(GL_QUADS);
			glTexCoord2f(1.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, 0);
			glTexCoord2f(1.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, 0);
			glTexCoord2f(0.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
			glTexCoord2f(0.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
			glEnd();
			glPicEnd();
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_QUADS);
			glVertex3i(160, 925 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(840, 925 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(840, 885 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(160, 885 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(160, 725 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(840, 725 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(840, 685 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(160, 685 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(160, 925 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(200, 925 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(200, 685 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(160, 685 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(800, 925 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(840, 925 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(840, 685 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glVertex3i(800, 685 - welcomeGV.selected * 320, STARTTHICKNESS + 2);
			glEnd();
		}
		else {
			glPicBegin(GL_REPLACE, 4);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 1.0); glVertex3i(-STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
			glTexCoord2f(1.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
			glTexCoord2f(1.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
			glTexCoord2f(0.0, 0.0); glVertex3i(-STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
			glEnd();
			glPicEnd();
			glPicBegin(GL_REPLACE, 2);
			glBegin(GL_QUADS);
			glTexCoord2f(1.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, 0);
			glTexCoord2f(1.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, 0);
			glTexCoord2f(0.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
			glTexCoord2f(0.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
			glEnd();
			glPicEnd();
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_QUADS);
			glVertex3i(160, 245 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(840, 245 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(840, 205 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(160, 205 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(840, 205 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(800, 205 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(800, 5 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(840, 5 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(160, 205 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(160, 5 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(200, 5 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(200, 205 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(160, 45 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(840, 45 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(840, 5 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glVertex3i(160, 5 - welcomeGV.mode * 480, STARTTHICKNESS + 2);
			glEnd();
		}
		break;
	case 1:
		glPicBegin(GL_REPLACE, 8);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex3i(-STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
		glTexCoord2f(1.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
		glTexCoord2f(1.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
		glTexCoord2f(0.0, 0.0); glVertex3i(-STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
		glEnd();
		glPicEnd();
		glPicBegin(GL_REPLACE, 16);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, 0);
		glTexCoord2f(1.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, 0);
		glTexCoord2f(0.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
		glTexCoord2f(0.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
		glEnd();
		glPicEnd();
		break;
	case 2:
		glPicBegin(GL_REPLACE, 32);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex3i(-STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
		glTexCoord2f(1.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
		glTexCoord2f(1.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
		glTexCoord2f(0.0, 0.0); glVertex3i(-STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
		glEnd();
		glPicEnd();
		glPicBegin(GL_REPLACE, 64);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, 0);
		glTexCoord2f(1.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, 0);
		glTexCoord2f(0.0, 0.0); glVertex3i(STARTWIDTH / 2, -STARTHEIGHT / 2, STARTTHICKNESS);
		glTexCoord2f(0.0, 1.0); glVertex3i(STARTWIDTH / 2, STARTHEIGHT / 2, STARTTHICKNESS);
		glEnd();
		glPicEnd();
		break;
	}
}
void start::menu() {
	if (welcomeGV.time == -1)return;
	if (welcomeGV.time == 0) {
		lights[0]->enable();
		lights[1]->disable();
	}
	if (welcomeGV.time == 500) {
		playerEye.setEye(1600.0, -200.0, 1600.0, 1.23*PIE, 0.46*PIE);
		playerEye.lookTo();
		welcomeGV.time++;
		welcomeGV.ent = FALSE;
	}
	else if(welcomeGV.time < 500) {
		int delta = 500 - welcomeGV.time;
		playerEye.setEye(1600.0+welcomeGV.accx*delta*delta*delta, -200.0, 1600.0+ welcomeGV.accy*delta*delta*delta, 1.23*PIE, 0.46*PIE);
		playerEye.lookTo();
	}
	else if(welcomeGV.time < 1000){
		int delta = welcomeGV.time-500;
		playerEye.setEye(1600.0 + welcomeGV.accx*delta*delta*delta, -200.0, 1600.0 + welcomeGV.accy*delta*delta*delta, 1.23*PIE, 0.46*PIE);
		playerEye.lookTo();
	}
	else if (welcomeGV.time == 1000) {
		welcomeGV.chm = FALSE;
		welcomeGV.mode = CONSTRUCT;
		pro = PLAYING;
		fileGV.explored.a1 = 2 * MAXBORDER;
		fileGV.explored.a2 = 0;
		fileGV.explored.b1 = MAXHEIGHT;
		fileGV.explored.b2 = 0;
		fileGV.explored.c1 = 2 * MAXBORDER;
		fileGV.explored.c2 = 0;
		lights[0]->disable();
		lights[1]->enable();
		fogs = new fog();
		plainWorld();
		loadData(0);
		playerEye.setEye(MAXBORDER*BLOCKSIZE+66.66666666, GROUNDLEVEL*BLOCKSIZE+0.00000001 + EYEHEIGHT, MAXBORDER*BLOCKSIZE + 66.66666666, 0.0, 0.65*PIE);
		glutPostRedisplay();
	}
	else if (welcomeGV.time < 1200) {
		int delta = 1200 - welcomeGV.time;
		playerEye.setEye(1600.0, -200.0, 1600.0, (0.43 + 0.0000001*delta*delta*delta)*PIE, 0.46*PIE);
		playerEye.lookTo();
	}
	else if (welcomeGV.time == 1200) {
		playerEye.setEye(1600.0, -200.0, 1600.0, 0.43*PIE, 0.46*PIE);
		playerEye.lookTo();
		welcomeGV.time++;
		welcomeGV.ent = FALSE;
	}
	else if (welcomeGV.time < 1400) {
		int delta = welcomeGV.time - 1200;
		playerEye.setEye(1600.0, -200.0, 1600.0, (0.43 + 0.0000001*delta*delta*delta)*PIE, 0.46*PIE);
		playerEye.lookTo();
	}
	else if (welcomeGV.time == 1400) {
		playerEye.setEye(1600.0, -200.0, 1600.0, 1.23*PIE, 0.46*PIE);
		playerEye.lookTo();
		welcomeGV.time = 501;
		welcomeGV.ent = FALSE;
	}
	else if (welcomeGV.time < 1800) {
		int delta = 1800 - welcomeGV.time;
		playerEye.setEye(1600.0, -200.0, 1600.0, (2.03 - 0.0000001*delta*delta*delta)*PIE, 0.46*PIE);
		playerEye.lookTo();
	}
	else if (welcomeGV.time == 1800) {
		playerEye.setEye(1600.0, -200.0, 1600.0, 2.03*PIE, 0.46*PIE);
		playerEye.lookTo();
		welcomeGV.time++;
		welcomeGV.ent = FALSE;
	}
	else if (welcomeGV.time < 2000) {
		int delta = welcomeGV.time - 1800;
		playerEye.setEye(1600.0, -200.0, 1600.0, (2.03 - 0.0000001*delta*delta*delta)*PIE, 0.46*PIE);
		playerEye.lookTo();
	}
	else if (welcomeGV.time == 2000) {
		playerEye.setEye(1600.0, -200.0, 1600.0, 1.23*PIE, 0.46*PIE);
		playerEye.lookTo();
		welcomeGV.time = 501;
		welcomeGV.ent = FALSE;
	}
	buildMenu(0);
}
void start::help() {
	if (instructGV.time == -1)return;
	if (instructGV.time < 200) {
		int delta = instructGV.time;
		playerEye.setEye(1600.0, -200.0, 1600.0, (2.03 - 0.0000001*delta*delta*delta)*PIE, 0.46*PIE);
		playerEye.lookTo();
	}
	else if (instructGV.time == 200) {
		playerEye.setEye(1600.0, -200.0, 1600.0, 1.23*PIE, 0.46*PIE);
		playerEye.lookTo();
		instructGV.time++;
		instructGV.ent = FALSE;
		pro = INSTRUCT;
	}
	else if (instructGV.time < 400) {
		int delta = 400 - instructGV.time;
		playerEye.setEye(1600.0, -200.0, 1600.0, (2.03 - 0.0000001*delta*delta*delta)*PIE, 0.46*PIE);
		playerEye.lookTo();
	}
	else if (instructGV.time == 400) {
		playerEye.setEye(1600.0, -200.0, 1600.0, 2.03*PIE, 0.46*PIE);
		playerEye.lookTo();
		instructGV.time = -1;
		instructGV.ent = FALSE;
		pro = WELCOME;
	}
	buildMenu(1);
}
void start::archive() {
	if (archiveGV.time == -1)return;
	if (archiveGV.time < 200) {
		int delta = archiveGV.time;
		playerEye.setEye(1600.0, -200.0, 1600.0, (0.43 + 0.0000001*delta*delta*delta)*PIE, 0.46*PIE);
		playerEye.lookTo();
	}
	else if (archiveGV.time == 200) {
		playerEye.setEye(1600.0, -200.0, 1600.0, 1.23*PIE, 0.46*PIE);
		playerEye.lookTo();
		archiveGV.time++;
		archiveGV.ent = FALSE;
		pro = ARCHIVE;
	}
	else if (archiveGV.time < 400) {
		int delta = 400 - archiveGV.time;
		playerEye.setEye(1600.0, -200.0, 1600.0, (0.43 + 0.0000001*delta*delta*delta)*PIE, 0.46*PIE);
		playerEye.lookTo();
	}
	else if (archiveGV.time == 400) {
		playerEye.setEye(1600.0, -200.0, 1600.0, 0.43*PIE, 0.46*PIE);
		playerEye.lookTo();
		archiveGV.time = -1;
		archiveGV.ent = FALSE;
		pro = WELCOME;
	}
	buildMenu(2);
}
