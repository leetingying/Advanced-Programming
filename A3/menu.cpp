#include "menu.h"
#include <limits>
using namespace std;

//vectors to store the data read from the input file
vector<Point2D> p2D;
vector<Point3D> p3D;
vector<Line2D> l2D;
vector<Line3D> l3D;

string studentID = "8551741";
string studentName = "Lee Ting Ying";
//variables to control how the data is to be sorted
//initialize the variables based on the default option
string filterCriteria = "Point2D";
string sortCriteria = "x-ordinate";
string sortOrder = "ASC";
string inputFile;

ostringstream finalOut;

//function to remove unwanted characters line of data read from input file
string removeChars(const string& input, const string& chars) {
    string result = input;
    for (char c : chars) {
        result.erase(remove(result.begin(), result.end(), c), result.end());
    }
    return result;
}

//Print the display menu with the studentID and studentName included
void displayMenu()
{
	cout << endl;
	cout << "Student ID	: " << studentID << endl;
	cout << "Student Name	: " << studentName << endl;
	cout << "--------------------------------------------" << endl;
	cout << "Welcome to Assn3 program!" << endl;
	cout << endl;
	cout << "1)	Read in data" << endl;
	cout << "2)	Specify filtering criteria (current : " << filterCriteria << ")" << endl;
	cout << "3)	Specify sorting criteria (current : " << sortCriteria << ")" << endl;
	cout << "4)	Specify sorting order (current : " << sortOrder << ")" << endl;
	cout << "5)	View data" << endl;
	cout << "6)	Store data" << endl;
	cout << "7)	Quit" << endl;
	cout << endl;
}

//function for user to enter data file name, read the data and store them in the respective vectors
void readFile()
{
	cout << endl;
	cout << "Please enter filename : ";
	getline(cin, inputFile);
	cout << endl;
	if (inputFile.empty())
	{
		cout << inputFile << " is empty " << endl;
		return;
	}
	
	ifstream file(inputFile);
	if(!file.is_open())
	{
		cerr << "Error: Unable to open file " << inputFile << endl;
		return;
	}
	
	set<string> uniqueline;
	string line;
	
	while(getline(file, line))
	{
		if(!uniqueline.insert(line).second)
		{
			continue;
		}
		
		istringstream iss(line);
		string type;
		getline(iss, type, ',');
		type = removeChars(type, " \t");

        string rest;
        getline(iss, rest);
        rest = removeChars(rest, "[],");

        istringstream dataStream(rest);
        vector<int> values;
        int val;
        while (dataStream >> val) {
            values.push_back(val);
        }

        if (type == "Point2D" && values.size() == 2) 
        {
            p2D.emplace_back(values[0], values[1]);
        } 
        else if (type == "Point3D" && values.size() == 3) 
        {
            p3D.emplace_back(values[0], values[1], values[2]);
        } 
        else if (type == "Line2D" && values.size() == 4) 
        {
            l2D.emplace_back(Point2D(values[0], values[1]), Point2D(values[2], values[3]));
        } 
        else if (type == "Line3D" && values.size() == 6) 
        {
            l3D.emplace_back(
                Point3D(values[0], values[1], values[2]),
                Point3D(values[3], values[4], values[5])
            );
        }
    }
    file.close();

    int totalCount = p2D.size() + p3D.size() + l2D.size() + l3D.size();
    cout << endl;
    cout << totalCount << " records read in successfully!" << endl;
    cout << endl;
    cout << "Going back to main menu ..." << endl; 
}

//function to print the filtering criteria and let the user choose the criteria they want
//then update the criteria based on the user option and set the respective default sort criteria
void filterCriteriaOption()
{
	cout << endl;
	cout << "[ Specify filtering criteria (current : " << filterCriteria << ") ]" << endl;
	cout << endl;
	cout << "	a)	Point2D records" << endl;
	cout << "	b)	Point3D records" << endl;
	cout << "	c)	Line2D records" << endl;
	cout << "	d)	Line3D records" << endl;
	cout << endl;
	cout << "	Please enter your criteria (a - d) : ";
	string input;
	getline(cin, input);
	char choice = input.empty() ? ' ' : tolower(input[0]);
	cout << endl;
	
	switch (choice)
	{
		case 'a':
			filterCriteria = "Point2D";
			sortCriteria = "x-ordinate";
			break;
			
		case 'b':
			filterCriteria = "Point3D";
			sortCriteria = "x-ordinate";
			break;
			
		case 'c':
			filterCriteria = "Line2D";
			sortCriteria = "Pt. 1";
			break;
			
		case 'd':
			filterCriteria = "Line3D";
			sortCriteria = "Pt. 1";
			break;
			
		default:
			cout << "Invalid filtering option! Keeping current filter criteria : " << filterCriteria << endl;
			return;
	}
	
	if (filterCriteria == "Point2D")
	{
		p2D = sortP2D(p2D, sortCriteria, sortOrder);
	}
	else if (filterCriteria == "Point3D")
	{
		p3D = sortP3D(p3D, sortCriteria, sortOrder);
	}
	else if (filterCriteria == "Line2D")
	{
		l2D = sortL2D(l2D, sortCriteria, sortOrder);
	}
	else if (filterCriteria == "Line3D")
	{
		l3D = sortL3D(l3D, sortCriteria, sortOrder);
	}
	
	cout << "	Filter criteria successfully set to '" << filterCriteria << "'!" << endl;
	cout << endl;
}

//function to display the options for criteria based on filter criteria
//then let user to choose the criteria they want to sort by 
void sortCriteriaOption()
{
	cout << endl;
	cout << "[ Specify sorting criteria (current : " << sortCriteria << ") ]" << endl;
	cout << endl;
	string finalOption;
	
	if(filterCriteria == "Point2D")
	{
		finalOption = "c";
		cout << "	a) x-ordinate value" << endl;
		cout << "	b) y-ordinate value" << endl;
		cout << "	c) Dist. Fr Origin value" << endl;
	}
	else if(filterCriteria == "Point3D")
	{
		finalOption = "d";
		cout << "	a) x-ordinate value" << endl;
		cout << "	b) y-ordinate value" << endl;
		cout << "	c) z-ordinate value" << endl;
		cout << "	d) Dist. Fr Origin value" << endl;
	}
	else if(filterCriteria == "Line2D")
	{
		finalOption = "c";
		cout << "	a) Pt. 1's (x, y) values" << endl;
		cout << "	b) Pt. 2's (x, y) values" << endl;
		cout << "	c) Length value" << endl;
	}
	else if(filterCriteria == "Line3D")
	{
		finalOption = "c";
		cout << "	a) Pt. 1's (x, y) values" << endl;
		cout << "	b) Pt. 2's (x, y) values" << endl;
		cout << "	c) Length value" << endl;
	}
	else
	{
		cout << "Invalid sorting criteria!" << endl;
		return;
	}
	
	cout << endl;
	cout << "	Please enter your criteria (a - " << finalOption << ") : ";
	string input;
	getline(cin, input);
	char choice = input.empty() ? ' ' : tolower(input[0]);
	if(filterCriteria == "Point2D")
	{
		switch (choice)
		{
			case 'a':
				sortCriteria = "x-ordinate";
				break;
				
			case 'b':
				sortCriteria = "y-ordinate";
				break;
				
			case 'c':
				sortCriteria = "Dist. Fr Origin";
				break;
				
			default:
				cout << "Invalid sorting criteria! Keeping current sorting criteria: " << sortCriteria << endl;
				return;
		}
	}
	else if(filterCriteria == "Point3D")
	{
		switch (choice)
		{
			case 'a':
				sortCriteria = "x-ordinate";
				break;
				
			case 'b':
				sortCriteria = "y-ordinate";
				break;
				
			case 'c':
				sortCriteria = "z-ordinate";
				break;
				
			case 'd':
				sortCriteria = "Dist. Fr Origin";
				break;
				
			default:
				cout << "Invalid sorting criteria! Keeping current sorting criteria: " << sortCriteria << endl;
				return;
		}		
	}
	else if(filterCriteria == "Line2D")
	{
		switch (choice)
		{
			case 'a':
				sortCriteria = "Pt. 1";
				break;
				
			case 'b':
				sortCriteria = "Pt. 2";
				break;
				
			case 'c':
				sortCriteria = "Length";
				break;
				
			default:
				cout << "Invalid sorting criteria! Keeping current sorting criteria: " << sortCriteria << endl;
				return;
		}
	}
	else if(filterCriteria == "Line3D")
	{
		switch (choice)
		{
			case 'a':
				sortCriteria = "Pt. 1";
				break;
				
			case 'b':
				sortCriteria = "Pt. 2";
				break;
				
			case 'c':
				sortCriteria = "Length";
				break;
				
			default:
				cout << "Invalid sorting criteria! Keeping current sorting criteria: " << sortCriteria << endl;
				return;
		}
	}
	
	if (filterCriteria == "Point2D")
	{
		p2D = sortP2D(p2D, sortCriteria, sortOrder);
	}
	else if (filterCriteria == "Point3D")
	{
		p3D = sortP3D(p3D, sortCriteria, sortOrder);
	}
	else if (filterCriteria == "Line2D")
	{
		l2D = sortL2D(l2D, sortCriteria, sortOrder);
	}
	else if (filterCriteria == "Line3D")
	{
		l3D = sortL3D(l3D, sortCriteria, sortOrder);
	}
	
	cout << endl;
	cout << "	Sorting criteria successfully set to '" << sortCriteria << "'!" << endl;
}

//function to get user to choose which order they want to sort the data by
void sortOrderOption()
{
	cout << endl;
	cout << "[ Specify sorting order (current : " << sortOrder << ") ]" << endl;
	cout << endl;
	cout << "	a) ASC (Ascending order)" << endl;
	cout << "	b) DSC (Descending order)" << endl;
	cout << endl;
	cout << "	Please enter your choice (a - b) : ";
	string input;
	getline(cin, input);
	char choice = input.empty() ? ' ' : tolower(input[0]);

	
	switch (choice)
	{
		case 'a':
			sortOrder = "ASC";
			break;
		
		case 'b':
			sortOrder = "DSC";
			break;
			
		default:
			cout << "Invalid order choice! Keeping current sorting order " << sortOrder << endl;
			return;
	}
	
	if (filterCriteria == "Point2D")
	{
		p2D = sortP2D(p2D, sortCriteria, sortOrder);
	}
	else if (filterCriteria == "Point3D")
	{
		p3D = sortP3D(p3D, sortCriteria, sortOrder);
	}
	else if (filterCriteria == "Line2D")
	{
		l2D = sortL2D(l2D, sortCriteria, sortOrder);
	}
	else if (filterCriteria == "Line3D")
	{
		l3D = sortL3D(l3D, sortCriteria, sortOrder);
	}
	
	cout << endl;
	cout << "	Sorting order successfully set to '" << sortOrder << "'!" << endl;
}

//function to store the output as a oss before printing it as a display
void displayDataOption()
{
	finalOut.str("");
	finalOut.clear();
	bool datavalid = false;

	finalOut << "[ View data ... ]" << endl;
	finalOut << " filtering criteria : " << filterCriteria << endl;
	finalOut << " sorting criteria : " << sortCriteria << endl;
	finalOut << " sorting order : " << sortOrder << endl;
	if (filterCriteria == "Point2D" &&!p2D.empty())
	{
		finalOut << setw(5) << "X" << setw(6) << "Y" << setw(19) << "Dist. Fr Origin" << endl;
		finalOut << "- - - - - - - - - - - - - - - - - - -" << endl;;
		for (const auto& p : p2D) 
		{
			finalOut << p;
		}
		cout << endl;
		datavalid = true;
	}
	else if (filterCriteria == "Point3D" && !p3D.empty())
	{
		finalOut << right << setw(5) << "X" << setw(6) << "Y" << setw(6) << "Z" << setw(19) << "Dist. Fr Origin" << endl;
		finalOut << "- - - - - - - - - - - - - - - - - - -" << endl;;
		for (const auto& p : p3D) 
		{
			finalOut << p;
		}
		cout << endl;
		datavalid = true;
	}
	else if (filterCriteria == "Line2D" && !l2D.empty())
	{
		finalOut << right << setw(5) << "P1-X" << setw(6) << "P1-Y" << setw(9) << "P2-X" << setw(6) << "P2-Y" << setw(10) << "Length" << endl;
		finalOut << "- - - - - - - - - - - - - - - - - - -" << endl;;
		for (const auto& l :  l2D) 
		{
			finalOut << l;
		}
		cout << endl;
		datavalid = true;
	}
	else if (filterCriteria == "Line3D" && !l3D.empty())
	{
		finalOut << right << setw(5) << "P1-X" << setw(6) << "P1-Y" << setw(6) << "P1-Z" << setw(9) << "P2-X" << setw(6) << "P2-Y"<< setw(6) << "P2-Z"  << setw(10) << "Length" << endl;
		finalOut << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		for (const auto& l : l3D)
		{
			finalOut << l;
		}
		cout << endl;
		datavalid = true;
	}
	
	if (!datavalid)
	{
		cout << endl;
		cout << "No data available to output" << endl;
	}
	
	cout << finalOut.str();
	cout << endl;
	cout << "Press any key to go back to the main menu...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

//function for user to input a file name and store the data into the file
void storeDataOption()
{
	string outfilename;
	bool datavalid = false;
	int count = 0;
	cout << endl;
	cout << "Please enter filename : ";
	getline(cin, outfilename);
	cout << endl;
	if (inputFile == "")
	{
		cout << endl;
		cout << "Error: No Data was inserted, Please go to option 1 and read the data file first." << endl;
		return;
	}
	
	
	ofstream outFile(outfilename);
	
	if (!outFile)
	{
		cout << endl;
		cout << "Error: Unable to create file" << endl;
		return;
	}
	if (filterCriteria == "Point2D" &&!p2D.empty())
	{
		outFile << setw(5) << "X" << setw(6) << "Y" << setw(19) << "Dist. Fr Origin" << endl;
		outFile << "- - - - - - - - - - - - - - - - - - -" << endl;;
		for (const auto& p : p2D) 
		{
			outFile << p;
			count++;
		}
		cout << endl;
		datavalid = true;
	}
	else if (filterCriteria == "Point3D" && !p3D.empty())
	{
		outFile << right << setw(5) << "X" << setw(6) << "Y" << setw(6) << "Z" << setw(19) << "Dist. Fr Origin" << endl;
		outFile << "- - - - - - - - - - - - - - - - - - -" << endl;;
		for (const auto& p : p3D) 
		{
			outFile << p;
			count++;
		}
		cout << endl;
		datavalid = true;
	}
	else if (filterCriteria == "Line2D" && !l2D.empty())
	{
		outFile << right << setw(5) << "P1-X" << setw(6) << "P1-Y" << setw(9) << "P2-X" << setw(6) << "P2-Y" << setw(10) << "Length" << endl;
		outFile << "- - - - - - - - - - - - - - - - - - -" << endl;;
		for (const auto& l :  l2D) 
		{
			outFile << l;
			count++;
		}
		cout << endl;
		datavalid = true;
	}
	else if (filterCriteria == "Line3D" && !l3D.empty())
	{
		outFile << right << setw(5) << "P1-X" << setw(6) << "P1-Y" << setw(6) << "P1-Z" << setw(9) << "P2-X" << setw(6) << "P2-Y"<< setw(6) << "P2-Z"  << setw(10) << "Length" << endl;
		outFile << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		for (const auto& l : l3D)
		{
			outFile << l;
			count++;
		}
		cout << endl;
		datavalid = true;
	}
	
	if (!datavalid)
	{
		cout << endl;
		cout << "No data available to output" << endl;
	}
	
	cout << endl;
	cout << count << " records output successfully to " << outfilename << " !" << endl;
	
	outFile.close();
	
	cout << endl;
	cout << "Going back to main menu ..." << endl;
}

