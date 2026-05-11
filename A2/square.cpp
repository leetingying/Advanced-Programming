#include "square.h"

//inherit from parent:ShapeTwoD, to get the name and special type
// Calls setCoords when constructor is called
Square::Square(string name, bool containsWarpSpace) :ShapeTwoD(name, containsWarpSpace)
{
    this -> setCoords();
}

// return the already calculated area
double Square::getArea()
{
	return area;
}

//Calculate and store result as area
double Square::computeArea() 
{
    area = abs(maxX - minX) * abs(maxY - minY);
    return area;
}

//Check if a point is inside the square 
bool Square::isPointInShape(int x, int y) 
{
	//if the point is on the edge or vertex, return false
	 if (isPointOnShape(x, y))
	 {
        return false;
    }
    if((x > minX) && (x < maxX) && (y > minY) && (y < maxY)) {
        return true;
    }
    else
    {
        return false;
    }
}

// check if the point lies on a square's perimeter
bool Square::isPointOnShape(int x, int y) 
{
    if(((minX <= x) && (x <= maxX)) && ((minY == y) || (maxY == y))){
		return true;
	}
	else if(((minX == x) || (x == maxX)) && ((minY <= y) && (y <= maxY))){
		return true;
	}
	else
    {
		return false;
    }
}

//function to collect 4 unique user input points and store in vector coordS
void Square::setCoords()
{
     coordS.clear();
     //point counter
     int i = 0;  
	
	//loop 4 times
     while (i < 4) {
     	Coord c;
        string input;
        //bool to check for valid point inputs
        bool valid = false;

        //Get X-coordinate  with input validation
        do 
        {
        	cout << "Please enter x-ordinate of pt. " << i + 1 << " : ";
            getline(cin, input);
            //trimming of input
            input.erase(0, input.find_first_not_of(" \t"));
            input.erase(input.find_last_not_of(" \t") + 1);
            try 
            {
            	c.x = stoi(input);
                valid = true;
            } 
            catch (...) 
            {
                cout << "Invalid input. Please enter a valid integer for pt. " << i + 1 << " x.\n";
            }
        }
        while (!valid);

        valid = false;

        //Get Y-coordinate  with input validation
        do 
        {
            cout << "Please enter y-ordinate of pt. " << i + 1 << " : ";
            getline(cin, input);
            //trimming of input
            input.erase(0, input.find_first_not_of(" \t"));
            input.erase(input.find_last_not_of(" \t") + 1);
            try 
            {
                c.y = stoi(input);
                valid = true;
            } 
            catch (...) 
            {
                cout << "Invalid input. Please enter a valid integer for pt. " << i + 1 << " y.\n";
            }
        } 
        while (!valid);

        // Check for duplicate points
        bool isDuplicate = false;
        for (const auto& existing : coordS) {
            if (existing.x == c.x && existing.y == c.y) {
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate) {
            cout << "Duplicate point entered. Please enter a unique vertex.\n";
            // retries for the same point if the point inputted is duplicate
            continue;
        }

        // Add unique point and move on
        coordS.push_back(c);
        i++;
        

		if (i==4) {
		    minX = maxX = coordS[0].x;
		    minY = maxY = coordS[0].y;
		    //Bounding box calculation 
		    //loop through all coordinates in coordS, set the min and max x y values
		    for (const auto& coord : coordS) {
		        minX = min(minX, coord.x);
		        maxX = max(maxX, coord.x);
		        minY = min(minY, coord.y);
		        maxY = max(maxY, coord.y);
		    }
		    int length = abs(maxX - minX);
		    int height = abs(maxY - minY);
			
			//check if the input data forms a square
		    if (length != height) {
		        cout << "Error: Coordinates do NOT form a perfect square. Please re-enter all points.\n";
		        //clear all records and restart
                coordS.clear(); 
                i = 0;          
		    }
		}
    }
}

//to get the shape id
void Square::setShapeNum(int num) 
{
    shapeNum = num;
}

//returns description of square
string Square::toString()
{
    string output;

    output += "\nShape [" + to_string(shapeNum) + "]\n";
     // base class info to get name and specialtype
    output += ShapeTwoD::toString();
    output += "\nArea : " + to_string(static_cast<int>(this->area)) + " units square\n";
    output += "Vertices :\n";  

    for (size_t i = 0; i < coordS.size(); i++) {
        output += "Point [" + to_string(i) + "] : (" + to_string(coordS[i].x) + ", " + to_string(coordS[i].y) + ")\n";
    }
	
	// Blank line after vertices
    output += "\n";  
	
	//lambda to check if a point is one of the vertices
    auto isVertex = [&](int x, int y) -> bool {
        for (const auto& coord : coordS) {
            if (coord.x == x && coord.y == y) {
                return true;
            }
        }
        return false;
    };
	
	//list points on perimeter excluding vertices
    output += "Points on perimeter : "; 

    bool hasPerimeterPoints = false;

    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            if (isPointOnShape(x, y) && !isVertex(x,y)) {
                output += "(" + to_string(x) + ", " + to_string(y) + "), ";
                hasPerimeterPoints = true;
            }
        }
    }

    if (!hasPerimeterPoints)
        output += "None!";
    else
    	// Remove trailing comma and space
        output.erase(output.size() - 2); 
	
	 // Two newlines before next section
    output += "\n\n"; 
	
	//list points in shape excluding perimeter
    output += "Points within shape : ";

    bool found = false;
    for (int x = minX + 1; x < maxX; x++) {
        for (int y = minY + 1; y < maxY; y++) {
            if (isPointInShape(x, y)) {
                output += "(" + to_string(x) + ", " + to_string(y) + "), ";
                found = true;
            }
        }
	}
		
        if (found)
        	// Remove trailing comma and space
            output.erase(output.size() - 2);
        else
            output += "None!";
    

    return output;
}


