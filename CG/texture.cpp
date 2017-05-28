#include "texture.h"

/*list:
1: The front picture of the starting table;
2: The front picture of selecting mode;
3: The side picture of the starting table;
4: The front picture of the helping table;
5: The side picture of the helping table;
6; The front picture of the archive table;
7: The side picture of the archive table;
*/

GLuint texName;
AUX_RGBImageRec *bmp[TOTALPIC];
CImage *jpg[TOTALPIC];
AUX_RGBImageRec *loadBmp(char *fileName, GLuint tex) {
	FILE *File = NULL;
	int rt;
	LPWSTR rs;
	if (!fileName) {
		return NULL;
	}
	File = fopen(fileName, "r");
	if (File) {
		fclose(File);
		rt = MultiByteToWideChar(CP_ACP, 0, fileName, -1, NULL, 0);
		rs = (LPWSTR)malloc(rt * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, fileName, -1, rs, rt * sizeof(wchar_t));
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(tex, &texName);
		glBindTexture(GL_TEXTURE_2D, texName);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		return auxDIBImageLoad(rs);
	}
	return NULL;
}
CImage *loadJpg(char *fileName, GLuint tex) {
	int rt;
	LPWSTR rs;
	unsigned char *pData = NULL;
	CImage *src = new CImage;
	if (!fileName) {
		return NULL;
	}
	rt = MultiByteToWideChar(CP_ACP, 0, fileName, -1, NULL, 0);
	rs = (LPWSTR)malloc(rt * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, fileName, -1, rs, rt * sizeof(wchar_t));
	HRESULT hr = src->Load(rs);
	if (!SUCCEEDED(hr)) {
		return NULL;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(tex, &texName);
	if (src->GetPitch()<0)pData = (unsigned char *)src->GetBits() + (src->GetPitch()*(src->GetHeight() - 1));
	else pData = (unsigned char *)src->GetBits();
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, src->GetWidth(), src->GetHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pData);
	return src;
}
void allBMP() {
	bmp[0] = loadBmp("123.bmp", 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp[0]->sizeX, bmp[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, bmp[0]->data);
}
void allJPG() {
	jpg[0] = loadJpg("Source\\7824837668.src", 1);
	jpg[1] = loadJpg("Source\\782487433.src", 2);
	jpg[2] = loadJpg("Source\\1502466736664.src", 4);
	jpg[3] = loadJpg("Source\\435737668.src", 8);
	jpg[4] = loadJpg("Source\\43577433.src", 16);
	jpg[5] = loadJpg("Source\\272448337668.src", 32);
	jpg[6] = loadJpg("Source\\27244837433.src", 64);
}
void glPicBegin(GLfloat param, GLuint tex) {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, param);
	glBindTexture(GL_TEXTURE_2D, tex);
}
void glPicEnd() {
	glDisable(GL_TEXTURE_2D);
}
