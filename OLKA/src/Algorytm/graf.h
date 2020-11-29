#include "../Modul_glowny/input.h"

#ifndef _GRAF_H_
#define _GRAF_H_

struct graf {
	int wezly;
	int** limity;
	double** koszty;
	graf(input);
	graf();
	~graf();
};

#endif