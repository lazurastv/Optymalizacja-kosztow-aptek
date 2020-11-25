#include <iostream>
#include <locale.h>
#include "input.h"
#include "IO.h"
#include "../Algorytm/alg.h"
#include "../Algorytm/graf.h"
#include "../Algorytm/wynik.h"

int main(int argc, char** argv) {
	//setlocale(LC_CTYPE, "Polish");
	//std::wcout << L"ś";
	try {
		if (argc < 2) {
			throw std::runtime_error("Nie podano pliku wejściowego!\n");
		}
		Czytnik cz = Czytnik(argv[1]);
		input dane = cz.dane;
		graf gr(dane);
		Algorytm algorytm(dane.ile_fabryk, dane.ile_aptek);
		wynik wk = algorytm.oblicz_wynik(gr);
		zapiszWynik(dane, wk);
	} catch (std::exception& err) {
		std::cout << err.what();
	}
}