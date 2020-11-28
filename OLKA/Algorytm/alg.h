#include "graf.h"
#include "wynik.h"
#include "../Modul_glowny/input.h"

#ifndef _ALG_H_
#define _ALG_H_

class Algorytm {
	private:
		int fabryki;
		int apteki;
		bool* sprawdzony;
		int** przeplyw;
		int* poprzednik;
		double* potencjal;
		double* dystans;
		bool bellmanFord(const graf&);
		void usun_cykle(const graf&);
	public:
		Algorytm(int, int);
		~Algorytm();
		wynik oblicz_wynik(const graf&);
};


#endif