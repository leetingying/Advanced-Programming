#ifndef CLOUD_H
#define CLOUD_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

struct Cloud
{
	int x, y;
	int cloudcover;
};
extern Cloud * cloudA;
extern string ** cloudPtr;

void populateCloud(string cloudfile, int row, int col);
void displayCloudByIndex(int row, int col);
void displayCloudBySym(int row, int col);
void deleteCloudMem(int row, int col);

#endif
