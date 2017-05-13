#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *roll[64] = {
	"3140102257", "张佳玥",
	"3140103297", "卢奕州",
	"3140103839", "杨臣",
	"3140103344", "董骁",
	"3140103641", "黄文廷",
	"3150104423", "诸嘉琦",
	"3130102388", "刘耕铭",
	"3140100674", "孙明琦",
	"3140100685", "陈昱彤",
	"3140100799", "游超",
	"3140102245", "郑杭捷",
	"3140102442", "张扬光",
	"3140102493", "沈旭东",
	"3140103543", "许晟杰",
	"3140103603", "王扬立",
	"3140103666", "傅瑶",
	"3140103770", "车嘉泰",
	"3140103892", "冯晗",
	"3140104023", "叶培峰",
	"3140104327", "孙天炜",
	"3140104945", "程帅",
	"3140105015", "李博",
	"3150102408", "陈鉴",
	"3150104497", "朱瑞昇",
	"3130000116", "王钦",
	"3150102769", "陈建瑜",
	"3150103787", "叶小刚",
	"3140105754", "陈源",
	"3140105303", "李嘉宁",
	"3140102315", "傅郅",
	"3140103996", "李陈浩文",
	"3140105028", "高颂" };

char *encrypt(char *num, unsigned char *name);
int main() {
	char *num = (char *)malloc(20 * sizeof(char));
	unsigned char *name = (unsigned char *)malloc(20 * sizeof(char));
	char *key;
	int tmp;
	memset(name, 0, 20 * sizeof(char));
	printf("Input the student number:");
	scanf("%s", num);
	//printf("Input the name:");
	//scanf("%s", name);
	for (tmp = 0; tmp < 32; tmp++) {
		if (strcmp(roll[2 * tmp], num) == 0) {
			strcpy(name, roll[2 * tmp + 1]);
			break;
		}
	}
	key = encrypt(num, name);
	printf("%s\n", key);
	return 0;
}
char *encrypt(char *num, unsigned char *name) {
	char *ret = (char *)malloc(20 * sizeof(char));
	int i = 0;
	while (num[i]) {
		if (name[i] & 1)ret[i] = num[i] - 0x30 - 0xBF;
		else ret[i] = (num[i] - 0x30 + 1) * 2 - 0xBF;
		i++;
	}
	ret[i] = '\0';
	return ret;
}