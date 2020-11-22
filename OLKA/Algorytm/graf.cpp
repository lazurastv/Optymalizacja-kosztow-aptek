#include "graf.h"
#include "../Modul_glowny/input.h"

graf::graf(input in) {
	wezly = 2 + in.ile_fabryk + in.ile_aptek;
	limity = new int*[wezly];
	koszty = new float*[wezly];
	for (int i = 0; i < wezly; i++) {
		limity[i] = new int[wezly];
		koszty[i] = new float[wezly];
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