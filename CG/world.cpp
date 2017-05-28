#include "world.h"
#include "eye.h"
#include "texture.h"
extern eye playerEye;
extern block *wholeWorld[2 * MAXBORDER][MAXHEIGHT][2 * MAXBORDER];
block::block(GLint x, GLint y, GLint z) {
	type = 0;
	bx = x*BLOCKSIZE;
	by = y*BLOCKSIZE;
	bz = z*BLOCKSIZE;
}
void block::buildBlock(int t, GLfloat r, GLfloat g, GLfloat b) {
	type = t;
	RGB[0] = r;
	RGB[1] = g;
	RGB[2] = b;
}
void block::showBlock(threeVect p) {
	switch (type) {
	case 1:
		glColor3fv(RGB);
		glPushMatrix();
		glTranslatef(bx + 50, by + 50, bz + 50);
		glutSolidCube((double)BLOCKSIZE);
		glPopMatrix();
		break;
	case 2:
		if (p.x < bx)showLeft();
		else if (p.x > bx + BLOCKSIZE)showRight();
		if (p.y < by)showDown();
		else if (p.y > by + BLOCKSIZE)showUp();
		if (p.z < bz)showBack();
		else if (p.z > bz + BLOCKSIZE)showFront();
		break;
	}
}
void block::destroyBlock() {
	type = 0;
}
void block::showUp() {
	//if (wholeWorld[bx / BLOCKSIZE][by / BLOCKSIZE + 1][bz / BLOCKSIZE])return;
	int vbo[][3] = { bx, by + BLOCKSIZE, bz, bx + BLOCKSIZE, by + BLOCKSIZE, bz, bx + BLOCKSIZE, by + BLOCKSIZE, bz + BLOCKSIZE, bx, by + BLOCKSIZE, bz + BLOCKSIZE };
	glVertex3iv(vbo[0]);
	glVertex3iv(vbo[1]);
	glVertex3iv(vbo[2]);
	glVertex3iv(vbo[3]);
}
void block::showDown() {
	//if (wholeWorld[bx / BLOCKSIZE][by / BLOCKSIZE - 1][bz / BLOCKSIZE])return;
	int vbo[][3] = { bx, by, bz, bx + BLOCKSIZE, by, bz, bx + BLOCKSIZE, by, bz + BLOCKSIZE,bx, by, bz + BLOCKSIZE };
	glVertex3iv(vbo[0]);
	glVertex3iv(vbo[1]);
	glVertex3iv(vbo[2]);
	glVertex3iv(vbo[3]);
}
void block::showLeft() {
	//if (wholeWorld[bx / BLOCKSIZE - 1][by / BLOCKSIZE][bz / BLOCKSIZE])return;
	int vbo[][3] = { bx, by, bz, bx, by + BLOCKSIZE, bz, bx, by + BLOCKSIZE, bz + BLOCKSIZE, bx, by, bz + BLOCKSIZE };
	glVertex3iv(vbo[0]);
	glVertex3iv(vbo[1]);
	glVertex3iv(vbo[2]);
	glVertex3iv(vbo[3]);
}
void block::showRight() {
	//if (wholeWorld[bx / BLOCKSIZE + 1][by / BLOCKSIZE][bz / BLOCKSIZE])return;
	int vbo[][3] = { bx + BLOCKSIZE, by, bz, bx + BLOCKSIZE, by + BLOCKSIZE, bz, bx + BLOCKSIZE, by + BLOCKSIZE, bz + BLOCKSIZE, bx + BLOCKSIZE, by, bz + BLOCKSIZE };
	glVertex3iv(vbo[0]);
	glVertex3iv(vbo[1]);
	glVertex3iv(vbo[2]);
	glVertex3iv(vbo[3]);
}
void block::showBack() {
	//if (wholeWorld[bx / BLOCKSIZE][by / BLOCKSIZE][bz / BLOCKSIZE - 1])return;
	int vbo[][3] = { bx, by, bz, bx + BLOCKSIZE, by, bz, bx + BLOCKSIZE, by + BLOCKSIZE, bz, bx, by + BLOCKSIZE, bz };
	glVertex3iv(vbo[0]);
	glVertex3iv(vbo[1]);
	glVertex3iv(vbo[2]);
	glVertex3iv(vbo[3]);
}
void block::showFront() {
	//if (wholeWorld[bx / BLOCKSIZE][by / BLOCKSIZE][bz / BLOCKSIZE + 1])return;
	int vbo[][3] = { bx, by, bz + BLOCKSIZE, bx + BLOCKSIZE, by, bz + BLOCKSIZE, bx + BLOCKSIZE, by + BLOCKSIZE, bz + BLOCKSIZE, bx, by + BLOCKSIZE, bz + BLOCKSIZE };
	glVertex3iv(vbo[0]);
	glVertex3iv(vbo[1]);
	glVertex3iv(vbo[2]);
	glVertex3iv(vbo[3]);
}
directList block::isChosen(int octant) {
	threeVect tmpPos = playerEye.getPos();
	twoVect tmpAng = playerEye.getAng();
	if (tmpAng.theta > 3 * PIE / 2)tmpAng.theta -= 3 * PIE / 2;
	if (tmpAng.theta > PIE)tmpAng.theta -= PIE;
	if (tmpAng.theta > PIE / 2)tmpAng.theta -= PIE / 2;
	if (tmpAng.fy > PIE / 2)tmpAng.fy  = PIE- tmpAng.fy;
	GLfloat deltaX = bx - tmpPos.x, deltaY = by - tmpPos.y, deltaZ = bz - tmpPos.z;
	GLfloat tmp;
	switch (octant) {
	case 1://Done.
		if (bx == tmpPos.x || by == tmpPos.y || bz == tmpPos.z || bx + BLOCKSIZE == tmpPos.x || by + BLOCKSIZE == tmpPos.y || bz + BLOCKSIZE == tmpPos.z)return NONE;
		tmp = tmpPos.y + deltaZ / (sin(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.x + deltaZ / tan(tmpAng.theta);
		if (tmp > bx + BLOCKSIZE)return NONE;
		tmp = tmpPos.y + deltaX / (cos(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.z + deltaX*tan(tmpAng.theta);
		if (tmp > bz + BLOCKSIZE)return NONE;
		tmp = tmpPos.z + deltaY*tan(tmpAng.fy)*sin(tmpAng.theta);
		if (tmp > bz + BLOCKSIZE)return NONE;
		tmp = tmpPos.x + deltaY*tan(tmpAng.fy)*cos(tmpAng.theta);
		if (tmp > bx + BLOCKSIZE)return NONE;
		tmp = tmpPos.x + deltaZ / tan(tmpAng.theta);
		if (tmp > bx) {
			tmp = tmpPos.y + deltaZ / (sin(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by)return BACK;
			else return DOWN;
		}
		else {
			tmp = tmpPos.y + deltaX / (cos(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by)return LEFT;
			else return DOWN;
		}
		break;
	case 2://Done.
		if (bx == tmpPos.x || by == tmpPos.y || bz == tmpPos.z || bx + BLOCKSIZE == tmpPos.x || by + BLOCKSIZE == tmpPos.y || bz + BLOCKSIZE == tmpPos.z)return NONE;
		tmp = tmpPos.y + deltaZ / (cos(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.x - deltaZ*tan(tmpAng.theta);
		if (tmp < bx)return NONE;
		tmp = tmpPos.y + (-deltaX-BLOCKSIZE) / (sin(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.z + (-deltaX - BLOCKSIZE) / tan(tmpAng.theta);
		if (tmp > bz + BLOCKSIZE)return NONE;
		tmp = tmpPos.z + deltaY*tan(tmpAng.fy)*cos(tmpAng.theta);
		if (tmp > bz + BLOCKSIZE)return NONE;
		tmp = tmpPos.x - deltaY*tan(tmpAng.fy)*sin(tmpAng.theta);
		if (tmp < bx)return NONE;
		tmp = tmpPos.x - deltaZ *tan(tmpAng.theta);
		if (tmp < bx + BLOCKSIZE) {
			tmp = tmpPos.y + deltaZ / (cos(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by)return BACK;
			else return DOWN;
		}
		else {
			tmp = tmpPos.y + (-deltaX - BLOCKSIZE) / (sin(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by)return RIGHT;
			else return DOWN;
		}
		break;
	case 5://Done.
		if (bx == tmpPos.x || by == tmpPos.y || bz == tmpPos.z || bx + BLOCKSIZE == tmpPos.x || by + BLOCKSIZE == tmpPos.y || bz + BLOCKSIZE == tmpPos.z)return NONE;
		tmp = tmpPos.y - (deltaZ + BLOCKSIZE) / (sin(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by+BLOCKSIZE)return NONE;
		tmp = tmpPos.x + deltaZ / tan(tmpAng.theta);
		if (tmp > bx + BLOCKSIZE)return NONE;
		tmp = tmpPos.y - (deltaX + BLOCKSIZE) / (cos(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by+BLOCKSIZE)return NONE;
		tmp = tmpPos.z + deltaX*tan(tmpAng.theta);
		if (tmp > bz + BLOCKSIZE)return NONE;
		tmp = tmpPos.z - deltaY*tan(tmpAng.fy)*sin(tmpAng.theta);
		if (tmp < bz)return NONE;
		tmp = tmpPos.x - deltaY*tan(tmpAng.fy)*cos(tmpAng.theta);
		if (tmp < bx)return NONE;
		tmp = tmpPos.x + deltaZ / tan(tmpAng.theta);
		if (tmp > bx) {
			tmp = tmpPos.y - deltaZ / (sin(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by + BLOCKSIZE)return UP;
			else return BACK;
		}
		else {
			tmp = tmpPos.y - deltaX / (cos(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by + BLOCKSIZE)return UP;
			else return LEFT;
		}
		break;
	case 6://Done.
		if (bx == tmpPos.x || by == tmpPos.y || bz == tmpPos.z || bx + BLOCKSIZE == tmpPos.x || by + BLOCKSIZE == tmpPos.y || bz + BLOCKSIZE == tmpPos.z)return NONE;
		tmp = tmpPos.y - (deltaZ + BLOCKSIZE) / (cos(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.x - deltaZ * tan(tmpAng.theta);
		if (tmp < bx)return NONE;
		tmp = tmpPos.y + deltaX / (sin(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.z + (-deltaX - BLOCKSIZE) / tan(tmpAng.theta);
		if (tmp > bz + BLOCKSIZE)return NONE;
		tmp = tmpPos.z - deltaY*tan(tmpAng.fy)*cos(tmpAng.theta);
		if (tmp < bz)return NONE;
		tmp = tmpPos.x + deltaY*tan(tmpAng.fy)*sin(tmpAng.theta);
		if (tmp > bx + BLOCKSIZE)return NONE;
		tmp = tmpPos.x - deltaZ*tan(tmpAng.theta);
		if (tmp < bx + BLOCKSIZE) {
			tmp = tmpPos.y - deltaZ / (cos(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by + BLOCKSIZE)return UP;
			else return BACK;
		}
		else {
			tmp = tmpPos.y - (-deltaX - BLOCKSIZE) / (sin(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by + BLOCKSIZE)return UP;
			else return RIGHT;
		}
		break;
	case 4://Done.
		if (bx == tmpPos.x || by == tmpPos.y || bz == tmpPos.z || bx + BLOCKSIZE == tmpPos.x || by + BLOCKSIZE == tmpPos.y || bz + BLOCKSIZE == tmpPos.z)return NONE;
		tmp = tmpPos.y + (-deltaZ - BLOCKSIZE) / (cos(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.x + (-deltaZ - BLOCKSIZE)*tan(tmpAng.theta);
		if (tmp > bx + BLOCKSIZE)return NONE;
		tmp = tmpPos.y + deltaX / (sin(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.z - deltaX / tan(tmpAng.theta);
		if (tmp < bz)return NONE;
		tmp = tmpPos.z - deltaY*tan(tmpAng.fy)*cos(tmpAng.theta);
		if (tmp < bz)return NONE;
		tmp = tmpPos.x + deltaY*tan(tmpAng.fy)*sin(tmpAng.theta);
		if (tmp > bx +BLOCKSIZE)return NONE;
		tmp = tmpPos.x + (-deltaZ - BLOCKSIZE)*tan(tmpAng.theta);
		if (tmp > bx) {
			tmp = tmpPos.y + (-deltaZ - BLOCKSIZE) / (cos(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by)return FRONT;
			else return DOWN;
		}
		else {
			tmp = tmpPos.y + deltaX / (sin(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by)return LEFT;
			else return DOWN;
		}
		break;
	case 3://Done.
		if (bx == tmpPos.x || by == tmpPos.y || bz == tmpPos.z || bx + BLOCKSIZE == tmpPos.x || by + BLOCKSIZE == tmpPos.y || bz + BLOCKSIZE == tmpPos.z)return NONE;
		tmp = tmpPos.y + (-deltaZ - BLOCKSIZE) / (sin(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.x - (-deltaZ - BLOCKSIZE) / tan(tmpAng.theta);
		if (tmp < bx)return NONE;
		tmp = tmpPos.y + (-deltaX-BLOCKSIZE) / (cos(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.z - (-deltaX - BLOCKSIZE) * tan(tmpAng.theta);
		if (tmp < bz)return NONE;
		tmp = tmpPos.z - deltaY*tan(tmpAng.fy)*sin(tmpAng.theta);
		if (tmp < bz)return NONE;
		tmp = tmpPos.x - deltaY*tan(tmpAng.fy)*cos(tmpAng.theta);
		if (tmp < bx)return NONE;
		tmp = tmpPos.x - (-deltaZ - BLOCKSIZE) / tan(tmpAng.theta);
		if (tmp < bx + BLOCKSIZE) {
			tmp = tmpPos.y + (-deltaZ - BLOCKSIZE) / (sin(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by)return FRONT;
			else return DOWN;
		}
		else {
			tmp = tmpPos.y + (-deltaX - BLOCKSIZE) / (cos(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by)return RIGHT;
			else return DOWN;
		}
		break;
	case 8://Done.
		if (bx == tmpPos.x || by == tmpPos.y || bz == tmpPos.z || bx + BLOCKSIZE == tmpPos.x || by + BLOCKSIZE == tmpPos.y || bz + BLOCKSIZE == tmpPos.z)return NONE;
		tmp = tmpPos.y + deltaZ / (cos(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.x + (-deltaZ - BLOCKSIZE)*tan(tmpAng.theta);
		if (tmp > bx + BLOCKSIZE)return NONE;
		tmp = tmpPos.y - (deltaX + BLOCKSIZE) / (sin(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.z - deltaX / tan(tmpAng.theta);
		if (tmp < bz)return NONE;
		tmp = tmpPos.z + deltaY*tan(tmpAng.fy)*cos(tmpAng.theta);
		if (tmp > bz + BLOCKSIZE)return NONE;
		tmp = tmpPos.x - deltaY*tan(tmpAng.fy)*sin(tmpAng.theta);
		if (tmp < bx)return NONE;
		tmp = tmpPos.x + (-deltaZ - BLOCKSIZE)*tan(tmpAng.theta);
		if (tmp > bx) {
			tmp = tmpPos.y - (-deltaZ - BLOCKSIZE) / (cos(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by + BLOCKSIZE)return UP;
			else return FRONT;
		}
		else {
			tmp = tmpPos.y - deltaX / (sin(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by + BLOCKSIZE)return UP;
			else return LEFT;
		}
		break;
	case 7://Done.
		if (bx == tmpPos.x || by == tmpPos.y || bz == tmpPos.z || bx + BLOCKSIZE == tmpPos.x || by + BLOCKSIZE == tmpPos.y || bz + BLOCKSIZE == tmpPos.z)return NONE;
		tmp = tmpPos.y + deltaZ / (sin(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.x - (-deltaZ - BLOCKSIZE) / tan(tmpAng.theta);
		if (tmp < bx)return NONE;
		tmp = tmpPos.y + deltaX/ (cos(tmpAng.theta)*tan(tmpAng.fy));
		if (tmp > by + BLOCKSIZE)return NONE;
		tmp = tmpPos.z - (-deltaX - BLOCKSIZE)*tan(tmpAng.theta);
		if (tmp < bz)return NONE;
		tmp = tmpPos.z + deltaY*tan(tmpAng.fy)*sin(tmpAng.theta);
		if (tmp > bz + BLOCKSIZE)return NONE;
		tmp = tmpPos.x + deltaY*tan(tmpAng.fy)*cos(tmpAng.theta);
		if (tmp > bx +BLOCKSIZE)return NONE;
		tmp = tmpPos.x - (-deltaZ - BLOCKSIZE) / tan(tmpAng.theta);
		if (tmp < bx + BLOCKSIZE) {
			tmp = tmpPos.y - (-deltaZ - BLOCKSIZE) / (sin(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by + BLOCKSIZE)return UP;
			else return FRONT;
		}
		else {
			tmp = tmpPos.y - (-deltaX - BLOCKSIZE) / (cos(tmpAng.theta)*tan(tmpAng.fy));
			if (tmp > by + BLOCKSIZE)return UP;
			else return RIGHT;
		}
		break;
	}
	return NONE;
}
