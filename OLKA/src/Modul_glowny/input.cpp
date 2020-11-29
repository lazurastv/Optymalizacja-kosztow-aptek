#include <sstream>
#include <string>
#include "input.h"

bool budynek::operator < (budynek a) {
	return ID < a.ID;
}

budynek::budynek(std::string in[3]) {
	if (in == nullptr) {
		throw std::runtime_error("Tablica nie istnieje!\n");
	}
	for (int i = 0; i < 3; i++) {
		in[i] = usunSpacje(in[i]);
		if (in[i].empty()) {
			throw std::runtime_error("Brakuje informacji!\n");
		}
	}
	ID = naturalna(in[0]);
	if (in[1].length() > 1000) {
		throw std::runtime_error("Nazwa musi miec mniej niz 1000 znakow!\n");
	}
	nazwa = usunSpacje(in[1]);
	wymog = naturalna(in[2]);
}

budynek::budynek() {};

bool handel::operator < (handel a) {
	if (ID_fabryki == a.ID_fabryki) {
		return ID_apteki < a.ID_apteki;
	} else {
		return ID_fabryki < a.ID_fabryki;
	}
}

handel::handel(std::string in[4]) {
	if (in == nullptr) {
		throw std::runtime_error("Tablica nie istnieje!\n");
	}
	for (int i = 0; i < 4; i++) {
		in[i] = usunSpacje(in[i]);
		if (in[i].empty()) {
			throw std::runtime_error("Brakuje informacji!\n");
		}
	}
	ID_fabryki = naturalna(in[0]);
	ID_apteki = naturalna(in[1]);
	limit = naturalna(in[2]);
	koszt = numeryczna(in[3]);
}

handel::handel() {};

int naturalna(std::string liczba) {
	try {
		int n = stoi(liczba);
		if (nieJestNaturalna(liczba) || n < 0) {
			throw std::exception();
		}
		return n;
	} catch (std::exception err) {
		throw std::runtime_error("\"" + liczba + "\" nie jest liczba naturalna!\n");
	}
}

double numeryczna(std::string liczba) {
	try {
		double n = stod(liczba);
		if (nieJestLiczba(liczba) || nieOdpowiedniaPrecyzja(liczba) || n < 0) {
			throw std::exception();
		}
		return n;
	} catch (std::exception err) {
		throw std::runtime_error("\"" + liczba + "\" nie jest dodatnia liczba o precyzji do drugiego miejsca po przecinku!");
	}
}

bool nieJestNaturalna(std::string num) {
	for (char c : num) {
		if (c < '0' || c > '9') {
			return true;
		}
	}
	return false;
}

bool nieJestLiczba(std::string num) {
	for (char c : num) {
		if ((c < '0' || c > '9') && c != '.') {
			return true;
		}
	}
	return false;
}

bool nieOdpowiedniaPrecyzja(std::string num) {
	std::stringstream skaner(num);
	std::string bufor;
	getline(skaner, bufor, '.');
	if (getline(skaner, bufor)) {
		return bufor.length() > 2;
	} else {
		return false;
	}
}

std::string usunSpacje(std::string nazwa) {
	int start = 0;
	int koniec = nazwa.length() - 1;
	int ile = nazwa.length();
	while (nazwa[start] <= ' ' && start < nazwa.length()) {
		start++;
		ile--;
	}
	if (ile == 0) {
		return "";
	}
	while (nazwa[koniec] <= ' ') {
		koniec--;
		ile--;
	}
	return nazwa.substr(start, ile);
}