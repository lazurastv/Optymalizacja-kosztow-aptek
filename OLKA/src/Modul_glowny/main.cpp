#include <iostream>
#include "input.h"
#include "IO.h"
#include "../Algorytm/alg.h"
#include "../Algorytm/graf.h"
#include "../Algorytm/wynik.h"

int main(int argc, char** argv) {
	try {
		if (argc < 2) {
			throw std::runtime_error("Nie podano pliku wejściowego!\n");
		}
		Czytnik cz(argv[1]);
		std::cout << "Wczytywanie danych...\n";
		input dane = cz.wczytajDane();
		Algorytm algorytm(dane);
		std::cout << "Obliczenia...\n";
		wynik wk = algorytm.obliczWynik();
		std::cout << "\nZapisywanie wyniku...\n";
		cz.zapiszWynik(wk);
		std::cout << "Koncze dzialanie.\n";
	} catch (std::exception& err) {
		std::cerr << err.what();
	}
}