#include <iostream>
#include <string>
#include "input.h"

bool budynek::operator > (budynek a) {
	return ID > a.ID;
}

bool handel::operator > (handel a) {
	if (ID_fabryki == a.ID_fabryki) {
		return ID_apteki > a.ID_apteki;
	} else {
		return ID_fabryki > a.ID_fabryki;
	}
}