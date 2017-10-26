#include <atlimage.h>
#include <iostream>
#include <string>

CImage *loadJpg(const char *fileName);
LPWSTR widen(const char *src);
void operate(CImage *pic);
double clamp(double val, double ceil, double floor);

int picWidth;
int picHeight;
byte *picmem;
byte *piccpy;

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
	int gray[256] = { 0 }, max = 0;
	picWidth = pic->GetWidth();
	picHeight = pic->GetHeight();
	picmem = (byte*)malloc(picWidth*picHeight * sizeof(char));
	piccpy = (byte*)malloc(picWidth*picHeight * sizeof(char));

	//first traverse to get the gray message.
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			picmem[pos] = byte(*tmp*0.299f + *(tmp + 1)*0.587f + *(tmp + 2)*0.114f);
			gray[int(*tmp*0.299f + *(tmp + 1)*0.587f + *(tmp + 2)*0.114f)]++;
			if (max < picmem[pos])max = picmem[pos];
			*tmp = char(picmem[pos]);
			*(tmp + 2) = char(picmem[pos]);
			*(tmp + 1) = char(picmem[pos]);
		}
	}
	pic->Save(widen("gray.jpg"));

	//second traverse to log the picture.
	char res;
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			res = 255 * log2(float(picmem[pos]) / 255 + 1) / log2(float(max) / 255 + 1);
			*tmp = res;
			*(tmp + 2) = res;
			*(tmp + 1) = res;
		}
	}
	pic->Save(widen("log.jpg"));

	float histo[256] = { 0 };
	for (int i = 0; i < 255; i++) {
		histo[i] += float(gray[i])/(picWidth*picHeight);
	}
	for (int i = 1; i < 256; i++) {
		histo[i] += histo[i - 1];
	}
	for (int i = 0; i < 255; i++) {
		histo[i] *= 255;
	}
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			picmem[pos] = histo[picmem[pos]];
			*tmp = char(picmem[pos]);
			*(tmp + 2) = char(picmem[pos]);
			*(tmp + 1) = char(picmem[pos]);
		}
	}
	pic->Save(widen("histo.jpg"));
}