#include "wynik.h"

wynik::wynik(int fabryki, int apteki) {
	suma = 0;
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

wynik::~wynik() {
	int ile = sizeof (zakupy) / sizeof (int*);
	for (int i = 0; i < ile; i++) {
		delete[] (zakupy[i]);
		delete[] (koszty[i]);
	}
	delete[] (zakupy);
	delete[] (koszty);
}