#include "cross.h"

//inherit from parent:ShapeTwoD, to get the name and special type
// Calls setCoords when constructor is called
Cross::Cross(string name, bool containsWarpSpace):ShapeTwoD(name, containsWarpSpace)
{
	this -> setCoords();
}

// return the already calculated area
double Cross::getArea()
{
	return area;
}

//Calculate and store result as area
double Cross::computeArea() 
{
	//shoelace mformula to find area of any polygon in this case is a cross
	double a = 0;
	for (int i = 0; i < 12; i++)
	{
		//coordC is a vector holding 12 points
		//% 12 ensures that the last point connects back to first point in order to form the cross
		a += coordC[i].x * coordC[(i + 1) % 12].y - coordC[i].y * coordC[(i + 1) % 12].x;
	}
	area =fabs(a)/2;
	
	return area;
	
}

//function to check if point is in shape
bool Cross::isPointInShape(int x, int y) 
{
	//if the point is on the perimeter, return false
	 if (isPointOnShape(x, y))
        return false;

    bool inside = false;
    int n = coordC.size();
	
	//Ray-casting algorithm to determine if a point is inside the shape
	//Counts the number of time a horizontal ray extending from point crosses shape edges
	//if the count if odd the point is inside, if even the point is outside
    for (int i = 0, j = n - 1; i < n; j = i++)
    {
        int xi = coordC[i].x, yi = coordC[i].y;
        int xj = coordC[j].x, yj = coordC[j].y;

        // Check if the point crosses the edge
        if ((yi > y) != (yj > y))
        {
            double intersectX = (double)(xj - xi) * (y - yi) / (yj - yi) + xi;
            if (x < intersectX)
                inside = !inside;
        }
    }
    
    return inside;
}

//function to check if point is on the edges
bool Cross::isPointOnShape(int x, int y)
{
	for (int i = 0; i < 12; ++i)
    {
        int x1 = coordC[i].x, y1 = coordC[i].y;
        int x2 = coordC[(i + 1) % 12].x, y2 = coordC[(i + 1) % 12].y;

        int dx = x2 - x1;
        int dy = y2 - y1;
        int dxp = x - x1;
        int dyp = y - y1;

        // Check for point is collinear with edge using cross product
        if (dx * dyp == dy * dxp)
        {
            // Check if point is within edge bounds
            if (min(x1, x2) <= x && x <= max(x1, x2) &&
                min(y1, y2) <= y && y <= max(y1, y2))
            {
                return true;
            }
        }
    }
    return false;
}

//function to collect 12 unique user input points and store in vector coordC
void Cross::setCoords() 
{
	coordC.clear();
    int i = 0;  // point counter

    while (i < 12) {
        Coord c;
        string input;
        bool valid = false;

        //Get X-coordinate with input validation
        do {
            cout << "Please enter x-ordinate of pt. " << i + 1 << " : ";
            getline(cin, input);
            //trimming input
            input.erase(0, input.find_first_not_of(" \t"));
            input.erase(input.find_last_not_of(" \t") + 1);
            try {
                c.x = stoi(input);
                valid = true;
            }
            catch (...) {
                cout << "Invalid input. Please enter a valid integer for pt. " << i + 1 << " x.\n";
            }
        } while (!valid);

        valid = false;

        //Get Y-coordinate with input validation
        do {
            cout << "Please enter y-ordinate of pt. " << i + 1 << " : ";
            getline(cin, input);
            //trimming inputs
            input.erase(0, input.find_first_not_of(" \t"));
            input.erase(input.find_last_not_of(" \t") + 1);
            try {
                c.y = stoi(input);
                valid = true;
            }
            catch (...) {
                cout << "Invalid input. Please enter a valid integer for pt. " << i + 1 << " y.\n";
            }
        } while (!valid);

        // Check for duplicate points
        bool isDuplicate = false;
        for (const auto& existing : coordC) {
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
        coordC.push_back(c);
        i++;
    }

    if (!coordC.empty()) {
        minX = maxX = coordC[0].x;
        minY = maxY = coordC[0].y;
		
		//Bounding box calculation 
        //loop through all coordinates in coordR, set the min and max x y values
        for (const auto& coord : coordC) {
            minX = min(minX, coord.x);
            maxX = max(maxX, coord.x);
            minY = min(minY, coord.y);
            maxY = max(maxY, coord.y);
        }
    }
}

//to get shape id
void Cross::setShapeNum(int num)
{
    shapeNum = num;
}

//returns description of cross
string Cross::toString() 
{
    string output;

    output += "\nShape [" + to_string(shapeNum) + "]\n";
     // base class info to get name and specialtype
    output += ShapeTwoD::toString(); 
    output += "\nArea : " + to_string(static_cast<int>(area)) + " units square\n";
    output += "Vertices :\n";

    for (size_t i = 0; i < coordC.size(); i++) {
        output += "Point [" + to_string(i) + "] : (" + to_string(coordC[i].x) + ", " + to_string(coordC[i].y) + ")\n";
    }
	
	//lambda to check if a point is one of the vertices
    auto isVertex = [&](int x, int y) -> bool {
        for (const auto& coord : coordC) {
            if (coord.x == x && coord.y == y) {
                return true;
            }
        }
        return false;
    };
	
	//list points in perimeter excluding vertices
    output += "\nPoints on perimeter : ";
    bool hasPerimeterPoints = false;

    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) 
        {
            // Only include perimeter points that are NOT one of the vertices
            if (isPointOnShape(x, y) && !isVertex(x, y)) {
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

	//list points in shape excluding perimeter
    output += "\n\nPoints within shape : ";
    
    bool found = false;
    for (int x = minX; x < maxX; x++) 
    {
    	for (int y = minY; y < maxY; y++) 
    	{
        	if (isPointInShape(x, y)) 
        	{
            	output += "(" + to_string(x) + ", " + to_string(y) + "), ";
                found = true;
            }
        }
    }

        if (found)
        	// Remove trailing comma and space
            output.erase(output.size() - 2); 
        else
            output += "None found!";
    

    return output;
}

