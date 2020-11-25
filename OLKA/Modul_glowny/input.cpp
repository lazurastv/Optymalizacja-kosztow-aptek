#include <sstream>
#include <string>
#include "input.h"

#include <iostream>

bool budynek::operator < (budynek a) {
	return ID < a.ID;
}

budynek::budynek(std::string in[3]) {
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

#include <iostream>

handel::handel(std::string in[4]) {
	ID_fabryki = naturalna(in[0]);
	ID_apteki = naturalna(in[1]);
	limit = naturalna(in[2]);
	koszt = numeryczna(in[3]);
}

handel::handel() {};

int naturalna(std::string liczba) {
	try {
		int n = stoi(liczba);
		if (n < 0) {
			throw std::invalid_argument("");
		}
		return n;
	} catch (std::invalid_argument err) {
		throw std::runtime_error("\"" + liczba + "\" nie jest liczba naturalna!\n");
	}
}

double numeryczna(std::string liczba) {
	try {
		double n = stod(liczba);
		if (n < 0 || nieOdpowiedniaPrecyzja(liczba)) {
			throw std::invalid_argument("");
		}
		return n;
	} catch (std::invalid_argument err) {
		throw std::runtime_error("\"" + liczba + "\" nie jest dodatnia liczba o precyzji do drugiego miejsca po przecinku!");
	}
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
	int first = 0;
	int last = nazwa.length() - 1;
	while (nazwa[first] == ' ') {
		first++;
	}
	while (nazwa[last] == ' ') {
		last--;
	}
	return nazwa.substr(first, last + 1);
}