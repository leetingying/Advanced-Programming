#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <iostream>
#include <iomanip>
#include "functions.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"

//to remove unwanted characters from lines of input data
std::string removeChars(const std::string&, const std::string&);

//function to print display menu with options, studentID and studentName
void displayMenu();

//function to take in the data from input file and store in respective vectors
void readFile();

//function to allow user to select which class objects they want to sort
void filterCriteriaOption();

//function to allow user to select the criteria to sort e.g. x or y of Points, pt. 1 of lines
void sortCriteriaOption();

//function to allow user to select to sort by ascending or descending
void sortOrderOption();

//function to print the data output for display
void displayDataOption();

//function to allow user to input a file name and store the output data into the file  
void storeDataOption();

#endif
