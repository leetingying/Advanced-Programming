#ifndef CITY_H
#define CITY_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

struct City
{
	int x, y, cityID;
	string cityName;
};

extern City * cityA;
extern string ** cityPtr;

void populateCity(string cityfile, int row, int col);
void displaycitymap(int x, int y);
void deleteCityMem(int row, int col);

#endif
