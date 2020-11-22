#include <iostream>
#include "input.h"
#include "IO.h"
#include "../Algorytm/alg.h"
#include "../Algorytm/graf.h"

int main(int argc, char** argv) {
	try {
		if (argc < 2) {
			throw std::runtime_error("Nie podano pliku wejsciowego!\n");
		}
		Czytnik cz = Czytnik(argv[1]);
		input dane = cz.dane;
		graf g = graf(dane);
		std::cout << g.wezly << std::endl;
	} catch (std::exception& err) {
		std::cout << err.what();
	}
}