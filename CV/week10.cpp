#include <atlimage.h>
#include <iostream>
#include <string>
#include <cmath>

CImage *loadJpg(const char *fileName);
LPWSTR widen(const char *src);
void operate(CImage *pic);

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
void operate(CImage *pic) {

	picWidth = pic->GetWidth();
	picHeight = pic->GetHeight();
	picmem = (byte*)malloc(picWidth*picHeight * 3 * sizeof(char));
	memset(picmem, 0, picWidth*picHeight * 3 * sizeof(char));

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

	//bilateral
	float weight;
	float sum;

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
					sum = 0;
					weight = 0;
					for (int y = 0; y < 3; y++) {
						for (int x = 0; x < 3; x++) {
							weight += exp(-((x - 1)*(x - 1) + (y - 1)*(y - 1)) -
								((picmem[pos + z] - picmem[pos + ((y - 1)*picWidth + x - 1) * 3 + z])*
								(picmem[pos + z] - picmem[pos + ((y - 1)*picWidth + x - 1) * 3 + z])) / 1024);
							sum += picmem[pos + ((y - 1)*picWidth + x - 1) * 3 + z] * 
								exp(-((x - 1)*(x - 1) + (y - 1)*(y - 1)) -
								((picmem[pos + z] - picmem[pos + ((y - 1)*picWidth + x - 1) * 3 + z])*
									(picmem[pos + z] - picmem[pos + ((y - 1)*picWidth + x - 1) * 3 + z])) / 1024);
						}
					}
					tmp[z] = sum / weight;
				}
			}
		}
	}
	pic->Save(widen("Bilateral.jpg"));
}