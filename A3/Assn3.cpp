#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "menu.h"

using namespace std;

int main() {
	string input;
	int choice = 0;
	do
	{
		displayMenu();
		cout << "Please enter your choice : ";
		getline(cin, input);
		if (!input.empty() && input.length() == 1 && isdigit(input[0])) 
		{
			//convert char digit to int
			choice = input[0] - '0';
			if (choice < 1 || choice > 7) 
			{
				cout <<"Invalid input. Please enter a digit between 1 and 7." << endl;
				continue;
			}
		} 
		else 
		{
			cout << "Invalid input. Please enter a single digit only." << endl;;
			continue;
		}
		
		switch(choice)
		{
			case 1:
				readFile();
				break;
			case 2:
				filterCriteriaOption();
				break;
			case 3:
				sortCriteriaOption();
				break;
			case 4:
				sortOrderOption();
				break;
			case 5:
				displayDataOption();
				break;
			case 6: 
				storeDataOption();
				break;
			case 7:
				cout << "You have chosen to quit the program!" << endl;
				break;
			default:
				cout << "Invalid choice! Please try again" << endl;
		}
	}
	while (choice != 7);
    return 0;
}

