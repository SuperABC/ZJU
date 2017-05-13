#include "file.h"
#include "world.h"
#include "eye.h"
#include <fstream>
//file format
/*
head:
	"world file"(file type)20hb + "%sd%sd%sd%sd%sd%sd"(explored space x, y, z)24hb + class player(player information)50hb + class eye(eye information)48hb
	+ "%sd"(card number)4hb + class time(time information)24hb + class enemy[20](enemy information)400hb + class gun[6](gun information)192hb + check(check intact)2hb
	+ ex(extra space)400hb;
body:
	"%d%1f%1f%1f"(type, R, G, B)480*40*480hb + check(check intact)2hb;
*/
using std::string;
using std::ofstream;
using std::ifstream;
using std::ios;
extern block *wholeWorld[2 * MAXBORDER][MAXHEIGHT][2 * MAXBORDER];
extern eye playerEye;
extern fileGlobal fileGV;
bool saveData(int num) {
	string name;
	char *none = (char *)malloc(1);
	char *tmp = (char *)malloc(1);
	*none = 0;
	switch (num) {
	case 0:
		name = "Source\\66736.dat";
		break;
	case 1:
		name = "Source\\28632641.dat";
		break;
	case 2:
		name = "Source\\28632642.dat";
		break;
	case 3:
		name = "Source\\28632643.dat";
		break;
	case 4:
		name = "Source\\28632644.dat";
		break;
	case 5:
		name = "Source\\28632645.dat";
		break;
	case 6:
		name = "Source\\28632646.dat";
		break;
	default:
		return FALSE;
	}
	ofstream fout(name, ios::binary);
	fout << "world file";
	fout << (short)fileGV.explored.a1;
	fout.seekp(0xE);
	fout << (short)fileGV.explored.a2;
	fout.seekp(0x12);
	fout << (short)fileGV.explored.b1;
	fout.seekp(0x16);
	fout << (short)fileGV.explored.b2;
	fout.seekp(0x1A);
	fout << (short)fileGV.explored.c1;
	fout.seekp(0x1E);
	fout << (short)fileGV.explored.c2;
	for (int i = 0; i < 25; i++) {
		fout << (char)0;
	}
	threeVect tmpPos = playerEye.getPos();
	twoVect tmpAng = playerEye.getAng();
	threeVect tmpAt = playerEye.getAt();
	threeVect tmpUp = playerEye.getUp();
	fout << tmpPos.x << tmpPos.y << tmpPos.z << tmpAng.theta << tmpAng.fy << tmpAt.x << tmpAt.y << tmpAt.z << tmpUp.x << tmpUp.y << tmpUp.z << (GLfloat)0;
	fout.seekp(0x400);
	/*for (int i = 0; i < 2 * MAXBORDER; i++) {
		for (int j = 0; j < MAXHEIGHT; j++) {
			for (int k = 0; k < 2*MAXBORDER; k++) {
				fout.write(wholeWorld[i][j][k] != NULL ? (char*)&wholeWorld[i][j][k]->type : none, 1);
				*tmp = wholeWorld[i][j][k] != NULL ? 10*wholeWorld[i][j][k]->RGB[0] : 0;
				fout.write(tmp, 1);
				*tmp = wholeWorld[i][j][k] != NULL ? 10 * wholeWorld[i][j][k]->RGB[1] : 0;
				fout.write(tmp, 1);
				*tmp = wholeWorld[i][j][k] != NULL ? 10 * wholeWorld[i][j][k]->RGB[2] : 0;
				fout.write(tmp, 1);
			}
		}
	}*/
	for (int i = fileGV.explored.a1; i <= fileGV.explored.a2; i++) {
		for (int j = fileGV.explored.b1; j <= fileGV.explored.b2; j++) {
			fout.seekp(0x400 + i * 8 * MAXBORDER*MAXHEIGHT + j * 8 * MAXBORDER + 4 * fileGV.explored.c1);
			for (int k = fileGV.explored.c1; k <= fileGV.explored.c2; k++) {
				fout.write(wholeWorld[i][j][k] != NULL ? (char*)&wholeWorld[i][j][k]->type : none, 1);
				*tmp = wholeWorld[i][j][k] != NULL ? 10 * wholeWorld[i][j][k]->RGB[0] : 0;
				fout.write(tmp, 1);
				*tmp = wholeWorld[i][j][k] != NULL ? 10 * wholeWorld[i][j][k]->RGB[1] : 0;
				fout.write(tmp, 1);
				*tmp = wholeWorld[i][j][k] != NULL ? 10 * wholeWorld[i][j][k]->RGB[2] : 0;
				fout.write(tmp, 1);
			}
		}
	}
	fout.seekp(0x400 + 16 * MAXBORDER*MAXHEIGHT * MAXBORDER);
	fout << (char)0;
	fout.close();
	return TRUE;
}
bool loadData(int num) {
	string name;
	char *none = (char *)malloc(1);
	GLfloat tmpfl;
	GLshort a1, a2, b1, b2, c1, c2;
	char tmpch;
	*none = 0;
	switch (num) {
	case 0:
		name = "Source\\66736.dat";
		break;
	case 1:
		name = "Source\\28632641.dat";
		break;
	case 2:
		name = "Source\\28632642.dat";
		break;
	case 3:
		name = "Source\\28632643.dat";
		break;
	case 4:
		name = "Source\\28632644.dat";
		break;
	case 5:
		name = "Source\\28632645.dat";
		break;
	case 6:
		name = "Source\\28632646.dat";
		break;
	default:
		return FALSE;
	}
	ifstream fin(name, ios::binary);
	if (fin.is_open() == FALSE)
		return FALSE;
	fin.seekg(0xA);
	fin >> a1;
	fin.seekg(0xE);
	fin >> a2;
	fin.seekg(0x12);
	fin >> b1;
	fin.seekg(0x16);
	fin >> b2;
	fin.seekg(0x1A);
	fin >> c1;
	fin.seekg(0x1E);
	fin >> c2;
	for (int i = a1; i <= a2; i++) {
		for (int j = b1; j <= b2; j++) {
			fin.seekg(0x400 + i * 8 * MAXBORDER*MAXHEIGHT + j * 8 * MAXBORDER + 4 * c1);
			for (int k = c1; k <= c2; k++) {
				fin.read(&tmpch, 1);
				if (tmpch) {
					if (!wholeWorld[i][j][k])wholeWorld[i][j][k] = new block(i, j, k);
					wholeWorld[i][j][k]->buildBlock(tmpch);
					fin.read(&tmpch, 1);
					wholeWorld[i][j][k]->RGB[0] = (float)tmpch / 10;
					fin.read(&tmpch, 1);
					wholeWorld[i][j][k]->RGB[1] = (float)tmpch / 10;
					fin.read(&tmpch, 1);
					wholeWorld[i][j][k]->RGB[2] = (float)tmpch / 10;
				}
				else {
					fin.read(&tmpch, 1);
					fin.read(&tmpch, 1);
					fin.read(&tmpch, 1);
				}
			}
		}
	}
	fileGV.explored.a1 = a1;
	fileGV.explored.a2 = a2;
	fileGV.explored.b1 = b1;
	fileGV.explored.b2 = b2;
	fileGV.explored.c1 = c1;
	fileGV.explored.c2 = c2;
	fin.close();
	fileGV.isLoaded = num;
	return TRUE;
}
