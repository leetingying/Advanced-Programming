#ifndef OTHERFUNC_H
#define OTHERFUNC_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> tokenizeString(string input, string delimiter);
string trim(string str);
void cleanFile(string filename);
string readLastNonEmpty(string filename);

int sortIndex(int sN);
string sortSymbol(int sN);

void Freeze();

#endif
