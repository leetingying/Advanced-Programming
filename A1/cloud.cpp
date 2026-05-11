#ifndef CLOUD_CPP
#define CLOUD_CPP
#include "cloud.h"
#include "otherfunc.h"

using namespace std;

//dynamic array of struct Cloud
Cloud * cloudA = nullptr;
//dynamic 2D array to store string cloudcover data mapped by coordinates
string ** cloudPtr = nullptr;

//Purpose of function: Read cloud data from a file, create cloud objects, place them in a 2D grid(map) and initializes cloudA and cloudPtr
void populateCloud(string cloudfile, int row, int col)
{
	//clean file formatting to remove white spaces
	cleanFile(cloudfile);
	
	ifstream cloudData(cloudfile);
	string line;
	
	int totalLength =0;
	
	if (cloudData.is_open())
	{
		//Count the number of non-empty lines in the file
		while(getline(cloudData, line))
		{
			if(!line.empty())
			{
				totalLength++;
			}
		}
		cloudData.close();
		
		ifstream cloudDataAgain(cloudfile);
		int linecount = 0;
		
		//initialize cloud array with the number of lines counted above as the size
		cloudA = new Cloud[totalLength];
		
		while(getline(cloudDataAgain, line))
		{
			//Parsing of data
			//First split by "-"
			//will get [0]=(x,y) and [1] = cloudcover
			vector<string> splitdata = tokenizeString(line, "-");
			//if the split is less than 2, the format is incorrect
			if (splitdata.size() != 2) {
				cerr << "Invalid line (no dash): " << line << endl;
				continue;
			}
			
			//Second split by ","
			//will get [0]= (x and [1] = y)
			vector<string> cloudCoord = tokenizeString(splitdata[0], ",");
			//if the split is less than 2, the format for coordinates is incorrect
			if (cloudCoord.size() != 2) {
				cerr << "Invalid coordinates: " << splitdata[0] << endl;
				continue;
			}
			
			//check if coord split first index is empty
			if (!cloudCoord[0].empty())
			{
				//Removes ( from (x
				cloudCoord[0].erase(cloudCoord[0].begin());
			}
			
			//Check if coord split second index is empty
			if (!cloudCoord[1].empty())
			{
				//Remove ) from y)
				cloudCoord[1].erase(cloudCoord[1].end() - 1);
			}
			try 
			{
				//Store the data into cloud array using the linecount as the index
				cloudA[linecount].x = stoi(cloudCoord[0]);
				cloudA[linecount].y = stoi(cloudCoord[1]);
				cloudA[linecount].cloudcover = stoi(splitdata[1]);
			}	
			catch (exception& e) 
			{
				// catch any error and display the error message with the error 
				cerr << "Parsing error in line: " << line << " — " << e.what() << endl;
				continue;
			}
			linecount++;
		}
		cloudDataAgain.close();
		
		//check that the input for row and col is not 0
		//if  is 0, a map cannot be drawn
		if (row <= 0 || col <= 0) {
			cerr << "Error: Invalid map size (" << row << ", " << col << ")." << endl;
			return;
		}
		
		//initializing dynamic 2D array 
		cloudPtr = new string * [row];
		
		for (int i = 0; i < row; i++)
		{
			cloudPtr[i] = new string [col];
			for (int j = 0; j <col; j++)
			{
				//for any points without value, empty string
				cloudPtr[i][j] = "";
			}
		}
		
		for (int z = 0; z <totalLength; z++)
		{
			int x = cloudA[z].x;
			int y = cloudA[z].y;

			if (x >= 0 && x < col && y >= 0 && y < row) {
				//using cloud cover values to represent each x,y coord grid
				cloudPtr[y][x] = to_string(cloudA[z].cloudcover);
			} else {
				cerr << "Warning: Ignored out-of-bounds cloud point (" << x << "," << y << ")" << endl;
			}
		}
	}
	else
	{
		cerr << "Error: Unable to open this file : " << cloudfile <<endl; 
	}
	
	
}

//Purpose of function: Display the grid using numeric 0-9 instead of the raw cloud values
void displayCloudByIndex(int row, int col)
{
	cout << endl;
	int maxL=0;
	for (int i =0; i<row; i++)
		for (int j=0; j<col;j++)
			maxL= max(maxL, (int)cloudPtr[i][j].length());
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
            if (cloudPtr[i][j] =="")
            {
            	//if there is no data received for the gridpoint, ? will be shown
            	cout << setw(cellWidth) << "?";
            }
            else
            {
            	//printing the cloudcover onto its point after conversion 
            	cout << setw(cellWidth) << sortIndex(stoi(cloudPtr[i][j]));
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

//Purpose of function: Similar to the displayCloudByIndex but shows symbols instead
void displayCloudBySym(int row, int col)
{
	cout << endl;
	int maxL=0;
	for (int i =0; i<row; i++)
		for (int j=0; j<col;j++)
			maxL= max(maxL, (int)cloudPtr[i][j].length());
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
            if (cloudPtr[i][j] =="")
            {
            	//if there is no data received for the gridpoint, ? will be shown
            	cout << setw(cellWidth) << "?";
            }
            else
            {
            	//printing the cloudcover symbol onto its point after conversion 
            	cout << setw(cellWidth) << sortSymbol(stoi(cloudPtr[i][j]));
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
void deleteCloudMem(int row, int col)
{
	if(cloudPtr != nullptr)
	{
		for (int i = 0; i < row; i++)
		{
			//delete each row of 2D array
			delete[] cloudPtr[i];
		}
		delete[] cloudPtr;
		cloudPtr=nullptr;
	}
	if(cloudA != nullptr)
	{
		delete[] cloudA;
		cloudA=nullptr;
	}
}


#endif

