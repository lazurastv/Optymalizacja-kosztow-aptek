#ifndef _MAIN_H
#define _MAIN_H

struct building {
	int ID;
	std::string name;
	int count;
};

struct deal {
	int max;
	float price;
};

struct ret_array {
	building* builds;
	int amount = 0;
};

ret_array getBuildingData(std::ifstream&, std::string);

#endif