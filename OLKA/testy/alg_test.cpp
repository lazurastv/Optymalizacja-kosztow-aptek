#include <cassert>
#include <iostream>
#include "../src/Modul_glowny/input.h"
#include "../src/Algorytm/alg.h"
#include "../src/Algorytm/wynik.h"

void test_obliczWynik() {
	input in;
	in.fabryki = new budynek[3];
	in.apteki = new budynek[3];
	in.handle = new handel[9];
	in.ile_fabryk = 3;
	in.ile_aptek = 3;
	
	budynek* b;
	for (int i = 0; i < 6; i++) {
		if (i < 3) {
			b = &in.fabryki[i];
		} else {
			b = &in.apteki[i - 3];
		}
		b->ID = i;
		b->nazwa = "test";
		switch (i) {
			case 0:	
				b->wymog = 900;
				break;
			case 1:
				b->wymog = 1300;
				break;
			case 2:
				b->wymog = 1100;
				break;
			case 3:
				b->wymog = 450;
				break;
			case 4:
				b->wymog = 690;
				break;
			case 5:
				b->wymog = 1200;
		}
	}
	delete (b);
	
	handel* h;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			h = &in.handle[i * 3 + j];
			h->ID_fabryki = i;
			h->ID_apteki = j;
			switch (i * 3 + j) {
				case 0:	
					h->limit = 800;
					h->koszt = 70.5;
					break;
				case 1:	
					h->limit = 600;
					h->koszt = 70;
					break;
				case 2:	
					h->limit = 750;
					h->koszt = 90.99;
					break;
				case 3:	
					h->limit = 900;
					h->koszt = 100;
					break;
				case 4:	
					h->limit = 600;
					h->koszt = 80;
					break;
				case 5:	
					h->limit = 450;
					h->koszt = 70;
					break;
				case 6:	
					h->limit = 900;
					h->koszt = 80;
					break;
				case 7:	
					h->limit = 900;
					h->koszt = 90;
					break;
				case 8:	
					h->limit = 300;
					h->koszt = 100;
			}
		}
	}
	delete (h);
	
	Algorytm alg(in);
	wynik w = alg.obliczWynik();
	
	assert(0 == w.zakupy[0][0]);
	assert(450 == w.zakupy[0][1]);
	assert(450 == w.zakupy[0][2]);
	assert(0 == w.zakupy[1][0]);
	assert(240 == w.zakupy[1][1]);
	assert(450 == w.zakupy[1][2]);
	assert(450 == w.zakupy[2][0]);
	assert(0 == w.zakupy[2][1]);
	assert(300 == w.zakupy[2][2]);
	
	assert(0 == w.koszty[0][0]);
	assert(31500 == w.koszty[0][1]);
	assert(40945.5 == w.koszty[0][2]);
	assert(0 == w.koszty[1][0]);
	assert(19200 == w.koszty[1][1]);
	assert(31500 == w.koszty[1][2]);
	assert(36000 == w.koszty[2][0]);
	assert(0 == w.koszty[2][1]);
	assert(30000 == w.koszty[2][2]);
}

main() {
	std::cout << "Test oblicz wynik\n";
	test_obliczWynik();
}