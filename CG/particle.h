#pragma once
#include "main.h"

enum particleType {
	RAIN,
	BLAST,
	CLOUD,
	FIRE,
	SNOW,
	FOUTAIN
};

class particle {
public:
	GLfloat life = 0;
	GLfloat fade;
	GLfloat RGB[3];

	GLfloat pos[3], vel[3], acc[3];
};
class generator {
protected:
	GLenum particleType;
	GLuint particleCount;
	particle *particles;
	GLuint colorCount;
	GLuint(*colorList)[3];

	GLfloat baseX, baseY, baseZ;
	GLfloat particleLife;
	GLfloat particleSize;
public:
	virtual void particleInit(int i) = 0;
	virtual void particleUpdate(int i) = 0;
	void particleDisplay(int i);
	void particleLoop();
};
class rain : public generator {
public:
	rain(GLfloat baseX, GLfloat baseY, GLfloat baseZ);
	~rain();
	virtual void particleInit(int i);
	virtual void particleUpdate(int i);
};
class blast : public generator {
public:
	blast(GLfloat baseX, GLfloat baseY, GLfloat baseZ);
	~blast();
	virtual void particleInit(int i);
	virtual void particleUpdate(int i);
};
class systemp {
private:
	int generCount;
	generator ** geners;
public:
	systemp(int *xpos, int *ypos, int *zpos, int SYSTYPE, int n);
	~systemp();
	void systemLoop();
};