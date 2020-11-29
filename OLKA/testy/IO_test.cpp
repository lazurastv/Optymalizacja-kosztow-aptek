#include <cassert>
#include <string>
#include <iostream>
#include "../src/Modul_glowny/IO.h"
#include "../src/Modul_glowny/input.h"

void porownaj_budynki(budynek bud, int ID, std::string nazwa, int wymog) {
	assert(bud.ID == ID);
	assert(bud.nazwa == nazwa);
	assert(bud.wymog == wymog);
}

void porownaj_handle(handel han, int ID_fabryki, int ID_apteki, int limit, double koszt) {
	assert(han.ID_fabryki == ID_fabryki);
	assert(han.ID_apteki == ID_apteki);
	assert(han.limit == limit);
	assert(han.koszt == koszt);
}

void test_wczytajDane() {
	Czytnik cz("../txt/Test.txt");
	input in = cz.wczytajDane();
	assert(in.ile_fabryk == 3);
	assert(in.ile_aptek == 2);
	for (int i = 0; i < 3; i++) {
		switch (i) {
			case 0:
				porownaj_budynki(in.fabryki[i], 1, "Eko Polska 2020", 1300);
				break;
			case 1:
				porownaj_budynki(in.fabryki[i], 3, "Post-Covid Sp. z o.o.", 1100);
				break;
			case 2:
				porownaj_budynki(in.fabryki[i], 5, "BioTech 2.0", 900);
		}
	}
	for (int i = 0; i < 2; i++) {
		switch (i) {
			case 0:
				porownaj_budynki(in.apteki[i], 1, "CentMedEko 24h", 690);
				break;
			case 1:
				porownaj_budynki(in.apteki[i], 7, "CentMedEko Centrala", 450);
		}
	}
	for (int i = 0; i < 6; i++) {
		switch (i) {
			case 0:
				porownaj_handle(in.handle[i], 1, 1, 900, 100);
				break;
			case 1:
				porownaj_handle(in.handle[i], 1, 7, 600, 80);
				break;
			case 2:
				porownaj_handle(in.handle[i], 3, 1, 600, 70);
				break;
			case 3:
				porownaj_handle(in.handle[i], 3, 7, 800, 70.5);
				break;
			case 4:
				porownaj_handle(in.handle[i], 5, 1, 750, 90.99);
				break;
			case 5:
				porownaj_handle(in.handle[i], 5, 7, 450, 70);
				break;
		}
	}
}

void test_sprawdzPlik() {
	try {
		Czytnik cz("Test");
		assert(false);
	} catch (std::exception err) {
	}
	try {
		Czytnik cz("Nic.txt");
		assert(false);
	} catch (std::exception err) {
	}
	try {
		Czytnik cz("");
		assert(false);
	} catch (std::exception err) {
	}
}

void test_sprawdzID() {
	Czytnik cz("../txt/DwaID.txt");
	try {
		input in = cz.wczytajDane();
		assert(false);
	} catch(std::exception err) {
	}
	Czytnik cz2("../txt/BezLinijki.txt");
	try {
		input in = cz2.wczytajDane();
		assert(false);
	} catch (std::exception err) {
	}
}

main() {
	std::cout << "Test sprawdz plik\n";
	test_sprawdzPlik();
	std::cout << "Test sprawdz ID\n";
	test_sprawdzID();
	std::cout << "Test wczytaj dane\n";
	test_wczytajDane();
}