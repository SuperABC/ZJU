#pragma once
#include "main.h"
#include <vector>
#include <fstream>
#include <string>
class objModel {
private:
	struct vertex {
		double x;
		double y;
		double z;
	};
	struct face {
		unsigned int v1, v2, v3;
	};
	std::vector<vertex> vetexes;
	std::vector<face> faces;
public:
	void parse(const char* filename);
	void draw();
};