#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "IO.h"
#include "input.h"

Czytnik::Czytnik (const char* in) {
	sciezka = std::string(in);
	sprawdzPlik();
	sprawdzTytul();
	czytajBudynki(0);
	czytajBudynki(1);
	czytajHandle();
	sprawdzID();
	plik.close();
}

void Czytnik::sprawdzPlik() {
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

void Czytnik::sprawdzID() {
	for (int i = 0; i < dane.ile_fabryk - 1; i++) {
		if (dane.fabryki[i].ID == dane.fabryki[i + 1].ID) {
			throw std::runtime_error(dane.fabryki[i].nazwa + " oraz " + dane.fabryki[i + 1].nazwa + " maja ten sam identyfikator!\n");
		}
	}
	for (int i = 0; i < dane.ile_aptek - 1; i++) {
		if (dane.apteki[i].ID == dane.apteki[i + 1].ID) {
			throw std::runtime_error(dane.apteki[i].nazwa + " oraz " + dane.apteki[i + 1].nazwa + " maja ten sam identyfikator!\n");
		}
	}
	for (int i = 0; i < dane.ile_fabryk; i++) {
		for (int j = 0; j < dane.ile_aptek; j++) {
			handel handel = dane.handle[i * dane.ile_aptek + j];
			if (handel.ID_fabryki != dane.fabryki[i].ID || handel.ID_apteki != dane.apteki[j].ID) {
				throw std::runtime_error("Brakuje danych dotyczacych handlu miedzy " + dane.fabryki[i].nazwa + " i " + dane.apteki[j].nazwa + "!\n");
			}
		}
	}
}

void Czytnik::czytajBudynki(int n) {
	budynek tmp[1000];
	std::string cut[3];
	int ile = 0;
	std::string bufor;
	while (getline(plik, bufor) && bufor != tytul[n + 1]) {
		czytajLinijke(bufor, cut, 3);
		try {
			tmp[ile++] = budynek(cut);
		} catch (std::runtime_error err) {
			throw bladLinia(err.what());
		}
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
			std::sort(dane.fabryki, dane.fabryki + ile);
			break;
		case 1:
			dane.apteki = new budynek[ile];
			for (int i = 0; i < ile; i++) {
				dane.apteki[i] = tmp[i];
			}
			dane.ile_aptek = ile;
			std::sort(dane.apteki, dane.apteki + ile);
	}
}

void Czytnik::czytajHandle() {
	int size = dane.ile_fabryk * dane.ile_aptek;
	handel tmp[size];
	std::string cut[4];
	int ile = 0;
	std::string bufor;
	while (getline(plik, bufor) && ile <= size) {
		czytajLinijke(bufor, cut, 4);
		try {
			tmp[ile++] = handel(cut);
		} catch (std::runtime_error err) {
			throw bladLinia(err.what());
		}
		linijka++;
	}
	linijka++;
	if (ile != size) {
		throw std::runtime_error("Handli powinno byc " + std::to_string(size) + ", a jest " + std::to_string(ile) + "!\n");
	}
	dane.handle = new handel[ile];
	for (int i = 0; i < ile; i++) {
		dane.handle[i] = tmp[i];
	}
	std::sort(dane.handle, dane.handle + dane.ile_fabryk * dane.ile_aptek);
}

void Czytnik::czytajLinijke(std::string bufor, std::string* cut, int ile) {
	std::stringstream skaner(bufor);
	for (int i = 0; i < ile; i++) {
		if (!getline(skaner, cut[i], '|') || jestPusty(cut[i])) {
			throw bladLinia("Brakuje informacji!\n");
		}
	}
}

std::runtime_error Czytnik::bladLinia(const std::string in) {
	return std::runtime_error("Linijka " + std::to_string(linijka) + ": " + in);
}

bool Czytnik::plikJestTekstowy() {
	int len = sciezka.length();
	return len > 3 && sciezka.substr(len - 4, 4) == ".txt";
}

bool Czytnik::plikIstnieje() {
	return plik.good() && plik.is_open();
}

bool jestPusty(std::string in) {
	for (char c : in) {
		if (c > ' ') {
			return false;
		}
	}
	return true;
}