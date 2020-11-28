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
		Czytnik cz = Czytnik(argv[1]);
		input dane = cz.wczytajDane();
		graf gr(dane);
		Algorytm algorytm(dane.ile_fabryk, dane.ile_aptek);
		std::cout << "Zaczynam: ";
		wynik wk = algorytm.oblicz_wynik(gr);
		std::cout << " Skonczylem!";
		zapiszWynik(dane, wk);
	} catch (std::exception& err) {
		std::cerr << err.what();
	}
}