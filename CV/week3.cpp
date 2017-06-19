#include <atlimage.h>
#include <iostream>
#include <string>

CImage *loadJpg(const char *fileName);
LPWSTR widen(const char *src);
void operate(CImage *pic);
double clamp(double val, double ceil, double floor);

float *picmem;

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
	int picWidth = pic->GetWidth();
	int picHeight = pic->GetHeight();
	float max = 0.f, min = 255.f;
	picmem = (float*)malloc(picWidth*picHeight * 3 * sizeof(char));
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			int pos = (j*picWidth + i) * 3;
			picmem[pos] = *tmp*0.299f + *(tmp + 1)*0.587f + *(tmp + 2)*0.114f;
			picmem[pos + 1] = (*(tmp + 2) - picmem[pos])*0.492f;
			picmem[pos + 2] = (*tmp - picmem[pos])*0.877f;
			if (picmem[pos] > max)
				max = picmem[pos];
			if (picmem[pos] < min)
				min = picmem[pos];
		}
	}
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			int pos = (j*picWidth + i) * 3;
			picmem[pos] = (picmem[pos] - min) * 255 / (max - min);
			*tmp = clamp(picmem[pos], 255, 0);
			*(tmp + 1) = clamp(picmem[pos], 255, 0);
			*(tmp + 2) = clamp(picmem[pos], 255, 0);
		}
	}
	pic->Save(widen("gray.jpg"));
	int delta = 0;
	std::cin >> delta;
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			int pos = (j*picWidth + i) * 3;
			picmem[pos] = clamp(picmem[pos]+delta, 255, 0);
			*tmp = clamp(picmem[pos] + picmem[pos + 2] * 1.140f, 255, 0);
			*(tmp + 2) = clamp(picmem[pos] + picmem[pos + 1] * 2.032f, 255, 0);
			*(tmp + 1) = clamp(picmem[pos] - picmem[pos + 1] * 0.394f - picmem[pos + 2] *0.581f, 255, 0);
		}
	}
	pic->Save(widen("color.jpg"));
}