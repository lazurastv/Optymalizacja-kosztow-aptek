#include "../Modul_glowny/input.h"

#ifndef _GRAF_H_
#define _GRAF_H_

struct graf {
	int wezly;
	int** limity;
	float** koszty;
	graf(input);
	~graf();
};

#endif