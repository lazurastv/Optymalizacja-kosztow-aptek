#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <locale.h>
#include "main.h"

ret_array getBuildingData(std::ifstream& input_file, std::string expected_line) {
	std::string read_line;
	building tmp[100];
	int i = 0;
	while (getline(input_file, read_line) && read_line != expected_line) {
		std::stringstream scan_line(read_line);
		getline(scan_line, read_line, '|');
		try {
			tmp[i].ID = stoi(read_line);
		} catch (std::invalid_argument err) {
			std::stringstream ss;
			ss << "W linijce \"";
		        ss << scan_line.str();
		        ss << "\" wartoœæ \"";
		        ss << read_line;
		        ss << "\" nie jest poprawnym identyfikatorem! Musi byæ liczba naturalna lub 0.\n";
			throw std::runtime_error(ss.str());
		}
		getline(scan_line, read_line, '|');
		try {
			tmp[i].name = read_line;
		} catch (std::length_error) {
			std::stringstream ss;
			ss << "Nazwa w linijce ";
			ss << i + 2;
		        ss << " jest zbyt d³uga!\n";
			throw std::runtime_error(ss.str());
		}
		if (!getline(scan_line, read_line, '|')) {
			throw std::runtime_error("\"" + scan_line.str() + "\" ma za ma³¹ iloœæ danych!\n");
		}
		try {
			tmp[i].count = stoi(read_line);
		} catch (std::invalid_argument) {
			throw std::runtime_error("W linijce \"" + scan_line.str() + "\" wartoœæ \"" + read_line + "\" nie jest poprawn¹ iloœci¹ leków! Musi byæ naturalna lub 0.\n");
		}
		i++;
	}
	if (read_line != expected_line) {
		std::stringstream ss;
		ss << "Brak linii ";
		ss << expected_line;
		ss << " w pliku! Powinna byæ na ";
	        ss << i + 2;
		ss << " linijce.\n";
		throw std::runtime_error(ss.str());
	}
	building builds[i];
	for (int j = 0; j < i; j++) {
		builds[j] = tmp[j];
	}
	ret_array ret;
	ret.builds = builds;
	ret.amount = i;
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
		throw std::runtime_error("Plik nie spe³nia wymogów szablonu! Pierwsza linijka powinna byæ :\"" + expected_line + "\", a jest: \"" + read_line + "\"!\n");
	}
}

bool fileExists(std::ifstream& file) {
	return file.good() && file.is_open();
}

int main(int argc, char** argv) {
	using namespace std;
	setlocale(LC_CTYPE, "Polish");

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
	ret_array factories;
	
	try {
		factories = getBuildingData(input_file, expected_line);
	} catch (runtime_error err) {
		cerr << err.what();
		return 4;
	}
	
	expected_line = "# Po³¹czenia producentów i aptek (id producenta | id apteki | dzienna maksymalna liczba dostarczanych szczepionek | koszt szczepionki [z³] )";
	ret_array pharmacies;
	
	try {
		pharmacies = getBuildingData(input_file, expected_line);
	} catch (int err) {
		cerr << "Plik nie spelnia wymogow szablonu!";
		cerr << " Linijka poprzedzajaca handle powinna byc: \"" << expected_line << "\"\n";
		return 6;
	} catch (std::invalid_argument) {
		cerr << "Wartosci w pliku sa niepoprawne albo ich nie ma!\n";
		return 7;
	}
	
	input_file.close();
}
