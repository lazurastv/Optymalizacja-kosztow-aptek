#include <cassert>
#include <string>
#include <iostream>
#include "../OLKA/Modul_glowny/input.h"
#include "../OLKA/Algorytm/graf.h"

budynek pseudo_budynek(int ID, std::string nazwa, int wymog) {
	budynek tmp;
	tmp.ID = ID;
	tmp.nazwa = nazwa;
	tmp.wymog = wymog;
	return tmp;
}

handel pseudo_handel(int ID_f, int ID_a, int limit, double koszt) {
	handel tmp;
	tmp.ID_fabryki = ID_f;
	tmp.ID_apteki = ID_a;
	tmp.limit = limit;
	tmp.koszt = koszt;
	return tmp;
}

void test_null_input() {
	input in;
	try {
		graf g(in);
		assert(false);
	} catch (std::exception err) {
	}
}

void test_dobry_input() {
	input in;
	in.ile_fabryk = 2;
	in.ile_aptek = 1;
	budynek fabryki[2];
	budynek apteki[1];
	handel handle[2];
	fabryki[0] = pseudo_budynek(5, "Farma co.", 400);
	fabryki[1] = pseudo_budynek(8, "Nom", 340);
	apteki[0] = pseudo_budynek(3, "Odbiorca", 740);
	handle[0] = pseudo_handel(5, 3, 500, 50.76);
	handle[1] = pseudo_handel(8, 3, 400, 49.98);
	in.fabryki = fabryki;
	in.apteki = apteki;
	in.handle = handle;
	graf g(in);
	assert(5 == g.wezly);
	int** limity = new int*[5];
	double** koszty = new double*[5];
	for (int i = 0; i < 5; i++) {
		limity[i] = new int[5];
		koszty[i] = new double[5];
		for (int j = 0; j < g.wezly; j++) {
			limity[i][j] = 0;
			koszty[i][j] = 0;
		}
	}
	limity[0][1] = 400;
	limity[0][2] = 340;
	limity[3][4] = 740;
	limity[1][3] = 500;
	koszty[1][3] = 50.76;
	limity[2][3] = 400;
	koszty[2][3] = 49.98;
	for (int i = 0; i < g.wezly; i++) {
		for (int j = 0; j < g.wezly; j++) {
			assert(limity[i][j] == g.limity[i][j]);
			assert(koszty[i][j] == g.koszty[i][j]);
		}
	}
	for (int i = 0; i < 5; i++) {
		delete[] (limity[i]);
		delete[] (koszty[i]);
	}
	delete[] (limity);
	delete[] (koszty);
}

main() {
	std::cout << "Test null input\n";
	test_null_input();
	std::cout << "Test dobry input\n";
	test_dobry_input();
}