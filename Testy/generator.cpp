#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

string tytul(int n) {
	switch (n) {
		case 0:
			return "# Producenci szczepionek (id | nazwa | dzienna produkcja)\n";
		case 1:
			return "# Apteki (id | nazwa | dzienne zapotrzebowanie)\n";
		case 2: default:
			return "# Polaczenia producentow i aptek (id producenta | id apteki | "
					"dzienna maksymalna liczba dostarczanych szczepionek | koszt szczepionki [zl] )\n";
	}
}

string budynek(int i) {
	string num = to_string(i);
	return num + '|' + num + '|' + to_string(rand()) + '\n';
}

#include <iostream>

string dwuprzecinkowa() {
	double val = (double)(rand()) / 100;
	stringstream tmp(to_string(val));
	string bufor;
	getline(tmp, bufor, '.');
	int len = bufor.length() + 3;
	return tmp.str().substr(0, len);
}

string handel(int i, int j) {
	string num1 = to_string(i);
	string num2 = to_string(j);
	return num1 + '|' + num2 + '|' + to_string(rand()) + '|' + dwuprzecinkowa() + '\n';
}

void generuj(int fabryki, int apteki) {
	int t = 0;
	string title;
	ifstream in;
	do {
		title = "Test" + to_string(t++) + ".txt";
		in = ifstream(title);
	} while (in.good());
	ofstream out;
	out.open(title);
	out << tytul(0);
	srand(time(NULL));
	for (int i = 0; i < fabryki; i++) {
		out << budynek(i);
	}
	out << tytul(1);
	for (int i = 0; i < apteki; i++) {
		out << budynek(i);
	}
	out << tytul(2);
	for (int i = 0; i < fabryki; i++) {
		for (int j = 0; j < apteki; j++) {
			out << handel(i, j);
		}
	}
	out.close();
}

int main(int argc, char** argv) {
	if (argc < 3) {
		cout << "Podaj liczbe fabryk i aptek (naturalna)!\n";
		return 1;
	}
	int fabryki = atoi(argv[1]);
	int apteki = atoi(argv[2]);
	generuj(fabryki, apteki);
}