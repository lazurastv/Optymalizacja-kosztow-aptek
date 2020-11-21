#include <iostream>
#include "input.h"
#include "IO.h"

int main(int argc, char** argv) {
	try {
		if (argc < 2) {
			throw std::runtime_error("Nie podano pliku wejsciowego!\n");
		}
		Czytnik cz = Czytnik(argv[1]);
		input dane = cz.dane;
		for (int i = 0; i < dane.ile_fabryk * dane.ile_aptek; i++) {
			std::cout << dane.handle[i].ID_fabryki << " " << dane.handle[i].ID_apteki << " " << dane.handle[i].limit << std::endl;
		}
	} catch (std::exception& err) {
		std::cout << err.what();
	}
}