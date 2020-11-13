#include <iostream>
#include <fstream>
#include <sstream>
#include "main.h"

ret_array getBuildingData(std::ifstream& input_file, std::string expected_line) {
	std::string read_line;
	building tmp[100];
	int i = 0;
	while (getline(input_file, read_line) && read_line != expected_line) {
		std::stringstream scan_line(read_line);
		getline(scan_line, read_line, '|');
		tmp[i].ID = stoi(read_line);
		getline(scan_line, read_line, '|');
		tmp[i].name = read_line;
		if (!getline(scan_line, read_line, '|')) {
			throw 1;
		}
		tmp[i].count = stoi(read_line);
		if (getline(scan_line, read_line, '|')) {
			throw 2;
		}
		i++;
	}
	if (read_line != expected_line) {
		throw 3;
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

int main(int argc, char** argv) {
	using namespace std;

	if (argc < 2) {
		cerr << "Brak pliku wejsciowego!\n";
		return 1;
	}
	
	string input_string = argv[1];
	int len = input_string.length();
	
	if (len < 4 || input_string.substr(len - 4, 4) != ".txt") {
		cerr << "Podany plik nie jest plikiem tekstowym!\n";
		return 2;
	}
	
	ifstream input_file;
	input_file.open(input_string);
	
	if (!input_file.good() || !input_file.is_open()) {
		cerr << "Blad otwierania pliku! Sprawdz czy plik istnieje / czy sciezka jest poprawna.\n";
		return 3;
	}
	
	string read_line, expected_line;
	expected_line = "# Producenci szczepionek (id | nazwa | dzienna produkcja)";
	getline(input_file, read_line);
	
	if (read_line != expected_line) {
		cerr << "Plik nie spelnia wymogow szablonu!";
		cerr << " Pierwsza linijka powinna byc: \"" << expected_line;
		cerr << "\", a jest: \"" << read_line << "\"\n";
		return 4;
	}
	
	expected_line = "# Apteki (id | nazwa | dzienne zapotrzebowanie)";
	ret_array factories;
	
	try {
		factories = getBuildingData(input_file, expected_line);
	} catch (int err) {
		cerr << "Plik nie spelnia wymogow szablonu!";
		cerr << " Linijka poprzedzajaca apteki powinna byc: \"" << expected_line << "\"\n";
		return 5;
	} catch (std::invalid_argument) {
		cerr << "Wartosci w pliku sa niepoprawne albo ich nie ma!\n";
		return 6;
	}
	
	expected_line = "# Połączenia producentów i aptek (id producenta | id apteki | dzienna maksymalna liczba dostarczanych szczepionek | koszt szczepionki [zł] )";
	ret_array pharmacies;
	
	try {
		pharmacies = getBuildingData(input_file, expected_line);
	} catch (int err) {
		cerr << "Plik nie spelnia wymogow szablonu!";
		cerr << " Linijka poprzedzajaca handle powinna byc: \"" << expected_line << "\"\n";
		return 7;
	}
	
	input_file.close();
}
