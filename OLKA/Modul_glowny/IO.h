#include <string>
#include <fstream>
#include "input.h"

#ifndef _IO_H_
#define _IO_H_

class Czytnik {
	private:
		int linijka = 1;
		std::ifstream plik;
		std::string sciezka;
		const std::string tytul[3] = {"# Producenci szczepionek (id | nazwa | dzienna produkcja)", 
									"# Apteki (id | nazwa | dzienne zapotrzebowanie)",
									"# Polaczenia producentow i aptek (id producenta | id apteki | "
									"dzienna maksymalna liczba dostarczanych szczepionek | koszt szczepionki [zl] )"};
		
		void sprawdzPlik();
		void sprawdzTytul();
		void sprawdzID();
		void czytajBudynki(int);
		void czytajHandle();
		void czytajLinijke(std::string, std::string*, int);
		bool plikJestTekstowy();
		bool plikIstnieje();
		std::runtime_error bladLinia(std::string);
	public:
		Czytnik (const char*);
		input dane;
};

bool jestPusty(std::string);

#endif
