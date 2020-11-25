#include <iostream>
#include "input.h"
#include "IO.h"
#include "../Algorytm/alg.h"
#include "../Algorytm/graf.h"
#include "../Algorytm/wynik.h"

int main(int argc, char** argv) {
	try {
		if (argc < 2) {
			throw std::runtime_error("Nie podano pliku wejsciowego!\n");
		}
		Czytnik cz = Czytnik(argv[1]);
		input dane = cz.dane;
		/*for (int i = 0; i < dane.ile_fabryk; i++) {
			std::cout << dane.handle[i].koszt;
		}*/
		graf gr(dane);
		Algorytm algorytm(dane.ile_fabryk, dane.ile_aptek);
		wynik wk = algorytm.oblicz_wynik(gr);
		std::cout << std::fixed << wk.suma;
	} catch (std::exception& err) {
		std::cout << err.what();
	}
}