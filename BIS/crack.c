#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *roll[64] = {
	"3140102257", "�żѫh",
	"3140103297", "¬����",
	"3140103839", "�",
	"3140103344", "����",
	"3140103641", "����͢",
	"3150104423", "�����",
	"3130102388", "������",
	"3140100674", "������",
	"3140100685", "����ͮ",
	"3140100799", "�γ�",
	"3140102245", "֣����",
	"3140102442", "�����",
	"3140102493", "����",
	"3140103543", "���ɽ�",
	"3140103603", "������",
	"3140103666", "����",
	"3140103770", "����̩",
	"3140103892", "����",
	"3140104023", "Ҷ���",
	"3140104327", "�����",
	"3140104945", "��˧",
	"3140105015", "�",
	"3150102408", "�¼�",
	"3150104497", "����N",
	"3130000116", "����",
	"3150102769", "�½��",
	"3150103787", "ҶС��",
	"3140105754", "��Դ",
	"3140105303", "�����",
	"3140102315", "��ۤ",
	"3140103996", "��º���",
	"3140105028", "����" };

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