#ifndef PRESSURE_CPP
#define PRESSURE_CPP
#include "pressure.h"
#include "otherfunc.h"

using namespace std;

//dynamic array of struct Pressure
Pressure * pressureA = nullptr;
//dynamic 2D array to store string pressure data mapped by coordinates
string ** pressurePtr = nullptr;

//Purpose of function: Read pressure data file, create pressure objects, , place them in a 2D grid(map) and initializes pressureA and pressurePtr
void populatePressure(string pressurefile, int row, int col)
{
	//clean the file formatting from extra whitespace
	cleanFile(pressurefile);
	ifstream pressureData(pressurefile);
	string line;
	
	int totalLength =0;
	
	if (pressureData.is_open())
	{
		//count the number of non-empty lines in the file
		while(getline(pressureData, line))
		{
			if(!line.empty())
			{
				totalLength++;
			}
		}
		pressureData.close();
		
		ifstream pressureDataAgain(pressurefile);
		int linecount = 0;
		//initialise pressure array by using the number of lines counted above as the size
		pressureA = new Pressure[totalLength];
		
		while(getline(pressureDataAgain, line))
		{
			//Parsing of data
			//First split by "-"
			//will get [0]=(x,y) and [1] =pressure value
			vector<string> splitdata = tokenizeString(line, "-");
			//if the split is less than 2, the format is incorrect
			if (splitdata.size() < 2) {
				cerr << "Invalid line format: " << line << endl;
				continue;
			}
			
			//Second split by ","
			//will get [0]= (x and [1] = y)
			vector<string> pressureCoord = tokenizeString(splitdata[0], ",");
			//if the split is less than 2, the format for coordinates is incorrect
			if (pressureCoord.size() != 2) {
				cerr << "Invalid coordinates: " << splitdata[0] << endl;
				continue;
			}
			
			//check if coord split first index is empty
			if (!pressureCoord[0].empty())
			{
				//Removes ( from (x
				pressureCoord[0].erase(pressureCoord[0].begin());
			}
			
			//Check if coord split second index is empty
			if (!pressureCoord[1].empty()) 
			{
				//Remove ) from y)
				pressureCoord[1].erase(pressureCoord[1].end() - 1);
			}
			
			try 
			{
				//Store the data into pressure array using the linecount as the index
				pressureA[linecount].x = stoi(pressureCoord[0]);
				pressureA[linecount].y = stoi(pressureCoord[1]);
				pressureA[linecount].pressure = stoi(splitdata[1]);
			} 
			catch (exception& e) 
			{
				// catch any error and display the error message with the error 
				cerr << "Parsing error in line: " << line << " — " << e.what() << endl;
				continue;
			}
			linecount++;
		}
		pressureDataAgain.close();
		
		//check that the input for row and col is not 0
		//if  is 0, a map cannot be drawn
		if (row <= 0 || col <= 0) {
			cerr << "Error: Invalid map size (" << row << ", " << col << ")." << endl;
			return;
		}

		//Initializing dynamic 2Darray
		pressurePtr = new string * [row];
		
		for (int i = 0; i < row; i++)
		{
			pressurePtr[i] = new string [col];
			for (int j = 0; j <col; j++)
			{
				//for the grids without any data, display as empty string
				pressurePtr[i][j] = "";
			}
		}
		
		for (int z = 0; z <totalLength; z++)
		{
			int x = pressureA[z].x;
			int y = pressureA[z].y;

			if (x >= 0 && x < col && y >= 0 && y < row) {
				//using pressure values to represent each x,y coord grid
				pressurePtr[y][x] = to_string(pressureA[z].pressure);
			} else {
				cerr << "Warning: Ignored out-of-bounds pressure point (" << x << "," << y << ")" << endl;
			}
		}
	}
	else
	{
		cerr << "Error: Unable to open this file : " << pressurefile <<endl; 
	}
	
} 

//Purpose of function: Display the grid using numeric 0-9 instead of the raw pressure values
void displayPressureByIndex(int row, int col)
{
	cout << endl;
	int maxL=0;
	for (int i =0; i<row; i++)
		for (int j=0; j<col;j++)
			maxL= max(maxL, (int)pressurePtr[i][j].length());
	//determine the widest cell to ensure that the spacing looks clean
    int cellWidth = maxL +2; 
	cout<<endl;
    
    // Printing top boundary
    //Offset for the boundary to match the left and right boundary
    //the top boundary does not have y axis hence the offset
    cout << setw(3) << " "; 
    for (int j = 0; j < col+1; j++) {
        cout << setw(cellWidth) << "#";
    }
    cout << setw(cellWidth) << "#" << endl;

    // Printing y axis along with the left and right boundary box 
    //including the data for the map
    for (int i = row - 1; i >= 0; i--) {
         // print the y axis
        cout << setw(2) << i << "    #";

        for (int j = 0; j < col; j++) {
            if (pressurePtr[i][j] =="")
            {
            	//if there is no data received for the gridpoint, ? will be shown
            	cout << setw(cellWidth) << "?";
            }
            else
            {
            	//printing the pressure onto its point after conversion
            	cout << setw(cellWidth) << sortIndex(stoi(pressurePtr[i][j]));
            }
        }

        cout << setw(cellWidth) << "#" << endl;
    }

    // Printing bottom boundary
    //Offset for the boundary to match the left and right boundary
    //the bottom boundary does not have y axis hence the offset
    cout << setw(3) << " "; 
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

//Purpose of function: Similar to displayPressureByIndex but shows symbols instead
void displayPressureBySym(int row, int col)
{
	cout << endl;
	int maxL=0;
	for (int i =0; i<row; i++)
		for (int j=0; j<col;j++)
			maxL= max(maxL, (int)pressurePtr[i][j].length());
	//determine the widest cell to ensure that the spacing looks clean
    int cellWidth = maxL +2; 
	cout<<endl;
    
    // Printing top boundary
    //Offset for the boundary to match the left and right boundary
    //the top boundary does not have y axis hence the offset
    cout << setw(3) << " "; 
    for (int j = 0; j < col+1; j++) {
        cout << setw(cellWidth) << "#";
    }
    cout << setw(cellWidth) << "#" << endl;

    // Printing y axis along with the left and right boundary box 
    //including the data for the map
    for (int i = row - 1; i >= 0; i--) {
        // print the y axis
        cout << setw(2) << i << "    #";

        for (int j = 0; j < col; j++) {
            if (pressurePtr[i][j] =="")
            {
            	//if there is no data received for the gridpoint, ? will be shown
            	cout << setw(cellWidth) << "?";
            }
            else
            {
            	//printing the pressure symbol onto its point after conversion 
            	cout << setw(cellWidth) << sortSymbol(stoi(pressurePtr[i][j]));
            }
        }

        cout << setw(cellWidth) << "#" << endl;
    }

    // Printing bottom boundary
    //Offset for the boundary to match the left and right boundary
    //the bottom boundary does not have y axis hence the offset
    cout << setw(3) << " "; 
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

//Purpose of function: Free all dynamically allocated memory and set pointers to nullptr for safety
void deletePressureMem(int row, int col)
{
	if(pressurePtr != nullptr)
	{
		for (int i = 0; i < row; i++)
		{
			//delete each row of 2D array
			delete[] pressurePtr[i];
		}
		delete[] pressurePtr;
		pressurePtr=nullptr;
	}
	if(pressureA != nullptr)
	{
		delete[] pressureA;
		pressureA=nullptr;
	}
}


#endif
