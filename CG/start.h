#pragma once
#include "main.h"
#define STARTWIDTH 2000
#define STARTHEIGHT 1600
#define STARTTHICKNESS 400
class start {
private:
	void buildMenu(int c);
public:
	void menu();
	void pause();
	void archive();
	void help();
};
