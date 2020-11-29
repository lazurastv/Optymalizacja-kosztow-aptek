#include "wynik.h"

wynik::wynik(int f, int a) {
	fabryki = f;
	apteki = a;
	zakupy = new int*[fabryki];
	koszty = new double*[fabryki];
	for (int i = 0; i < fabryki; i++) {
		zakupy[i] = new int[apteki];
		koszty[i] = new double[apteki];
		for (int j = 0; j < apteki; j++) {
			zakupy[i][j] = 0;
			koszty[i][j] = 0;
		}
	}
}

wynik::wynik(const wynik& w) {
	fabryki = w.fabryki;
	apteki = w.apteki;
	zakupy = new int*[fabryki];
	koszty = new double*[fabryki];
	for (int i = 0; i < fabryki; i++) {
		zakupy[i] = new int[apteki];
		koszty[i] = new double[apteki];
		for (int j = 0; j < apteki; j++) {
			zakupy[i][j] = w.zakupy[i][j];
			koszty[i][j] = w.koszty[i][j];
		}
	}
}

wynik::wynik() {
	zakupy = nullptr;
	koszty = nullptr;
}

wynik::~wynik() {
	for (int i = 0; i < fabryki; i++) {
		delete[] (zakupy[i]);
		delete[] (koszty[i]);
	}
	delete[] (zakupy);
	delete[] (koszty);
}