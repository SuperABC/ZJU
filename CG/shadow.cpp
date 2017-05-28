#include "shadow.h"
#include "eye.h"
extern eye playerEye;
void initShadow() {

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_Q);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);
}
void transposeMatrix(GLfloat m[16]) {
	GLfloat  tmp;
#define Swap(a, b) tmp = a; a = b; b = tmp
	Swap(m[1], m[4]);
	Swap(m[2], m[8]);
	Swap(m[3], m[12]);
	Swap(m[6], m[9]);
	Swap(m[7], m[13]);
	Swap(m[11], m[14]);
#undef Swap
}
void generateShadow() {
	GLint viewPort[4];

	glGetIntegerv(GL_VIEWPORT, viewPort);
	glViewport(0, 0, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	playerEye.lookTo();
	sightLimit();

	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0,
		SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, 0);
	glViewport(viewPort[0], viewPort[1], viewPort[2], viewPort[3]);
}
void generateDepth() {
	GLfloat tmpMatrix[16];
	GLfloat lightPos[4];
	glGetLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.5, 0.5, 0.0);
	glScalef(0.5, 0.5, 1.0);
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	gluLookAt(lightPos[0], lightPos[1], lightPos[2], MAXBORDER*BLOCKSIZE, MAXBORDER*BLOCKSIZE, GROUNDLEVEL*BLOCKSIZE, 0, 1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, tmpMatrix);
	glPopMatrix();

	transposeMatrix(tmpMatrix);

	glTexGenfv(GL_S, GL_OBJECT_PLANE, &tmpMatrix[0]);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, &tmpMatrix[4]);
	glTexGenfv(GL_R, GL_OBJECT_PLANE, &tmpMatrix[8]);
	glTexGenfv(GL_Q, GL_OBJECT_PLANE, &tmpMatrix[12]);
}
