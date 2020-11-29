#include <cassert>
#include <iostream>
#include "../src/Algorytm/graf.h"
#include "../src/Algorytm/alg.h"
#include "../src/Algorytm/wynik.h"

void test_obliczWynik() {
	graf g;
	g.wezly = 8;
	g.limity = new int*[8];
	g.koszty = new double*[8];
	for (int i = 0; i < 8; i++) {
		g.limity[i] = new int[8];
		g.koszty[i] = new double[8];
		for (int j = 0; j < 8; j++) {
			g.limity[i][j] = 0;
			g.koszty[i][j] = 0;
		}
	}
	g.limity[0][1] = 900;
	g.limity[0][2] = 1300;
	g.limity[0][3] = 1100;
	g.limity[4][7] = 450;
	g.limity[5][7] = 690;
	g.limity[6][7] = 1200;
	
	g.limity[1][4] = 800;
	g.koszty[1][4] = 70.5;
	g.limity[2][4] = 900;
	g.koszty[2][4] = 100;
	g.limity[3][4] = 900;
	g.koszty[3][4] = 80;
	
	g.limity[1][5] = 600;
	g.koszty[1][5] = 70;
	g.limity[2][5] = 600;
	g.koszty[2][5] = 80;
	g.limity[3][5] = 900;
	g.koszty[3][5] = 90;
	
	g.limity[1][6] = 750;
	g.koszty[1][6] = 90.99;
	g.limity[2][6] = 450;
	g.koszty[2][6] = 70;
	g.limity[3][6] = 300;
	g.koszty[3][6] = 100;
	
	Algorytm alg(3, 3);
	wynik w = alg.obliczWynik(g);
	
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