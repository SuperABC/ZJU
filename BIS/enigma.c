#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define ROTATE(x) (x = ((x)-'A'+1)%26+'A')

const char plugBoard[] = "ZNVDEFTYKUILPBOMWRXGJCQSHA";
									 //ABCDEFGHIJKLMNOPQRSTUVWXYZ
const char rotorTable[6][27] = {
	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
	"BDFHJLCPRTXVZNYEIWGAKMUSQO",
	"VZBRGITYUPSDNHLXAWMJQOFECK",
	"AJPCZWRLFBDKOTYUQGENHXMIVS",
	"TAGBPCSDQEUFVNZHYIXJWLRKOM",
	"QCYLXWENFTZOSMVJUDKGIARPHB"
  //ABCDEFGHIJKLMNOPQRSTUVWXYZ
};
const char reflector[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
									//ABCDEFGHIJKLMNOPQRSTUVWXYZ
char messageKey[3];

int findAnswer(char *plain) {
    while(*(plain+6)) {
		if (*plain == 'H'&&*(plain + 1) == 'I'&&*(plain + 2) == 'T'
			&&*(plain + 3) == 'L'&&*(plain + 4) == 'E' && *(plain + 5) == 'R')
			return 1;
		plain++;
    }
	return 0;
}
void rotateRotor(char *rotor1, char *rotor2, char *rotor3) {
	ROTATE(*rotor1);
	if (*rotor1 == 'F') {
		ROTATE(*rotor2);
		if (*rotor2 == 'W')
			ROTATE(*rotor3);
	}
	else if (*rotor2 == 'V') {
		ROTATE(*rotor2);
		ROTATE(*rotor3);
	}
}
char r1pos(char c, int delta) {
	c = (c - 'A' + delta + 26) % 26;
	c = rotorTable[0][c];
	return (c - 'A' - delta + 26) % 26 + 'A';
}
char r2pos(char c, int delta) {
	c = (c - 'A' + delta + 26) % 26;
	c = rotorTable[1][c];
	return (c - 'A' - delta + 26) % 26 + 'A';
}
char r3pos(char c, int delta) {
	c = (c - 'A' + delta + 26) % 26;
	c = rotorTable[2][c];
	return (c - 'A' - delta + 26) % 26 + 'A';
}
char r1neg(char c, int delta) {
	c = (c - 'A' + delta + 26) % 26;
	c = rotorTable[3][c];
	return (c - 'A' - delta + 26) % 26 + 'A';
}
char r2neg(char c, int delta) {
	c = (c - 'A' + delta + 26) % 26;
	c = rotorTable[4][c];
	return (c - 'A' - delta + 26) % 26 + 'A';
}
char r3neg(char c, int delta) {
	c = (c - 'A' + delta + 26) % 26;
	c = rotorTable[5][c];
    return (c - 'A' - delta + 26) % 26 + 'A';
}
char passRotor(char c, int delta1, int delta2, int delta3) {
    c = plugBoard[c - 'A'];
    c = r1pos(c, delta1);
    c = r2pos(c, delta2);
    c = r3pos(c, delta3);
	c = reflector[c - 'A'];
    c = r3neg(c, delta3);
    c = r2neg(c, delta2);
    c = r1neg(c, delta1);
    c = plugBoard[c - 'A'];
    return c;
}
char *enigma_encrypt_decrypt(char *p) {
    char rotor1,rotor2,rotor3;
    int delta1, delta2, delta3, i = 0;
	char *ret = (char *)malloc(1024 * sizeof(char));
	rotor1 = messageKey[0];
	rotor2 = messageKey[1];
	rotor3 = messageKey[2];
	while (*p != '\0') {
		rotateRotor(&rotor1, &rotor2, &rotor3);
		delta1 = rotor1 - 'B';
		delta2 = rotor2 - 'E';
		delta3 = rotor3 - 'W';
		ret[i++] = passRotor(*(p++), delta1, delta2, delta3);
	}
	ret[i] = '\0';
	return ret;
}

int main(int argc, char* argv[]) {
    char *cypherText = (char *)malloc(1024*sizeof(char));
	char *plainText = (char *)malloc(1024 * sizeof(char));
    scanf("%s", cypherText);
	for (messageKey[2] = 'A'; messageKey[2] <= 'Z'; messageKey[2]++)
		for (messageKey[1] = 'A'; messageKey[1] <= 'Z'; messageKey[1]++)
			for (messageKey[0] = 'A'; messageKey[0] <= 'Z'; messageKey[0]++) {
				strcpy(plainText, enigma_encrypt_decrypt(cypherText));
				if (findAnswer(plainText)) {
					printf("MessageKey=%c%c%c\n", messageKey[2], messageKey[1], messageKey[0]);
					printf("PlainText=%s\n", plainText);
					system("pause");
					return 0;
				}
			}
	system("pause");
    return 0;
}
