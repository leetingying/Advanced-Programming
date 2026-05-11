#ifndef PRESSURE_H
#define PRESSURE_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

struct Pressure
{
	int x, y;
	int pressure;
};

extern Pressure * pressureA;
extern string ** pressurePtr;

void populatePressure(string pressurefile, int row, int col);
void displayPressureByIndex(int row, int col);
void displayPressureBySym(int row, int col);
void deletePressureMem(int row, int col);

#endif
