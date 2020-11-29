#ifndef _WYNIK_H_
#define _WYNIK_H_

struct wynik {
	int** zakupy;
	double** koszty;
	int fabryki;
	int apteki;
	wynik(int, int);
	wynik(const wynik&);
	wynik();
	~wynik();
};

#endif