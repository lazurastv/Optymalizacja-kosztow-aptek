#ifndef _WYNIK_H_
#define _WYNIK_H_

struct wynik {
	int** zakupy;
	double** koszty;
	wynik(int, int);
	wynik() {};
	~wynik();
};

#endif