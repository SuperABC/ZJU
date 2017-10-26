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
	picmem = (byte*)malloc(picWidth*picHeight * 3 * sizeof(char));
	memset(picmem, 0, picWidth*picHeight * 3 * sizeof(char));

	int mean;

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

	//mean
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			int pos = (j*picWidth + i) * 3;
			if (i == 0 || j == 0 || i == picWidth - 1 || j == picHeight - 1) {
				*(tmp++) = picmem[pos++];
				*(tmp++) = picmem[pos++];
				*(tmp++) = picmem[pos++];
			}
			else {
				for (int z = 0; z < 3; z++) {
					mean = 0;
					for (int y = 0; y < 3; y++) {
						for (int x = 0; x < 3; x++) {
							mean += picmem[pos + ((y - 1)*picWidth + x - 1) * 3 + z];
						}
					}
					tmp[z] = mean / 9;;
				}
			}
		}
	}
	pic->Save(widen("Mean.jpg"));

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

	//Laplacian
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			int pos = (j*picWidth + i) * 3;
			*(tmp++) = picmem[pos++];
			*(tmp++) = picmem[pos++];
			*(tmp++) = picmem[pos++];
			 if (i != 0 && j != 0 && i != picWidth - 1 && j != picHeight - 1) {
				for (int z = 0; z < 3; z++) {
					mean = 0;
					mean += picmem[pos - 3 + z];
					mean += picmem[pos + 3 + z];
					mean += picmem[pos - picWidth * 3 + z];
					mean += picmem[pos + picWidth * 3 + z];
					mean -= 4 * picmem[pos + z];
					tmp[z] += mean / 9;
				}
			}
		}
	}
	pic->Save(widen("Laplacian.jpg"));
}