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

std::string getFileName(int, char**);

std::ifstream getFile(std::string);

bool fileExists(std::ifstream&);

ret_array getBuildingData(std::ifstream&, std::string);

#endif
