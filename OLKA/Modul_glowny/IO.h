#include <string>
#include <fstream>
#include "input.h"

#ifndef _IO_H_
#define _IO_H_

class Czytnik {
	private:
		int linijka = 1;
		std::ifstream plik;
		void sprawdzPlik(std::string);
		void sprawdzTytul();
		void sprawdzID();
		void czytajBudynki(int);
		void czytajHandle();
		void czytajLinijke(std::string, std::string*, int);
		std::runtime_error bladLinia(std::string);
	public:
		Czytnik (const char*);
		input dane;
};

bool plikJestTekstowy(std::string);

bool plikIstnieje(std::string);
		
bool napisJestPusty(std::string);

std::string tytul(int);

#endif
