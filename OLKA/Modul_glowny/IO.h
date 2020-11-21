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
		input dane;
		const std::string tytul[3] = {"# Producenci szczepionek (id | nazwa | dzienna produkcja)", 
									"# Apteki (id | nazwa | dzienne zapotrzebowanie)",
									"# Polaczenia producentow i aptek (id producenta | id apteki | "
									"dzienna maksymalna liczba dostarczanych szczepionek | koszt szczepionki [zl] )"};
		
		void przygotujPlik();
		bool plikJestTekstowy();
		bool plikIstnieje();
		void sprawdzTytul();
		void czytajBudynki(int);
		budynek stworzBudynek(std::string*);
		void czytajHandle();
		handel stworzHandel(std::string*);
		void czytajLinijke(std::string, std::string*, int);
		std::runtime_error bladLinia(std::string);
		int naturalna(std::string);
		float numeryczna(std::string);
	public:
		Czytnik (const char*);
		input wczytajDane();
};

#endif
