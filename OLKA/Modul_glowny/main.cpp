#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "main.h"

class NoInputFile: public std::exception {
	public:
		const char* what() const throw() {
			return "Nie podano pliku wejœciowego!\n";
		}
};

class LineError: public std::exception {
	protected:
		std::string what_arg;
	public:
		LineError(int n) {
			what_arg = "Linijka " + std::to_string(n) + ": ";
		}
		const char* what() const throw() {
			return what_arg.c_str();
		}
};

class NotEnoughData: public LineError {
	public:
		NotEnoughData(int n) : LineError{ n } {
			what_arg += "Brakuje danych!\n";
		}
};

class StringTooLong: public LineError {
	public:
		StringTooLong(int n) : LineError{ n } {
			what_arg += "Linijka jest zbyt d³uga!\n";
		}
};

class NumberNotNatural: public LineError {
	public:
		NumberNotNatural(int n, const std::string& number) : LineError{ n } {
			what_arg += "\"" + number + "\" nie jest liczb¹ naturaln¹ albo jest zbyt du¿¹!\n";
		}
};

class OtherLineExpected: public LineError {
	public:
		OtherLineExpected(int n, const std::string& exp, const std::string& rec) : LineError{ n } {
			what_arg += "Powinna byæ: \"" + exp + "\", a jest: \"" + rec + "\"!\n";
		}
};

class FileIsNotTextFile: public std::exception {
	protected:
		std::string what_arg;
	public:	
		FileIsNotTextFile(const std::string& file) {
			what_arg = "\"" + file + "\" nie jest plikiem tekstowym!\n";
		}
		
		const char* what() const throw() {
			return what_arg.c_str();
		}
};

class FileDoesNotExist: public std::exception {
	protected:
		std::string what_arg;
	public:
		FileDoesNotExist(const std::string& file) {
			what_arg = "B³¹d otwierania \"" + file + "\"! Czy plik istnieje / œcie¿ka jest poprawna?";
		}
		
		const char* what() const throw() {
			return what_arg.c_str();
		}
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
					throw NotEnoughData(start + i);
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

std::string getFileName(int len, char** in) {
	if (len < 2) {
		throw NoInputFile();
	}
	return in[1];
}

std::ifstream getFile(std::string input) {
	int len = input.length();
	if (len < 4 || input.substr(len - 4, 4) != ".txt") {
		throw FileIsNotTextFile(input);
	}
	std::ifstream file;
	file.open(input);
	if (!fileExists(file)) {
		throw FileDoesNotExist(input);
	}
	return file;
}

void checkFirstLine(std::ifstream& in) {
	std::string expected_line = "# Producenci szczepionek (id | nazwa | dzienna produkcja)";
	std::string read_line;
	getline(in, read_line);
	if (read_line != expected_line) {
		throw OtherLineExpected(1, expected_line, read_line);
	}
}

bool fileExists(std::ifstream& file) {
	return file.good() && file.is_open();
}

bool isNatural(float num) {
	return (int)num == num && num >= 0;
}

int main(int argc, char** argv) {
	using namespace std;

	string input_string, expected_line;
	ifstream input_file;
	buildings_with_size factories, pharmacies;

	try {
		input_string = getFileName(argc, argv);
		input_file = getFile(input_string);
		checkFirstLine(input_file);
		expected_line = "# Apteki (id | nazwa | dzienne zapotrzebowanie)";
		factories = getBuildingData(input_file, expected_line, 3);
		expected_line = "# Po³¹czenia producentów i aptek (id producenta | id apteki";
		expected_line += "| dzienna maksymalna liczba dostarczanych szczepionek | koszt szczepionki [z³] )";
		pharmacies = getBuildingData(input_file, expected_line, factories.size + 3);
	} catch (std::exception& err) {
		cerr << err.what();
		return 1;
	}
	
	input_file.close();
}
