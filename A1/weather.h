#ifndef WEATHER_H
#define WEATHER_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

struct WeatherReport{
	string cityName;
	int cityID;
	double AvgCC, AvgP, Rainp;
	string cloudSym, pressureSym;
};

void weatherReport(int arrLength, int totalCity, int totalLength);

void sortRainprob(string cloud, string pressure);

#endif
