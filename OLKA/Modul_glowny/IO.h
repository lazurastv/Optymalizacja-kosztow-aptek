#include "input.h"

#ifndef _IO_H_
#define _IO_H_

std::ifstream przygotujPlik(std::string);

bool plikIstnieje(std::ifstream&);

bool liczbaNaturalna(float);

buildings_with_size getBuildingData(std::ifstream&, std::string, int);

input wczytajDane(char*);

#endif
