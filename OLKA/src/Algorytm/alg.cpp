#include <climits>
#include <iostream>
#include "../Modul_glowny/input.h"
#include "alg.h"
#include "graf.h"
#include "wynik.h"

#define INF INT_MAX

Algorytm::Algorytm(const input& in) {
	g = graf(in);
	fabryki = in.ile_fabryk;
	apteki = in.ile_aptek;
	przeplyw = new int*[g.wezly];
	for (int i = 0; i < g.wezly; i++) {
		przeplyw[i] = new int[g.wezly];
		for (int j = 0; j < g.wezly; j++) {
			przeplyw[i][j] = 0;
		}
	}
	poprzednik = new int[g.wezly];
	potencjal = new double[g.wezly];
	for (int i = 0; i < g.wezly; i++) {
		poprzednik[i] = 0;
		potencjal[i] = 0;
	}
	sprawdzony = new bool[g.wezly];
	dystans = new double[g.wezly + 1];
}

Algorytm::~Algorytm() {
	delete[] (sprawdzony);
	for (int i = 0; i < g.wezly; i++) {
		delete[] (przeplyw[i]);
	}
	delete[] (przeplyw);
	delete[] (poprzednik);
	delete[] (potencjal);
	delete[] (dystans);
}

wynik Algorytm::obliczWynik() {
	int count = 0;
	std::cout << "Gorne ograniczenie iteracji: " << fabryki * apteki << std::endl;
	while (bellmanFord()) {
		if (count % 100 == 0) {
			std::cout << count << " ";
		}
		count++;
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
			}
			else {
				przeplyw[poprzednik[w]][w] += ile;
			}
			w = poprzednik[w];
		}
	}
	wynik score(fabryki, apteki);
	for (int i = 0; i < fabryki; i++) {
		for (int j = 0; j < apteki; j++) {
			score.zakupy[i][j] = przeplyw[i + 1][j + 1 + fabryki];
			score.koszty[i][j] = score.zakupy[i][j] * g.koszty[i + 1][j + 1 + fabryki];
		}
	}
	return score;
}

bool Algorytm::bellmanFord() {
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
				if (przeplyw[akt_wezel][w] < g.limity[akt_wezel][w]) {
					double koszt = dystans[akt_wezel] + potencjal[akt_wezel] - potencjal[w] + g.koszty[akt_wezel][w];
					if (koszt < dystans[w]) {
						dystans[w] = koszt;
						poprzednik[w] = akt_wezel;
					} 
				}
				if (przeplyw[w][akt_wezel] != 0) {
					double koszt = dystans[akt_wezel] + potencjal[akt_wezel] - potencjal[w] - g.koszty[w][akt_wezel];
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
		potencjal[w] += dystans[w];
		if (INF < potencjal[w]) {
			potencjal[w] = INF;
		}
	}
	
	return sprawdzony[g.wezly - 1];
}