#pragma once
#include "main.h"
#define SHADOW_MAP_WIDTH      256
#define SHADOW_MAP_HEIGHT     256
void initShadow();
void transposeMatrix(GLfloat m[16]);
void generateShadow();
void generateDepth();
