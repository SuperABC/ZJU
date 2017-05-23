#include "particle.h"
#include "world.h"
#include "eye.h"
#define CALCDIST(x1, y1, z1, x2, y2, z2) (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2)))
extern block *wholeWorld[2 * MAXBORDER][MAXHEIGHT][2 * MAXBORDER];
extern eye playerEye;
const int rainColor = 10, blastColor = 10;
GLuint colorArray0[rainColor][3] = {
	50,50,100,
	50,50,255,
	50,60,255,
	50,70,255,
	50,85,255,
	50,110,255,
	50,130,255,
	50,150,255,
	50,160,255,
	50,180,255
};
GLuint colorArray1[blastColor][3] = {
	255,20,0,
	255,50,0,
	255,80,0,
	255,100,0,
	255,120,0,
	255,150,0,
	255,200,0,
	255,220,0,
	255,250,0,
	255,255,0
};

void generator::particleDisplay(int i) {
	if (particles[i].life <= 0)return;
	glColor4f(particles[i].RGB[0], particles[i].RGB[1], particles[i].RGB[2], particles[i].life / particleLife);
	glPointSize(particleSize);
	switch (particleType) {
	case RAIN:
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex3f(particles[i].pos[0], particles[i].pos[1], particles[i].pos[2]);
		glVertex3f(particles[i].pos[0], particles[i].pos[1] + 2*particleSize, particles[i].pos[2]);
		glEnd();
		break;
	case BLAST:
		glBegin(GL_POINTS);
		glVertex3f(particles[i].pos[0], particles[i].pos[1], particles[i].pos[2]);
		glEnd();
		break;
	}
}
void generator::particleLoop() {
	for (int i = 0; i < particleCount; i++) {
		particleDisplay(i);
		particleUpdate(i);
	}
	switch(particleType){
	case RAIN:
		threeVect base = playerEye.getPos();
		baseX = base.x;
		baseZ = base.z;
		break;
	case BLAST:
		break;
	}
}

rain::rain(GLfloat baseX, GLfloat baseY, GLfloat baseZ) {
	this->baseX = baseX;
	this->baseY = baseY;
	this->baseZ = baseZ;
	particleType = RAIN;
	particleCount = 4000;
	particles = new particle[particleCount];
	colorList = colorArray0;
	colorCount = rainColor;
	particleSize = 3;
	particleLife = 10;
	for (int i = 0; i < particleCount; i++)particleInit(i);
}
rain::~rain() {
	delete[] particles;
}
void rain::particleInit(int i) {
	float xRange = 2000;
	float yRange = 100;
	float zRange = 2000;
	particles[i].life = 0.5 + particleLife*(rand() % 50) * 0.01f;
	particles[i].fade = 0.002f;
	particles[i].RGB[0] = colorList[colorCount - 1][0] / 255.0f;
	particles[i].RGB[1] = colorList[colorCount - 1][1] / 255.0f;
	particles[i].RGB[2] = colorList[colorCount - 1][2] / 255.0f;

	particles[i].pos[0] = (float)(xRange / 2 - xRange*(rand() % 100)*0.01) + baseX;
	particles[i].pos[1] = (float)(yRange / 2 - xRange*(rand() % 100)*0.01) + baseY;
	particles[i].pos[2] = (float)(zRange / 2 - zRange*(rand() % 100)*0.01) + baseZ;
	particles[i].vel[0] = 0;
	particles[i].vel[1] = -80;
	particles[i].vel[2] = 0;
	particles[i].acc[0] = 0;
	particles[i].acc[1] = 0;
	particles[i].acc[2] = 0;
}
void rain::particleUpdate(int i) {
	if (particles[i].life < 0.0f || wholeWorld[(int)particles[i].pos[0] / BLOCKSIZE][(int)particles[i].pos[1] / BLOCKSIZE][(int)particles[i].pos[2] / BLOCKSIZE])particleInit(i);
	else {
		particles[i].pos[0] += particles[i].vel[0];
		particles[i].pos[1] += particles[i].vel[1];
		particles[i].pos[2] += particles[i].vel[2];
		particles[i].vel[0] += particles[i].acc[0];
		particles[i].vel[1] += particles[i].acc[1];
		particles[i].vel[2] += particles[i].acc[2];
		particles[i].life -= particles[i].fade;
		GLuint colorPos = (GLuint)(particles[i].life / particleLife * (colorCount - 1));
		particles[i].RGB[0] = colorList[colorPos][0] / 255.0f;
		particles[i].RGB[1] = colorList[colorPos][1] / 255.0f;
		particles[i].RGB[2] = colorList[colorPos][2] / 255.0f;
	}
}

blast::blast(GLfloat baseX, GLfloat baseY, GLfloat baseZ) {
	threeVect tmpPos = playerEye.getPos();
	this->baseX = baseX;
	this->baseY = baseY;
	this->baseZ = baseZ;
	particleType = BLAST;
	particleCount = 400;
	particles = new particle[particleCount];
	colorList = colorArray1;
	colorCount = rainColor;
	GLfloat dist = CALCDIST(baseX, baseY, baseZ, tmpPos.x, tmpPos.y, tmpPos.z);
	if(dist > 1000)particleSize = 5;
	else if (dist > 500)particleSize = 8;
	else if (dist > 200)particleSize = 12;
	else particleSize = 15;
	particleLife = 10;
	for (int i = 0; i < particleCount; i++)particleInit(i);
}
blast::~blast() {
	delete[] particles;
}
void blast::particleInit(int i) {
	float xRange = 40;
	float yRange = 40;
	float zRange = 40;
	particles[i].life = 0.5 + particleLife*(rand() % 50) * 0.01f;
	particles[i].fade = 0.2f;
	particles[i].RGB[0] = colorList[colorCount - 1][0] / 255.0f;
	particles[i].RGB[1] = colorList[colorCount - 1][1] / 255.0f;
	particles[i].RGB[2] = colorList[colorCount - 1][2] / 255.0f;

	particles[i].pos[0] = (float)(xRange / 2 - xRange*(rand() % 100)*0.01) + baseX;
	particles[i].pos[1] = (float)(yRange / 2 - xRange*(rand() % 100)*0.01) + baseY;
	particles[i].pos[2] = (float)(zRange / 2 - zRange*(rand() % 100)*0.01) + baseZ;
	particles[i].vel[0] = (particles[i].pos[0] - baseX);
	particles[i].vel[1] = (particles[i].pos[1] - baseY);
	particles[i].vel[2] = (particles[i].pos[2] - baseZ);
	particles[i].acc[0] = -(particles[i].pos[0] - baseX) / 40;
	particles[i].acc[1] = -(particles[i].pos[1] - baseY) / 40;
	particles[i].acc[2] = -(particles[i].pos[2] - baseZ) / 40;
}
void blast::particleUpdate(int i) {
	if (particles[i].life < 0)return;
	particles[i].pos[0] += particles[i].vel[0];
	particles[i].pos[1] += particles[i].vel[1];
	particles[i].pos[2] += particles[i].vel[2];
	particles[i].vel[0] += particles[i].acc[0];
	particles[i].vel[1] += particles[i].acc[1];
	particles[i].vel[2] += particles[i].acc[2];
	particles[i].life -= particles[i].fade;
	GLuint colorPos = (GLuint)(particles[i].life / particleLife * (colorCount - 1));
	particles[i].RGB[0] = colorList[colorPos][0] / 255.0f;
	particles[i].RGB[1] = colorList[colorPos][1] / 255.0f;
	particles[i].RGB[2] = colorList[colorPos][2] / 255.0f;
}

systemp::systemp(int *xpos, int *ypos, int *zpos, int SYSTYPE, int n) {
	generCount = n;
	switch (SYSTYPE) {
	case RAIN:
		geners = (generator**)new generator*[n];
		for (int i = 0; i<n; i++)geners[i] = new rain((float)xpos[i], (float)ypos[i], (float)zpos[i]);
		break;
	case BLAST:
		geners = (generator**)new generator*[n];
		for (int i = 0; i<n; i++)geners[i] = new blast((float)xpos[i], (float)ypos[i], (float)zpos[i]);
		break;
	}
}
systemp::~systemp() {
	for (int i = 0; i<generCount; i++)
		delete geners[i];
	delete[] geners;
}
void systemp::systemLoop() {
	for (int i = 0; i<generCount; i++)geners[i]->particleLoop();
}