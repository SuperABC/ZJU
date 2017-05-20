#include "obj.h"
using namespace std;
void objModel::parse(const char *filename) {
	string s;
	ifstream fin(filename);
	if (!fin)
		return;
	while (fin >> s) {
		switch (*s.c_str()) {
		case 'v':
			vertex v;
			fin >> v.x >> v.y >> v.z;
			this->vetexes.push_back(v);
			break;
		case 'g':
			break;
		case 'f':
			face f;
			fin >> f.v1 >> f.v2 >> f.v3;
			faces.push_back(f);
			break;
		}
	}
}
void objModel::draw() {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < faces.size(); i++) {
		vertex v1 = vetexes[faces[i].v1 - 1];
		vertex v2 = vetexes[faces[i].v2 - 1];
		vertex v3 = vetexes[faces[i].v3 - 1];
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
	}
	glEnd();
}
