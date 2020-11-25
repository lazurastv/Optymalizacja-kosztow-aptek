#include <climits>
#include "../Modul_glowny/input.h"
#include "alg.h"
#include "graf.h"
#include "wynik.h"

#define INF INT_MAX

#include <iostream>

Algorytm::Algorytm(int f, int a) {
	fabryki = f;
	apteki = a;
	int wezly = 2 + fabryki + apteki;
	przeplyw = new int*[wezly];
	for (int i = 0; i < wezly; i++) {
		przeplyw[i] = new int[wezly];
		for (int j = 0; j < wezly; j++) {
			przeplyw[i][j] = 0;
		}
	}
	poprzednik = new int[wezly];
	poprzedni_dystans = new double[wezly];
	for (int i = 0; i < wezly; i++) {
		poprzednik[i] = 0;
		poprzedni_dystans[i] = 0;
	}
	sprawdzony = new bool[wezly];
	dystans = new double[wezly + 1];
}

Algorytm::~Algorytm() {
	delete[] (sprawdzony);
	for (int i = 0; i < 2 + fabryki + apteki; i++) {
		delete[] (przeplyw[i]);
	}
	delete[] (przeplyw);
	delete[] (poprzednik);
	delete[] (poprzedni_dystans);
	delete[] (dystans);
}

wynik Algorytm::oblicz_wynik(const graf& g) {
	double suma = 0;
	while (bellmanFord(g)) {
        int ile = INF;
		int w = g.wezly - 1;
        while (w != 0) {
			int limit;
			if (przeplyw[w][poprzednik[w]] != 0) {
				limit = przeplyw[w][poprzednik[w]];
			} else {
				limit = g.limity[poprzednik[w]][w] - przeplyw[poprzednik[w]][w];
			}
			if (limit < ile) {
				ile = limit;
			} 
			w = poprzednik[w];
		}
		w = g.wezly - 1;
        while (w != 0) {
			if (przeplyw[w][poprzednik[w]] != 0) { 
				przeplyw[w][poprzednik[w]] -= ile; 
				suma -= ile * g.koszty[w][poprzednik[w]];
			}
			else {
				przeplyw[poprzednik[w]][w] += ile; 
				suma += ile * g.koszty[poprzednik[w]][w];
			}
			w = poprzednik[w];
		}
	}
	wynik score(fabryki, apteki);
	score.suma = suma;
	for (int i = 0; i < fabryki; i++) {
		for (int j = 0; j < apteki; j++) {
			score.zakupy[i][j] = przeplyw[i + 1][j + 1 + fabryki];
			score.koszty[i][j] = score.zakupy[i][j] * g.koszty[i + 1][j + 1 + fabryki];
		}
	}
	return score;
}

bool Algorytm::bellmanFord(const graf& g) {
	int akt_wezel = 0;
	for (int i = 0; i < g.wezly; i++) {
		sprawdzony[i] = false;
		dystans[i] = INF;
	}
	dystans[g.wezly] = INF;
	dystans[0] = 0;
	while (akt_wezel != g.wezly) {
        int najlepszy = g.wezly;
        sprawdzony[akt_wezel] = true;
  
        for (int w = 0; w < g.wezly; w++) { 
			if (!sprawdzony[w]) {
				if (przeplyw[w][akt_wezel] != 0) {
					double koszt = dystans[akt_wezel] + poprzedni_dystans[akt_wezel] - poprzedni_dystans[w] - g.koszty[w][akt_wezel];
					if (koszt < dystans[w]) {
						dystans[w] = koszt; 
						poprzednik[w] = akt_wezel; 
					}
				}
				if (przeplyw[akt_wezel][w] < g.limity[akt_wezel][w]) {
					double koszt = dystans[akt_wezel] + poprzedni_dystans[akt_wezel] - poprzedni_dystans[w] + g.koszty[akt_wezel][w];
					if (koszt < dystans[w]) {
						dystans[w] = koszt;
						poprzednik[w] = akt_wezel;
					} 
				}
				if (dystans[w] < dystans[najlepszy]) {
					najlepszy = w;
				}
			}
		}
		akt_wezel = najlepszy;
	}
		
	for (int w = 0; w < g.wezly; w++) {
		poprzedni_dystans[w] = poprzedni_dystans[w] + dystans[w];
	}
	
	return sprawdzony[g.wezly - 1];
}