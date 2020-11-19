#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "IO.h"
#include "input.h"

std::runtime_error BrakPlikuWejsciowego() {
	return std::runtime_error("Nie podano pliku wejœciowego!\n");
}

std::runtime_error BrakiWDanych(int lin) {
	return std::runtime_error("Linijka " + lin + " ma niepelne dane!\n");
}

std::runtime_error ZbytDlugaLinijka(int lin) {
	return std::runtime_error("Linijka " + lin + " jest zbyt dluga!\n");
}

std::runtime_error LiczbaNienaturalna(int lin) {
	return std::runtime_error("\"" + number + "\" w linijce " + lin + " nie jest liczb¹ naturaln¹ albo jest zbyt du¿¹!\n");
}

std::runtime_error NiespodziewanaLinijka(int lin, char* exp, char* rec) {
	return std::runtime_error("Linijka " + lin + " powinna byæ: \"" + exp + "\", a jest: \"" + rec + "\"!\n";);
};

std::runtime_error PlikNieTekstowy(char* file) {
	return runtime_error("\"" + file + "\" nie jest plikiem tekstowym!\n");
};

std::runtime_error PlikNieIstnieje(char* file) {
	return runtime_error("B³¹d otwierania \"" + file + "\"! Czy plik istnieje / œcie¿ka jest poprawna?");
};

buildings_with_size getBuildingData(std::ifstream& input_file, std::string expected_line, int start) {
	std::string read_line;
	building tmp[100];
	std::string cut[3];
	int i = 0;
	try {
		while (getline(input_file, read_line) && read_line != expected_line) {
			std::stringstream scan_line(read_line);
			for (int j = 0; j < 3; j++) {
				if (!getline(scan_line, cut[j], '|')) {
					throw BrakiWDanych(start + i);
				}
			}
			try {
				if (!isNatural(stof(cut[0]))) {
					throw std::invalid_argument("");
				}
				tmp[i].count = stoi(cut[0]);
			} catch (std::invalid_argument err) {
				throw NumberNotNatural(start + i, cut[0]);
			}
			try {
				if (!isNatural(stof(cut[2]))) {
					throw std::invalid_argument("");
				}
				tmp[i].count = stoi(cut[2]);
			} catch (std::invalid_argument err) {
				throw NumberNotNatural(start + i, cut[2]);
			}
			i++;
		}
	} catch (std::length_error) {
		throw StringTooLong(start + i);
	}
	if (read_line != expected_line) {
		throw OtherLineExpected(start + i, expected_line, read_line);
	}
	building buildings[i];
	for (int j = 0; j < i; j++) {
		buildings[j] = tmp[j];
	}
	buildings_with_size ret;
	ret.buildings = buildings;
	ret.size = i;
	return ret;
}

std::ifstream przygotujPlik(std::string sciezka) {
	std::ifstream plik;
	if (!plikJestTekstowy(sciezka)) {
		throw PlikNieTekstowy(sciezka);
	}
	plik.open(sciezka);
	if (!plikIstnieje(plik)) {
		throw PlikNieIstnieje(sciezka);
	}
	return plik;
}

bool plikJestTekstowy(std::string plik) {
	int len = plik.length();
	if (len < 4 || plik.substr(len - 4, 4) != ".txt") {
		throw PlikNieTekstowy(plik);
	}
}

bool plikIstnieje(std::ifstream& plik) {
	return plik.good() && plik.is_open();
}

//Zawsze rozmiaru 2
int* sprawdzSzablonIIlosc(std::ifstream& plik) {
	
}

void checkFirstLine(std::ifstream& in) {
	std::string expected_line = "# Producenci szczepionek (id | nazwa | dzienna produkcja)";
	std::string read_line;
	getline(in, read_line);
	if (read_line != expected_line) {
		throw OtherLineExpected(1, expected_line, read_line);
	}
}

bool liczbaNaturalna(float num) {
	return (int)num == num && num >= 0;
}

input wczytajDane(const char* sciezka) {
	using namespace std;
	string sciezka_string(sciezka);
	ifstream input_file = przygotujPlik(sciezka_string);
	checkFirstLine(input_file);
	expected_line = "# Apteki (id | nazwa | dzienne zapotrzebowanie)";
	factories = getBuildingData(input_file, expected_line, 3);
	expected_line = "# Po³¹czenia producentów i aptek (id producenta | id apteki";
	expected_line += "| dzienna maksymalna liczba dostarczanych szczepionek | koszt szczepionki [z³] )";
	pharmacies = getBuildingData(input_file, expected_line, factories.size + 3);
	input_file.close();
}
