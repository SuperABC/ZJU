#include "eye.h"
#include "world.h"
extern block *wholeWorld[2 * MAXBORDER][MAXHEIGHT][2 * MAXBORDER];
extern playingGlobal playingGV;
eye::eye() {
	Upv_x = 0;
	Upv_y = 1;
	Upv_z = 0;
}
void eye::setEye(GLfloat x, GLfloat y, GLfloat z, GLfloat theta, GLfloat fy) {
	Pos_x = x;
	Pos_y = y;
	Pos_z = z;
	Ang_theta = theta;
	Ang_fy = fy;
	At_x = sin(fy)*cos(theta);
	At_y = cos(fy);
	At_z = sin(fy)*sin(theta);
}
void eye::setEye(GLfloat x, GLfloat y, GLfloat z, GLfloat ax, GLfloat ay, GLfloat az) {
	Pos_x = x;
	Pos_y = y;
	Pos_z = z;
	At_x = ax;
	At_y = ay;
	At_z = az;
	Ang_fy = acos(At_y);
	if (At_z > 0)Ang_theta = acos(At_x);
	else Ang_theta = (float)(2 * PIE - acos(At_x));
}
void eye::lookTo() {
	gluLookAt(Pos_x, Pos_y, Pos_z, Pos_x + At_x, Pos_y + At_y, Pos_z + At_z, Upv_x, Upv_y, Upv_z);
}
void eye::moveEye(GLfloat fb, GLfloat lr, GLfloat ud, bool conf) {
	if (!conf) {
		Pos_x += At_x * fb + At_z*lr;
		Pos_y += ud;
		Pos_z += At_z * fb - At_x*lr;
	}
	else {
		Pos_x += At_x * fb + At_z*lr;
		Pos_z += At_z * fb - At_x*lr;
		GLfloat ppx = Pos_x, ppz = Pos_z;
		GLfloat testx = Pos_x;
		GLfloat testz = Pos_z;
		Pos_x = testx;
		Pos_z = testz;
		if (!playingGV.crouch) {
			if (wholeWorld[(int)(Pos_x + FIGUREWIDTH / 2) / BLOCKSIZE][(int)Pos_y / BLOCKSIZE][(int)ppz / BLOCKSIZE] || wholeWorld[(int)(Pos_x + FIGUREWIDTH / 2) / BLOCKSIZE][(int)Pos_y / BLOCKSIZE - 1][(int)ppz / BLOCKSIZE]) {
				Pos_x = (int)(Pos_x + FIGUREWIDTH / 2) / BLOCKSIZE*BLOCKSIZE - FIGUREWIDTH / 2;
				playingGV.speedX = 0;
			}
			else if (wholeWorld[(int)(Pos_x - FIGUREWIDTH / 2) / BLOCKSIZE][(int)Pos_y / BLOCKSIZE][(int)ppz / BLOCKSIZE] || wholeWorld[(int)(Pos_x - FIGUREWIDTH / 2) / BLOCKSIZE][(int)Pos_y / BLOCKSIZE - 1][(int)ppz / BLOCKSIZE]) {
				Pos_x = (int)(Pos_x - FIGUREWIDTH / 2) / BLOCKSIZE*BLOCKSIZE + BLOCKSIZE + FIGUREWIDTH / 2;
				playingGV.speedX = 0;
			}
			if (wholeWorld[(int)ppx / BLOCKSIZE][(int)Pos_y / BLOCKSIZE][(int)(Pos_z + FIGUREWIDTH / 2) / BLOCKSIZE] || wholeWorld[(int)ppx / BLOCKSIZE][(int)Pos_y / BLOCKSIZE - 1][(int)(Pos_z + FIGUREWIDTH / 2) / BLOCKSIZE]) {
				Pos_z = (int)(Pos_z + FIGUREWIDTH / 2) / BLOCKSIZE*BLOCKSIZE - FIGUREWIDTH / 2;
				playingGV.speedZ = 0;
			}
			else if (wholeWorld[(int)ppx / BLOCKSIZE][(int)Pos_y / BLOCKSIZE][(int)(Pos_z - FIGUREWIDTH / 2) / BLOCKSIZE] || wholeWorld[(int)ppx / BLOCKSIZE][(int)Pos_y / BLOCKSIZE - 1][(int)(Pos_z - FIGUREWIDTH / 2) / BLOCKSIZE]) {
				Pos_z = (int)(Pos_z - FIGUREWIDTH / 2) / BLOCKSIZE*BLOCKSIZE + BLOCKSIZE + FIGUREWIDTH / 2;
				playingGV.speedZ = 0;
			}
			Pos_y += ud;
			if (wholeWorld[(int)Pos_x / BLOCKSIZE][(int)Pos_y / BLOCKSIZE][(int)Pos_z / BLOCKSIZE]) {
				Pos_y = (int)Pos_y / BLOCKSIZE * BLOCKSIZE - 10;
			}
			if (wholeWorld[(int)Pos_x / BLOCKSIZE][(int)(Pos_y - EYEHEIGHT) / BLOCKSIZE][(int)Pos_z / BLOCKSIZE]) {
				Pos_y = (int)(Pos_y - EYEHEIGHT + BLOCKSIZE) / BLOCKSIZE * BLOCKSIZE + EYEHEIGHT;
			}
		}
		else {
			if (wholeWorld[(int)(Pos_x + FIGUREWIDTH / 2) / BLOCKSIZE][(int)Pos_y / BLOCKSIZE][(int)ppz / BLOCKSIZE]) {
				Pos_x = (int)(Pos_x + FIGUREWIDTH / 2) / BLOCKSIZE*BLOCKSIZE - FIGUREWIDTH / 2;
				playingGV.speedX = 0;
			}
			else if (wholeWorld[(int)(Pos_x - FIGUREWIDTH / 2) / BLOCKSIZE][(int)Pos_y / BLOCKSIZE][(int)ppz / BLOCKSIZE]) {
				Pos_x = (int)(Pos_x - FIGUREWIDTH / 2) / BLOCKSIZE*BLOCKSIZE + BLOCKSIZE + FIGUREWIDTH / 2;
				playingGV.speedX = 0;
			}
			if (wholeWorld[(int)ppx / BLOCKSIZE][(int)Pos_y / BLOCKSIZE][(int)(Pos_z + FIGUREWIDTH / 2) / BLOCKSIZE]) {
				Pos_z = (int)(Pos_z + FIGUREWIDTH / 2) / BLOCKSIZE*BLOCKSIZE - FIGUREWIDTH / 2;
				playingGV.speedZ = 0;
			}
			else if (wholeWorld[(int)ppx / BLOCKSIZE][(int)Pos_y / BLOCKSIZE][(int)(Pos_z - FIGUREWIDTH / 2) / BLOCKSIZE]) {
				Pos_z = (int)(Pos_z - FIGUREWIDTH / 2) / BLOCKSIZE*BLOCKSIZE + BLOCKSIZE + FIGUREWIDTH / 2;
				playingGV.speedZ = 0;
			}
			Pos_y += ud;
			if (wholeWorld[(int)Pos_x / BLOCKSIZE][(int)Pos_y / BLOCKSIZE][(int)Pos_z / BLOCKSIZE]) {
				Pos_y = (int)Pos_y / BLOCKSIZE * BLOCKSIZE - 10;
			}
			if (wholeWorld[(int)Pos_x / BLOCKSIZE][(int)(Pos_y - CROUCHHEIGHT) / BLOCKSIZE][(int)Pos_z / BLOCKSIZE]) {
				Pos_y = (int)(Pos_y - CROUCHHEIGHT + BLOCKSIZE) / BLOCKSIZE * BLOCKSIZE + CROUCHHEIGHT;
			}
		}
	}
}
void eye::rotateEye(GLfloat theta, GLfloat fy) {
	Ang_theta += theta;
	if (Ang_theta > 2 * PIE)Ang_theta -= 2 * PIE;
	if (Ang_theta < 0)Ang_theta += 2 * PIE;
	Ang_fy += fy;
	if (Ang_fy < 0.01)Ang_fy = 0.01;
	if (Ang_fy > PIE-0.01)Ang_fy = PIE-0.01;
	At_x =sin(Ang_fy)*cos(Ang_theta);
	At_y =cos(Ang_fy);
	At_z =sin(Ang_fy)*sin(Ang_theta);
}
struct threeVect eye::getPos() {
	threeVect rt = { Pos_x, Pos_y, Pos_z };
	return rt;
}
struct threeVect eye::getAt() {
	threeVect rt = { At_x, At_y, At_z };
	return rt;
}
struct twoVect eye::getAng() {
	twoVect rt = { Ang_theta, Ang_fy };
	return rt;
}
struct threeVect eye::getUp() {
	threeVect rt = { Upv_x, Upv_y, Upv_z };
	return rt;
};
