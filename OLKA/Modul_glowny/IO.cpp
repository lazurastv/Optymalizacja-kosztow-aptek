#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "IO.h"
#include "input.h"

main() {
	try {
		Czytnik cz = Czytnik("W³asny test.txt");
		input out = cz.wczytajDane();
		std::cout << out.ile_fabryk << " " << out.ile_aptek << std::endl;
		for (int i = 0; i < 2; i++) {
			std::cout << out.fabryki[i].nazwa << "\n";
		}
		for (int i = 0; i < 3; i++) {
			std::cout << out.apteki[i].nazwa << "\n";
		}
		for (int i = 0; i < 6; i++) {
			std::cout << out.handle[i].koszt << " ";
		}
		delete[] (out.fabryki);
		delete[] (out.apteki);
		delete[] (out.handle);
	} catch (std::exception& err) {
		std::cerr << err.what();
	}
}

Czytnik::Czytnik (const char* in) {
	sciezka = std::string(in);
	przygotujPlik();
	sprawdzTytul();
	czytajBudynki(0);
	czytajBudynki(1);
	czytajHandle();
	plik.close();
}

input Czytnik::wczytajDane() {
	return dane;
}

void Czytnik::przygotujPlik() {
	if (!plikJestTekstowy()) {
		throw std::runtime_error("Plik \"" + sciezka + "\" nie jest tekstowy!\n");
	}
	plik.open(sciezka);
	if (!plikIstnieje()) {
		throw std::runtime_error("Nie znaleziono pliku \"" + sciezka + "\"!\n");
	}
}

void Czytnik::sprawdzTytul() {
	std::string bufor;
	getline(plik, bufor);
	if (bufor != tytul[0]) {
		throw bladLinia("Powinna byc \"" + tytul[0] + "\", a jest \"" + bufor + "\"!\n");
	}
	linijka++;
}

bool Czytnik::plikJestTekstowy() {
	int len = sciezka.length();
	return len > 3 && sciezka.substr(len - 4, 4) == ".txt";
}

bool Czytnik::plikIstnieje() {
	return plik.good() && plik.is_open();
}

void Czytnik::czytajBudynki(int n) {
	budynek tmp[1000];
	std::string cut[3];
	int ile = 0;
	std::string bufor;
	while (getline(plik, bufor) && bufor != tytul[n + 1]) {
		czytajLinijke(bufor, cut, 3);
		tmp[ile++] = stworzBudynek(cut);
		linijka++;
	}
	linijka++;
	if (bufor != tytul[n + 1]) {
		throw bladLinia("Powinna byc \"" + tytul[n + 1] + "\", a jest \"" + bufor + "\"!\n");
	}
	switch (n) {
		case 0:
			dane.fabryki = new budynek[ile];
			for (int i = 0; i < ile; i++) {
				dane.fabryki[i] = tmp[i];
			}
			dane.ile_fabryk = ile;
			break;
		case 1:
			dane.apteki = new budynek[ile];
			for (int i = 0; i < ile; i++) {
				dane.apteki[i] = tmp[i];
			}
			dane.ile_aptek = ile;
	}
}

void Czytnik::czytajHandle() {
	int size = dane.ile_fabryk * dane.ile_aptek;
	handel tmp[size];
	std::string cut[4];
	int ile = 0;
	std::string bufor;
	while (getline(plik, bufor) && ile < size) {
		czytajLinijke(bufor, cut, 4);
		tmp[ile++] = stworzHandel(cut);
		linijka++;
	}
	linijka++;
	if (ile < size) {
		throw std::runtime_error("Handli powinno byc " + std::to_string(size) + ", a jest " + std::to_string(ile) + "!\n");
	}
	dane.handle = new handel[ile];
	for (int i = 0; i < ile; i++) {
		dane.handle[i] = tmp[i];
	}
}

void Czytnik::czytajLinijke(std::string bufor, std::string* cut, int ile) {
	std::stringstream skaner(bufor);
	for (int i = 0; i < ile; i++) {
		if (!getline(skaner, cut[i], '|')) {
			throw bladLinia("Brakuje informacji!\n");
		}
	}
}

budynek Czytnik::stworzBudynek(std::string in[3]) {
	budynek tmp;
	tmp.ID = naturalna(in[0]);
	if (in[1].length() > 1000) {
		throw bladLinia("Nazwa jest zbyt dluga!\n");
	}
	tmp.nazwa = in[1];
	tmp.wymog = naturalna(in[2]);
	return tmp;
}

handel Czytnik::stworzHandel(std::string in[4]) {
	handel tmp;
	tmp.ID_fabryki = naturalna(in[0]);
	tmp.ID_apteki = naturalna(in[1]);
	tmp.limit = naturalna(in[2]);
	tmp.koszt = numeryczna(in[3]);
	return tmp;
}

int Czytnik::naturalna(std::string liczba) {
	try {
		int n = stoi(liczba);
		if (n < 0) {
			throw std::invalid_argument("");
		}
		return n;
	} catch (std::invalid_argument err) {
		throw bladLinia("\"" + liczba + "\" nie jest liczba naturalna!\n");
	}
}

float Czytnik::numeryczna(std::string liczba) {
	try {
		float n = stof(liczba);
		if (n < 0) {
			throw std::invalid_argument("");
		}
		return n;
	} catch (std::invalid_argument err) {
		throw bladLinia("\"" + liczba + "\" nie jest dodatnia liczba o precyzji do drugiego miejsca po przecinku!");
	}
}

std::runtime_error Czytnik::bladLinia(const std::string in) {
	return std::runtime_error("Linijka " + std::to_string(linijka) + ": " + in);
}