#ifndef CITY_CPP
#define CITY_CPP
#include "city.h"
#include "otherfunc.h"

using namespace std;

//dynamic array of struct City
City * cityA = nullptr;
//dynamic 2D array to store string cityID mapped by coordinates
string ** cityPtr = nullptr;

//Purpose of function: Read city data from a file, create city objects, place them in a 2D grid(map) and initializes cityA and cityPtr
void populateCity(string cityfile, int row, int col)
{
	// clean the file formatting to remove any extra white spaces
	cleanFile(cityfile);
	
	ifstream cityData(cityfile);
	string line;
	int totalLength = 0;
	
	if(cityData.is_open())
	{
		//count the number of lines in the file
		while (getline(cityData, line))
		{
			if(!line.empty())
			{
				totalLength++;
			}
		}
		cityData.close();
		
		// initialize the city array with the number of lines counted above
		cityA = new City[totalLength];
		
		ifstream cityDataAgain(cityfile);
		int linecount = 0;
		while (getline(cityDataAgain,line))
		{
			//Parsing of data
			//First split the line by "-" 
			//will get [0] = [x, y], [1] = cityID, [2] = cityName
			vector<string> splitdata = tokenizeString(line,"-");
			
			//to check if the size of the split, if it is less than 3, there is input missing
			if (splitdata.size() < 3) {
				cerr << "Invalid line format: " << line << endl;
				continue;
			}
			
			//Second split by ","
			//will get [0] = [x and [1] = y]
			vector<string> cityCoord = tokenizeString(splitdata[0], ",");
			//if this split is less than 2, the format is wrong
			if (cityCoord.size() != 2) {
				cerr << "Invalid coordinates: " << splitdata[0] << endl;
				continue;
			}
			
			//check that coordinates split first index is not empty
			if (!cityCoord[0].empty()) 
			{
				//Remove [ from [x
				cityCoord[0].erase(cityCoord[0].begin());
			}
			
			//check that coordinates split second index is not empty
			if (!cityCoord[1].empty())
			{ 
				//Remove ] from y]
				cityCoord[1].erase(cityCoord[1].end() - 1); 
			}
			
			try 
			{
				//store the data retrieve after spliting into city array
				//index by linecount
				cityA[linecount].x = stoi(cityCoord[0]);
				cityA[linecount].y = stoi(cityCoord[1]);
				cityA[linecount].cityID = stoi(splitdata[1]);
				cityA[linecount].cityName = splitdata[2];
			} 
			catch (exception& e) {
				// catch any error and display the error message with the error 
				cerr << "Parsing error in line: " << line << " — " << e.what() << endl;
				continue;
			}
			linecount++;
		}
		cityDataAgain.close();
		
		//check that the input for row and col is not 0
		//if  is 0, a map cannot be drawn
		if (row <= 0 || col <= 0) {
			cerr << "Error: Invalid map size (" << row << ", " << col << ")." << endl;
			return;
		}
		
		//Create 2D map Array
		cityPtr = new string*[row];
		for (int i = 0; i < row; i++) {
			cityPtr[i] = new string[col];
			for (int j = 0; j < col; j++) {
				//for the grids without any data, display as empty string
				cityPtr[i][j] = "";
			}
		}
		
		for (int z = 0; z < linecount; z++)
		{
			int x = cityA[z].x;
			int y = cityA[z].y;
			
			//Place cities on the map by using cityID to represent
			if (x >= 0 && x < col && y >= 0 && y < row) {
				cityPtr[y][x] = to_string(cityA[z].cityID);
			} else {
				cerr << "Warning: Ignored out-of-bounds city point (" << x << "," << y << ")" << endl;
			}
		}
	}
	else
	{
		cerr << "Error:Unable to open this file: " << cityfile <<endl;
	}
}

//Purpose of function: Display the map grid in the terminal
void displaycitymap(int row, int col)
{
	cout << endl;
	int maxL=0;
	for (int i =0; i<row; i++)
		for (int j=0; j<col;j++)
			maxL= max(maxL, (int)cityPtr[i][j].length());
	//determine the widest cell to ensure that the spacing looks clean
    int cellWidth = maxL +2; 
	cout<<endl;
	
    // Printing top boundary
    //Offset for the boundary to match the left and right boundary
    //the top boundary does not have y axis hence the offset
    cout << setw(4) << " "; 
    for (int j = 0; j < col+1; ++j) {
        cout << setw(cellWidth) << "#";
    }
    cout << setw(cellWidth) << "#" << endl;

    // Printing y axis along with the left and right boundary box 
    //including the data for the map
    for (int i = row - 1; i >= 0; --i) {
    	// print the y axis
        cout << setw(2) << i << "    #";
		
		//printing the cityID onto its point and any other points will be empty string
        for (int j = 0; j < col; ++j) {
            cout << setw(cellWidth) << cityPtr[i][j];
        }

        cout << setw(cellWidth) << "#" << endl;
    }

    // Printing bottom boundary
    //Offset for the boundary to match the left and right boundary
    //the bottom boundary does not have y axis hence the offset
    cout << setw(4) << " "; 
    for (int j = 0; j < col+1; ++j) {
        cout << setw(cellWidth) << "#";
    }
    cout << setw(cellWidth) << "#" << endl;

    // Printing x axis
    //Offset for the x axis to match the boundary lines and data correctly
    cout << setw(7) << " "; 
    for (int j = 0; j < col; ++j) {
        cout << setw(cellWidth)<< j;
    }
    cout << endl;
}

//Purpose of function: Free all dynamically allocated memory
void deleteCityMem(int row, int col)
{
	if (cityPtr != nullptr)
	{
		//delete each row of  cityPtr
		for (int i = 0; i < row; i++)
		{
			delete[] cityPtr[i];
		}
		//delete the array
		delete[] cityPtr;
		// set to nullptr for safety
		cityPtr=nullptr;
	}
	if (cityA != nullptr)
	{
		//delete City Array and set to nullptr for safety
		delete[] cityA;
		cityA=nullptr;
	}
}




#endif
