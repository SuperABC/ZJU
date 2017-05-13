#pragma once
#include "main.h"
class eye {
private:
	GLfloat Pos_x, Pos_y, Pos_z;
	GLfloat Ang_theta, Ang_fy;
	GLfloat At_x, At_y, At_z;
	GLfloat Upv_x, Upv_y, Upv_z;
	void updateEye();
public:
	eye();
	void setEye(GLfloat x, GLfloat y, GLfloat z, GLfloat theta, GLfloat fy);
	void setEye(GLfloat x, GLfloat y, GLfloat z, GLfloat ax, GLfloat ay, GLfloat az);
	void moveEye(GLfloat fb, GLfloat lr, GLfloat ud, bool conf = FALSE);
	void rotateEye(GLfloat theta, GLfloat fy);
	void rotateUp(GLfloat bf, GLfloat lr);
	void lookTo();
	struct threeVect getPos();
	struct threeVect getAt();
	struct twoVect getAng();
	struct threeVect getUp();
};
