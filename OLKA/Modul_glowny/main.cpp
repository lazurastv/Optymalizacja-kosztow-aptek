#include <iostream>
#include "input.h"
#include "IO.cpp"

using namespace std;

runtime_error brakPlikuWejsciowego() {
	return runtime_error("Nie podano pliku wejsciowego!\n");
}

int main(int argc, char** argv) {
	try {
		if (argc < 2) {
			throw brakPlikuWejsciowego();
		}
		input dane = wczytajDane(argv[1]);
		cout << dane.a;
	} catch (std::exception& err) {
		cout << err.what();
	}
}