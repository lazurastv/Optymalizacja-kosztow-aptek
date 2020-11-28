#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <filesystem>
#include "IO.h"
#include "input.h"

namespace fs = std::filesystem;

Czytnik::Czytnik (const char* in) {
	std::string sciezka(in);
	sprawdzPlik(sciezka);
	plik.open(sciezka);
}

input Czytnik::wczytajDane() {
	sprawdzTytul();
	czytajBudynki(0);
	czytajBudynki(1);
	czytajHandle();
	sprawdzID();
	plik.close();
	return dane;
}

void Czytnik::sprawdzPlik(std::string sciezka) {
	if (!plikJestTekstowy(sciezka)) {
		throw std::runtime_error("Plik \"" + sciezka + "\" nie jest tekstowy!\n");
	}
	if (!fs::exists(sciezka)) {
		throw std::runtime_error("Nie znaleziono pliku \"" + sciezka + "\"!\n");
	}
}

void Czytnik::sprawdzTytul() {
	std::string bufor;
	getline(plik, bufor);
	if (bufor != tytul(0)) {
		throw bladLinia("Powinna byc \"" + tytul(0) + "\", a jest \"" + bufor + "\"!\n");
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
	while (getline(plik, bufor) && bufor != tytul(n + 1)) {
		czytajLinijke(bufor, cut, 3);
		try {
			tmp[ile++] = budynek(cut);
		} catch (std::runtime_error err) {
			throw bladLinia(err.what());
		}
		linijka++;
	}
	linijka++;
	if (bufor != tytul(n + 1)) {
		throw bladLinia("Powinna byc \"" + tytul(n + 1) + "\", a jest \"" + bufor + "\"!\n");
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
	handel* tmp = new handel[size];
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
	delete[] (tmp);
	std::sort(dane.handle, dane.handle + dane.ile_fabryk * dane.ile_aptek);
}

void Czytnik::czytajLinijke(std::string bufor, std::string* cut, int ile) {
	std::stringstream skaner(bufor);
	for (int i = 0; i < ile; i++) {
		if (!getline(skaner, cut[i], '|')) {
			throw bladLinia("Brakuje informacji!\n");
		}
	}
}

std::runtime_error Czytnik::bladLinia(const std::string in) {
	return std::runtime_error("Linijka " + std::to_string(linijka) + ": " + in);
}

bool plikJestTekstowy(std::string sciezka) {
	int len = sciezka.length();
	return len > 3 && sciezka.substr(len - 4, 4) == ".txt";
}

std::string tytul(int n) {
	switch(n) {
		case 0:
			return "# Producenci szczepionek (id | nazwa | dzienna produkcja)";
		case 1:
			return "# Apteki (id | nazwa | dzienne zapotrzebowanie)";
		case 2:
			return "# Polaczenia producentow i aptek (id producenta | id apteki | "
					"dzienna maksymalna liczba dostarczanych szczepionek | koszt szczepionki [zl])";
		default:
			return "";
	}
}

void zapiszWynik(input in, wynik w) {
	using namespace std;
	ifstream tmp;
	string title;
	int t = 0;
    fs::create_directory("Plik_wyjsciowy");
	do {
		title = "Plik_wyjsciowy/Wynik_" + to_string(in.ile_fabryk) + "_" + to_string(in.ile_aptek) + "_" + to_string(t++) + ".txt";
		tmp = ifstream(title);
	} while (fs::exists(title));
	ofstream out;
	out.open(title);
	out.precision(15);
	double suma = 0;
	for (int j = 0; j < in.ile_aptek; j++) {
		for (int i = 0; i < in.ile_fabryk; i++) {
			if (w.zakupy[i][j] != 0) {
				out << in.fabryki[i].nazwa << " -> " << in.apteki[j].nazwa;
				out << " [Koszt = " << w.zakupy[i][j] << " * " << in.handle[i * in.ile_fabryk + j].koszt;
				out << " = " << w.koszty[i][j] << " zl]\n";
				suma += w.koszty[i][j];
			}
		}
	}
	out << "Oplaty calkowite : " << suma;
	out.close();
}