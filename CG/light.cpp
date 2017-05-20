#include "light.h"
#include "environment.h"
extern planet sun, moon;
extern dt timeClock;
light::light(int d) {
	index = d;
	on = FALSE;
	switch (d) {
	case 0:
		lightPos[0] = 2000;
		lightPos[1] = 2000;
		lightPos[2] = 500;
		lightPos[3] = 1;
		lightAmb[0] = 0.2;
		lightAmb[1] = 0.2;
		lightAmb[2] = 0.2;
		lightAmb[3] = 1;
		lightDif[0] = 1;
		lightDif[1] = 1;
		lightDif[2] = 1;
		lightDif[3] = 1;
		lightSpc[0] = 1;
		lightSpc[1] = 1;
		lightSpc[2] = 1;
		lightSpc[3] = 1;
		break;
	case 1:
		lightPos[0] = (sun.Dist / 3 + MAXBORDER*BLOCKSIZE - 50001)*cos(sun.Ang / 180 * PIE);
		lightPos[1] = (sun.Dist / 3 + MAXBORDER*BLOCKSIZE - 50001)*sin(sun.Ang / 180 * PIE) + GROUNDLEVEL* BLOCKSIZE;
		lightPos[2] = MAXBORDER*BLOCKSIZE;
		lightPos[3] = 0;
		lightAmb[0] = 0.3;
		lightAmb[1] = 0.3;
		lightAmb[2] = 0.3;
		lightAmb[3] = 1;
		lightDif[0] = 0.5;
		lightDif[1] = 0.5;
		lightDif[2] = 0.5;
		lightDif[3] = 1;
		lightSpc[0] = 1;
		lightSpc[1] = 1;
		lightSpc[2] = 1;
		lightSpc[3] = 1;
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	}
}
void light::enable(bool newl) {
	on = TRUE;
	switch (index) {
	case 0:
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpc);
		if (!newl)return;
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		break;
	case 1:
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
		glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDif);
		glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpc);
		if (!newl)return;
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
		glEnable(GL_COLOR_MATERIAL);
		break;
	}
}
void light::disable() {
	on = FALSE;
	switch (index) {
	case 0:
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		break;
	case 1:
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHTING);
		break;
	}
}
void light::update() {
	switch (index) {
	case 0:
		break;
	case 1:
		lightPos[0] = (sun.Dist / 3 + MAXBORDER*BLOCKSIZE - 50001)*cos(sun.Ang / 180 * PIE);
		lightPos[1] = (sun.Dist / 3 + MAXBORDER*BLOCKSIZE - 50001)*sin(sun.Ang / 180 * PIE) + GROUNDLEVEL* BLOCKSIZE;
		lightPos[2] = MAXBORDER*BLOCKSIZE;
		lightPos[3] = 0;
		if (timeClock.inRange(5, 0, 0, 7, 0, 0)) {
			lightAmb[0] += 0.2 / 720;
			lightAmb[1] += 0.2 / 720;
			lightAmb[2] += 0.2 / 720;
			lightAmb[3] = 1;
			lightDif[0] += 0.5 / 720;
			lightDif[1] += 0.5 / 720;
			lightDif[2] += 0.5 / 720;
			lightDif[3] = 1;
		}
		if (timeClock.inRange(17, 0, 0, 19, 0, 0)) {
			lightAmb[0] -= 0.2 / 720;
			lightAmb[1] -= 0.2 / 720;
			lightAmb[2] -= 0.2 / 720;
			lightAmb[3] = 1;
			lightDif[0] -= 0.5 / 720;
			lightDif[1] -= 0.5 / 720;
			lightDif[2] -= 0.5 / 720;
			lightDif[3] = 1;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	}
}
