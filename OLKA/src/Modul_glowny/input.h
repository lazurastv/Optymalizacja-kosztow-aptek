#include <string>

#ifndef _INPUT_H_
#define _INPUT_H_

struct budynek {
	int ID;
	std::string nazwa;
	int wymog;
	bool operator < (budynek);
	budynek(std::string[]);
	budynek();
};

struct handel {
	int ID_fabryki;
	int ID_apteki;
	int limit;
	double koszt;
	bool operator < (handel);
	handel(std::string[]);
	handel();
};

struct input {
	budynek* fabryki;
	budynek* apteki;
	int ile_fabryk;
	int ile_aptek;
	handel* handle;
	input(const input&);
	input();
	~input();
};

int naturalna(std::string);

double numeryczna(std::string);

bool nieJestNaturalna(std::string);

bool nieJestLiczba(std::string);

bool nieOdpowiedniaPrecyzja(std::string);

std::string usunSpacje(std::string);

#endif