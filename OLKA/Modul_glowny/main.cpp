#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	using namespace std;
	string input_string;
	if (argc > 1) {
		input_string = argv[1];
	} else {
		cerr << "Brak pliku wejsciowego!\n";
		return 1;
	}
	
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
	
	string read_line;
	while (getline(input_file, read_line)) {
		cout << read_line << endl;
	}
	input_file.close();
}
