#include <cassert>
#include <string>
#include <sstream>
#include <iostream>
#include "../OLKA/Modul_glowny/input.h"

void test_dobry_budynek() {
	std::string cut[3] = {"5", "\t Jacek z.o.o. ! \n", "150"};
	budynek bud(cut);
	assert(bud.ID == 5);
	assert(bud.nazwa == "Jacek z.o.o. !");
	assert(bud.wymog == 150);
}

void test_zle_ID_budynek() {
	std::string cut[3];
	cut[1] = "Jacek z.o.o.";
	cut[2] = "150";
	for (int i = 0; i < 3; i++) {
		switch (i) {
			case 0:
				cut[0] = "5f\n";
				break;
			case 1:
				cut[0] = "5.7";
				break;
			case 2:
				cut[0] = "    ";
		}
		try {
			budynek bud(cut);
			assert(false);
		} catch (std::exception err) {
			continue;
		}
	}
}

void test_zla_nazwa_budynek() {
	std::string cut[3];
	cut[0] = "5";
	cut[2] = "150";
	std::stringstream stream;
	for (int i = 0; i < 201; i++) {
		stream << "abcde";
	}
	for (int i = 0; i < 2; i++) {
		switch (i) {
			case 0:
				cut[1] = stream.str();
				break;
			case 1:
				cut[1] = "   ";
		}
		try {
			budynek bud(cut);
			assert(false);
		} catch (std::exception err) {
			continue;
		}
	}
}

void test_zly_wymog_budynek() {
	std::string cut[3];
	cut[0] = "5";
	cut[1] = "Jacek z.o.o.";
	for (int i = 0; i < 2; i++) {
		switch (i) {
			case 0:
				cut[2] = "15pl\n";
				break;
			case 1:
				cut[2] = "15.77";
			case 2:
				cut[2] = "    ";
		}
		try {
			budynek bud(cut);
			assert(false);
		} catch (std::exception err) {
			continue;
		}
	}
}

void test_null_budynek() {
	try {
		budynek bud(nullptr);
		assert(false);
	} catch (std::exception err) {
	}
}

void test_dobry_handel() {
	std::string cut[4] = {"5", "6", "150", "16.67"};
	handel han(cut);
	assert(han.ID_fabryki == 5);
	assert(han.ID_apteki == 6);
	assert(han.limit == 150);
	assert(han.koszt == 16.67);
}

void test_zla_cena_handel() {
	std::string cut[4];
	cut[0] = "5";
	cut[1] = "6";
	cut[2] = "150";
	for (int i = 0; i < 3; i++) {
		switch(i) {
			case 0:
				cut[3] = "6tekst5\t";
				break;
			case 1:
				cut[3] = "15.677";
				break;
			case 2:
				cut[3] = "    ";
		}
		try {
			handel han(cut);
			assert(false);
		} catch (std::exception err) {
			continue;
		}
	}
}

void test_budynek() {
	std::cout << "Test dobry budynek\n";
	test_dobry_budynek();
	std::cout << "Test zle ID\n";
	test_zle_ID_budynek();
	std::cout << "Test zla nazwa\n";
	test_zla_nazwa_budynek();
	std::cout << "Test zly wymog\n";
	test_zly_wymog_budynek();
	std::cout << "Test null budynek\n";
	test_null_budynek();
}

void test_handel() {
	std::cout << "Test dobry handel\n";
	test_dobry_handel();
	std::cout << "Test zla cena handel\n";
	test_zla_cena_handel();
}

main() {
	test_budynek();
	test_handel();
}