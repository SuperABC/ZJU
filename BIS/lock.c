#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char shell[] = { 0x50, 0x53, 0x51, 0x52, 0x0e, 0x1f, 0xbe, 0x00, 0x00, 0xe8, 0x00, 0x00, 0x5b, 0x81, 0xeb, 0x0C,
	0x00, 0xb9, 0x00, 0x00, 0x06, 0x8c, 0xc5, 0x83, 0xc5, 0x10, 0x8e, 0xc5, 0x26, 0x8a, 0x04, 0x34,
	0x44, 0x26, 0x88, 0x04, 0x07, 0x46, 0xe2, 0xec, 0x8b, 0x8f, 0x69, 0x00, 0x83, 0xf9, 0x00, 0x74,
	0x20, 0x8b, 0xb7, 0x7b, 0x00, 0x8d, 0xb0, 0x63, 0x00, 0x8b, 0x3c, 0x8b, 0x54, 0x02, 0x06, 0x8c,
	0xc5, 0x83, 0xc5, 0x10, 0x03, 0xd5, 0x8e, 0xc2, 0x26, 0x01, 0x2d, 0x07, 0x83, 0xc6, 0x04, 0xe2,
	0xe8, 0x5a, 0x59, 0x5b, 0x58, 0x8b, 0xc5, 0x05, 0x00, 0x00, 0x50, 0xb8, 0x00, 0x00, 0x50, 0xcb };

static char *help = "Usage:\nInput \"lock source.exe destiny.exe\" to lock the source to destiny.\n";
static char *miss = "Oops! The source file not found!\n";
static char *error = "There may be something wrong with the source exe file, please check.";

long int lock(long int length, unsigned char *data);

int main(int args, char *argv[]) {
	FILE *fsrc, *fdst;
	char *srcName = (char *)malloc(0x100), *dstName = (char *)malloc(0x100);

	long int len;
	unsigned char *p;
	unsigned char *locked;

	if (args == 1) {
		printf("Input the source file name:\n");
		scanf("%s", srcName);
		printf("Input the destiny file name:\n");
		scanf("%s", dstName);
	}
	else if (args == 2) {
		strcpy(srcName, argv[1]);
		printf("Input the destiny file name:\n");
		scanf("%s", dstName);
	}
	else if (args == 3) {
		strcpy(srcName, argv[1]);
		strcpy(dstName, argv[2]);
	}
	else {
		printf("%s", help);
		return -1;
	}

	fsrc = fopen(srcName, "rb");
	if (fsrc == NULL) {
		printf("%s", miss);
		return -1;
	}
	fseek(fsrc, 0, SEEK_END);
	len = ftell(fsrc);
	fseek(fsrc, 0, SEEK_SET);
	p = (unsigned char *)malloc(2 * len + 0x100);
	fread(p, 1, len, fsrc);
	fclose(fsrc);

	len = lock(len, p);
	if (len == 0) {
		printf("%s", error);
		return -1;
	}

	fdst = fopen(dstName, "wb");
	fwrite(p, 1, len, fdst);
	fclose(fdst);
	return 0;
}

long int lock(long int length, unsigned char *data) {
	int headLength, dsLength, i;
	unsigned char *headData;
	
	unsigned char *start = data;

	//校验exe
	if (*data++ != 0x4D)return 0;
	if (*data++ != 0x5A)return 0;
	data += 0x06;

	//复制文件头
	headLength = (data[0] + data[1] * 0x10) * 0x10;
	headData = (unsigned char *)malloc(headLength);
	data -= 0x08;
	memcpy(headData, data, headLength);
	data += 0x06;

	//重定向位数清零
	*(unsigned short *)data = 0;
	data += 0x0E;

	//更改起始IP
	dsLength = *(unsigned short *)data + *(unsigned short *)(data + 2) * 0x10;
	*(unsigned short *)data += (length-headLength-dsLength);
	data -= 0x12;

	//更改文件总长
	*data = (length + headLength + sizeof(shell)) % 0x200;
	data += 2;
	*data = (length + headLength + sizeof(shell) + 0x200 - 1) / 0x200;
	data += (headLength - 4);

	//加密文件
	for (i = 0; i < length - headLength; i++) {
		*data++ ^= 0x44;
	}

	//连接shell代码
	memcpy(data, shell, sizeof(shell));
	data += 0x12;

	//设置解密循环次数
	*(unsigned short *)data = length - headLength;
	data += 0x46;

	//设置返回地址
	*(unsigned short *)data = (headLength + dsLength) / 0x10 - headLength / 0x10;
	data += 0x04;
	*(unsigned short *)data = (headLength + dsLength) % 0x10;
	data += sizeof(shell) - 0x59;

	//连接文件头
	memcpy(data, headData, headLength);

	return length + headLength + sizeof(shell);
}