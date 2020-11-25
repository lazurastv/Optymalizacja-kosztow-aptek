#include "graf.h"
#include "../Modul_glowny/input.h"

#include <iostream>

graf::graf(input in) {
	wezly = 2 + in.ile_fabryk + in.ile_aptek;
	limity = new int*[wezly];
	koszty = new double*[wezly];
	for (int i = 0; i < wezly; i++) {
		limity[i] = new int[wezly];
		koszty[i] = new double[wezly];
		for (int j = 0; j < wezly; j++) {
			limity[i][j] = 0;
			koszty[i][j] = 0;
		}
	}
	for (int j = 0; j < in.ile_fabryk; j++) {
		limity[0][j + 1] = in.fabryki[j].wymog;
	}
	for (int i = 0; i < in.ile_aptek; i++) {
		limity[i + 1 + in.ile_fabryk][wezly - 1] = in.apteki[i].wymog;
	}
	for (int j = 0; j < in.ile_aptek; j++) {
		for (int i = 0; i < in.ile_fabryk; i++) {
			koszty[i + 1][j + 1 + in.ile_fabryk] = in.handle[i * in.ile_fabryk + j].koszt;
			limity[i + 1][j + 1 + in.ile_fabryk] = in.handle[i * in.ile_fabryk + j].limit;
		}
	}
}

graf::~graf() {
	for (int i = 0; i < wezly; i++) {
		delete[] (limity[i]);
		delete[] (koszty[i]);
	}
	delete[] (limity);
	delete[] (koszty);
}