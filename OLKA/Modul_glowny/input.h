#include <string>

#ifndef _INPUT_H_
#define _INPUT_H_

struct budynek {
	int ID;
	std::string nazwa;
	int wymog;
	bool operator > (budynek);
};

struct handel {
	int ID_fabryki;
	int ID_apteki;
	int limit;
	float koszt;
	bool operator > (handel);
};

struct input {
	budynek* fabryki;
	budynek* apteki;
	int ile_fabryk;
	int ile_aptek;
	handel* handle;
};

#endif