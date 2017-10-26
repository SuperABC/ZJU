#include <atlimage.h>
#include <iostream>
#include <string>

#include "week7.h"

CImage *loadJpg(const char *fileName);
LPWSTR widen(const char *src);
void operate(CImage *pic);
double clamp(double val, double ceil, double floor);

int picWidth;
int picHeight;
byte *picmem;

int main() {
	CImage *pic = new CImage();
	std::string fn;
	std::cin >> fn;
	pic = loadJpg(fn.c_str());
	if (pic) {
		operate(pic);
	}
	else std::cout << "File not found!" << std::endl;
}
CImage *loadJpg(const char *fileName) {
	unsigned char *pData = NULL;
	CImage *src = new CImage;
	if (!fileName)return NULL;
	HRESULT hr = src->Load(widen(fileName));
	if (!SUCCEEDED(hr))return NULL;
	return src;
}
LPWSTR widen(const char *src) {
	int rt;
	LPWSTR rs;
	rt = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
	rs = (LPWSTR)malloc(rt * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, src, -1, rs, rt * sizeof(wchar_t));
	return rs;
}
double clamp(double val, double ceil, double floor) {
	if (val > ceil)return ceil;
	if (val < floor)return floor;
	return val;
}
void operate(CImage *pic) {

	picWidth = pic->GetWidth();
	picHeight = pic->GetHeight();
	picmem = (byte*)malloc(picWidth*picHeight*3 * sizeof(char));
	
	vector tmpPos;
	int tmpDelta;

	//copy
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			int pos = (j*picWidth + i) * 3;
			picmem[pos++] = *(tmp++);
			picmem[pos++] = *(tmp++);
			picmem[pos++] = *(tmp++);
		}
	}
	
	//translate.
	matrix transMat = matrix::translate(200, 200);
	for (int i = 960; i < 2880; i++) {
		for (int j = 540; j < 1620; j++) {
			tmpPos = transMat*vector(i, j, 1);
			if (tmpPos[0] < 0 || tmpPos[0] >= picWidth || tmpPos[1] < 0 || tmpPos[1] >= picHeight)continue;
			byte *tmp = (byte*)pic->GetPixelAddress(tmpPos.raster()[0], tmpPos.raster()[1]);
			tmpDelta = (j*picWidth + i) * 3;
			*(tmp++) = picmem[tmpDelta++];
			*(tmp++) = picmem[tmpDelta++];
			*(tmp++) = picmem[tmpDelta++];
		}
	}
	pic->Save(widen("traslate.jpg"));

	//restore
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			int pos = (j*picWidth + i) * 3;
			*(tmp++) = picmem[pos++];
			*(tmp++) = picmem[pos++];
			*(tmp++) = picmem[pos++];
		}
	}

	//scale.
	matrix scaleMat = matrix::scale(0.4, 0.8)*matrix::translate(-960, -540);
	for (int i = 960; i < 2880; i++) {
		for (int j = 540; j < 1620; j++) {
			tmpPos = scaleMat*vector(i, j, 1);
			if (tmpPos[0] < 0 || tmpPos[0] >= picWidth || tmpPos[1] < 0 || tmpPos[1] >= picHeight)continue;
			byte *tmp = (byte*)pic->GetPixelAddress(tmpPos.raster()[0], tmpPos.raster()[1]);
			tmpDelta = (j*picWidth + i) * 3;
			*(tmp++) = picmem[tmpDelta++];
			*(tmp++) = picmem[tmpDelta++];
			*(tmp++) = picmem[tmpDelta++];
		}
	}
	pic->Save(widen("scale.jpg"));

	//restore
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			int pos = (j*picWidth + i) * 3;
			*(tmp++) = picmem[pos++];
			*(tmp++) = picmem[pos++];
			*(tmp++) = picmem[pos++];
		}
	}

	//rotate.
	matrix rotateMat = matrix::translate(960, 540)*matrix::rotate(PIE/4)*matrix::translate(-960, -540);
	for (int i = 960; i < 2880; i++) {
		for (int j = 540; j < 1620; j++) {
			tmpPos = rotateMat*vector(i, j, 1);
			if (tmpPos[0] < 0 || tmpPos[0] >= picWidth || tmpPos[1] < 0 || tmpPos[1] >= picHeight)continue;
			byte *tmp = (byte*)pic->GetPixelAddress(tmpPos.raster()[0], tmpPos.raster()[1]);
			tmpDelta = (j*picWidth + i) * 3;
			*(tmp++) = picmem[tmpDelta++];
			*(tmp++) = picmem[tmpDelta++];
			*(tmp++) = picmem[tmpDelta++];
		}
	}
	pic->Save(widen("rotate.jpg"));

	//restore
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			int pos = (j*picWidth + i) * 3;
			*(tmp++) = picmem[pos++];
			*(tmp++) = picmem[pos++];
			*(tmp++) = picmem[pos++];
		}
	}
	
	//mirror.
	matrix mirrorMat = matrix::scale(-1, 1)*matrix::translate(-picWidth, 0);
	for (int i = 960; i < 2880; i++) {
		for (int j = 540; j < 1620; j++) {
			tmpPos = mirrorMat*vector(i, j, 1);
			if (tmpPos[0] < 0 || tmpPos[0] >= picWidth || tmpPos[1] < 0 || tmpPos[1] >= picHeight)continue;
			byte *tmp = (byte*)pic->GetPixelAddress(tmpPos.raster()[0], tmpPos.raster()[1]);
			tmpDelta = (j*picWidth + i) * 3;
			*(tmp++) = picmem[tmpDelta++];
			*(tmp++) = picmem[tmpDelta++];
			*(tmp++) = picmem[tmpDelta++];
		}
	}
	pic->Save(widen("mirror.jpg"));

	//restore
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			int pos = (j*picWidth + i) * 3;
			*(tmp++) = picmem[pos++];
			*(tmp++) = picmem[pos++];
			*(tmp++) = picmem[pos++];
		}
	}
	
	//shear.
	matrix shearMat = matrix::shear(0.4, 0.2)*matrix::translate(-960, -540);
	for (int i = 960; i < 2880; i++) {
		for (int j = 540; j < 1620; j++) {
			tmpPos = shearMat*vector(i, j, 1);
			if (tmpPos[0] < 0 || tmpPos[0] >= picWidth || tmpPos[1] < 0 || tmpPos[1] >= picHeight)continue;
			byte *tmp = (byte*)pic->GetPixelAddress(tmpPos.raster()[0], tmpPos.raster()[1]);
			tmpDelta = (j*picWidth + i) * 3;
			*(tmp++) = picmem[tmpDelta++];
			*(tmp++) = picmem[tmpDelta++];
			*(tmp++) = picmem[tmpDelta++];
		}
	}
	pic->Save(widen("shear.jpg"));

}