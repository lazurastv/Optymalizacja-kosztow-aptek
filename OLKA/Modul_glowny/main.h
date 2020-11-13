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

struct buildings_with_size {
	building* buildings;
	int size = 0;
};

std::string getFileName(int, char**);

std::ifstream getFile(std::string);

bool fileExists(std::ifstream&);

buildings_with_size getBuildingData(std::ifstream&, std::string, int);

#endif
