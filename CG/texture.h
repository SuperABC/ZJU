#pragma once
#include "main.h"
#define TOTALPIC 100
AUX_RGBImageRec *loadBmp(char *fileName, GLuint tex);
CImage *loadJpg(char *fileName, GLuint tex);
void allBMP();
void allJPG();
void glPicBegin(GLfloat param, GLuint tex);
void glPicEnd();
