#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "main.h"

buildings_with_size getBuildingData(std::ifstream& input_file, std::string expected_line, int start) {
	std::string read_line;
	building tmp[100];
	int i = 0;
	std::string cut[3];
	while (getline(input_file, read_line) && read_line != expected_line) {
		std::stringstream scan_line(read_line);
		for (int j = 0; j < 3; j++) {
			if (!getline(scan_line, cut[j], '|')) {
				std::stringstream ss;
				ss << "Linijka " << start + i << ": ";
				ss << "ma za ma³¹ iloœæ danych!\n";
				throw std::runtime_error(ss.str());
			}
		}
		try {
			tmp[i].count = stoi(cut[0]);
			if (tmp[i].count < 0) {
				throw std::invalid_argument("");
			}
		} catch (std::invalid_argument err) {
			try {
				float test = stof(cut[0]);
			} catch (std::invalid_argument err) {
				std::stringstream ss;
				ss << "Linijka " << start + i << ": ";
				ss << "\"" << cut[0] << "\" powinno byæ liczb¹ naturaln¹ LUB\n";
				ss << "\"" << read_line << "\" powinno byæ ";
				ss << "\"" << expected_line << "\"!\n";
				throw std::runtime_error(ss.str());
			}
			std::stringstream ss;
			ss << "Linijka " << start + i << ": ";
			ss << cut[2] << " nie jest liczb¹ naturaln¹!\n";
			throw std::runtime_error(ss.str());
		} catch (std::runtime_error err) {
			throw err;
		}
		try {
			tmp[i].name = cut[1];
		} catch (std::length_error) {
			std::stringstream ss;
			ss << "Linijka " << start + i << ": ";
		    ss << "Nazwa jest zbyt d³uga!\n";
			throw std::runtime_error(ss.str());
		}
		try {
			tmp[i].count = stoi(cut[2]);
			if (tmp[i].count < 0) {
				throw std::invalid_argument("");
			}
		} catch (std::invalid_argument err) {
			std::stringstream ss;
			ss << "Linijka " << start + i << ": ";
			ss << cut[2] << " nie jest liczb¹ naturaln¹!\n";
			throw std::runtime_error(ss.str());
		}
		i++;
	}
	if (read_line != expected_line) {
		std::stringstream ss;
		ss << "Linijka " << start + i << ": ";
		ss << "Powinno byæ \"" << expected_line << "\" ";
		ss << ", a jest \"" << read_line << "\"!\n";
		throw std::runtime_error(ss.str());
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

std::string getFileName(int len, char** in) {
	if (len < 2) {
		throw std::runtime_error("Nie podano pliku wejœciowego!\n");
	}
	return in[1];
}

std::ifstream getFile(std::string input) {
	int len = input.length();
	if (len < 4 || input.substr(len - 4, 4) != ".txt") {
		throw std::runtime_error("\"" + input + "\" nie jest plikiem tekstowym!\n");
	}
	std::ifstream file;
	file.open(input);
	if (!fileExists(file)) {
		throw std::runtime_error("B³¹d otwierania \"" + input + "\"! Czy plik istnieje / œcie¿ka jest poprawna?");
	}
	return file;
}

void checkFirstLine(std::ifstream& in) {
	std::string expected_line = "# Producenci szczepionek (id | nazwa | dzienna produkcja)";
	std::string read_line;
	getline(in, read_line);
	
	if (read_line != expected_line) {
		throw std::runtime_error("Linijka 1: Powinno byæ :\"" + expected_line + "\", a jest: \"" + read_line + "\"!\n");
	}
}

bool fileExists(std::ifstream& file) {
	return file.good() && file.is_open();
}

int main(int argc, char** argv) {
	using namespace std;

	string input_string;

        try {
		input_string = getFileName(argc, argv);
	} catch (runtime_error err) {
		cerr << err.what();
		return 1;
	}

	ifstream input_file;

	try {
		input_file = getFile(input_string);
	} catch (runtime_error err) {
		cerr << err.what();
		return 2;
	}
	try {
		checkFirstLine(input_file);
	} catch (runtime_error err) {
		cerr << err.what();
		return 3;
	}
	
	string expected_line = "# Apteki (id | nazwa | dzienne zapotrzebowanie)";
	buildings_with_size factories;
	
	try {
		factories = getBuildingData(input_file, expected_line, 3);
	} catch (runtime_error err) {
		cerr << err.what();
		return 4;
	}
	
	expected_line = "# Po³¹czenia producentów i aptek (id producenta | id apteki | dzienna maksymalna liczba dostarczanych szczepionek | koszt szczepionki [z³] )";
	buildings_with_size pharmacies;
	
	try {
		pharmacies = getBuildingData(input_file, expected_line, factories.size + 3);
	} catch (std::runtime_error err) {
		cerr << err.what();
		return 5;
	}
	
	input_file.close();
}
