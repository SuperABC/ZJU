#include <atlimage.h>
#include <iostream>
#include <string>

CImage *loadJpg(const char *fileName);
LPWSTR widen(const char *src);
void operate(CImage *pic);
double clamp(double val, double ceil, double floor);
void dilate(int i, int j);
void erode(int i, int j);

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
	int gray[256] = { 0 };
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
		}
	}

	int threshold, maxth = 0, maxi = 0;
	int nb, nf, ub, uf;
	//second traverse to find the best threshold.
	for (threshold = 1; threshold < 256; threshold++) {
		nb = 0;
		nf = 0;
		for (int i = 0; i < threshold; i++) {
			nb += gray[i];
			ub += i*gray[i];
		}
		for (int i = threshold; i < 256; i++) {
			nf += gray[i];
			uf += i*gray[i];
		}
		ub /= threshold;
		uf /= (256 - threshold);
		int tmp = nb*nf*(ub - uf)*(ub - uf);
		if (tmp > maxth) {
			maxth = tmp;
			maxi = threshold;
		}
	}
	threshold = maxi;

	//third traverse to write the picture.
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			if (picmem[pos] >= threshold) {
				picmem[pos] = 1;
				*tmp = char(255);
				*(tmp + 2) = char(255);
				*(tmp + 1) = char(255);
			}
			else {
				picmem[pos] = 0;
				*tmp = char(0);
				*(tmp + 2) = char(0);
				*(tmp + 1) = char(0);
			}
		}
	}
	pic->Save(widen("bin.jpg"));

	//forth traverse to dilate and close the picture.
	memcpy(piccpy, picmem, picWidth*picHeight * sizeof(char));
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			if (picmem[pos] == 1)dilate(i, j);
		}
	}
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			if (picmem[pos]) {
				picmem[pos] = 1;
				*tmp = char(255);
				*(tmp + 2) = char(255);
				*(tmp + 1) = char(255);
			}
			else {
				picmem[pos] = 0;
				*tmp = char(0);
				*(tmp + 2) = char(0);
				*(tmp + 1) = char(0);
			}
		}
	}
	pic->Save(widen("dilation.jpg"));
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			if (picmem[pos] == 1)erode(i, j);
		}
	}
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			if (picmem[pos] == 1) {
				picmem[pos] = 1;
				*tmp = char(255);
				*(tmp + 2) = char(255);
				*(tmp + 1) = char(255);
			}
			else {
				picmem[pos] = 0;
				*tmp = char(0);
				*(tmp + 2) = char(0);
				*(tmp + 1) = char(0);
			}
		}
	}
	pic->Save(widen("close.jpg"));

	//fifth traverse to erode the picture.
	memcpy(picmem, piccpy, picWidth*picHeight * sizeof(char));
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			if (picmem[pos] == 1)erode(i, j);
		}
	}
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			if (picmem[pos] == 1) {
				picmem[pos] = 1;
				*tmp = char(255);
				*(tmp + 2) = char(255);
				*(tmp + 1) = char(255);
			}
			else {
				picmem[pos] = 0;
				*tmp = char(0);
				*(tmp + 2) = char(0);
				*(tmp + 1) = char(0);
			}
		}
	}
	pic->Save(widen("erosion.jpg"));
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			if (picmem[pos] == 1)dilate(i, j);
		}
	}
	for (int i = 0; i < picWidth; i++) {
		for (int j = 0; j < picHeight; j++) {
			int pos = (j*picWidth + i);
			byte *tmp = (byte*)pic->GetPixelAddress(i, j);
			if (picmem[pos]) {
				picmem[pos] = 1;
				*tmp = char(255);
				*(tmp + 2) = char(255);
				*(tmp + 1) = char(255);
			}
			else {
				picmem[pos] = 0;
				*tmp = char(0);
				*(tmp + 2) = char(0);
				*(tmp + 1) = char(0);
			}
		}
	}
	pic->Save(widen("open.jpg"));
}

void dilate(int i, int j) {
	int pos = (j*picWidth + i);
	if (i > 0)picmem[pos-1] = 2;
	if (j > 0)picmem[pos-picWidth] = 2;
	if (i < picWidth - 1)picmem[pos+1] = 2;
	if (j < picHeight - 1)picmem[pos+picWidth] = 2;
}
void erode(int i, int j) {
	int pos = (j*picWidth + i);
	if (i > 0 && picmem[pos-1] == 0)picmem[pos] = 2;
	if (i < picWidth - 1 && picmem[pos+1] == 0)picmem[pos] = 2;
	if (j > 0 && picmem[pos-picWidth] == 0)picmem[pos] = 2;
	if (j < picHeight - 1 && picmem[pos+picWidth] == 0)picmem[pos] = 2;
}