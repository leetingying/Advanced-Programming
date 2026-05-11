#include "circle.h"

//inherit from parent:ShapeTwoD, to get the name and special type
// Calls setCoords when constructor is called
Circle::Circle(string name, bool containsWarpSpace) :ShapeTwoD(name, containsWarpSpace)
{
	this->setCoords();
}

// return the already calculated area
double Circle::getArea()
{
	return area;	
}

//Calculate and store result as area using formula pi r square
double Circle::computeArea()
{
	area = Pi * radius * radius;
	return area;
}

// function to check if point is in shape
bool Circle::isPointInShape(int x, int y)
{
	//Calculate the euclidean distance between point and center
	//true if distance is less than radius
	double dist = sqrt(pow(x-center.x, 2) + pow(y-center.y, 2));
	return dist < radius;
}

//function to check if point is on the perimeter of circle
bool Circle::isPointOnShape(int x, int y)
{
	//circle equation
	if((pow((x- center.x), 2) + pow((y - center.y),2)) == pow(radius, 2)){
		return true;
	}
	return false;
}

//function to set radius
void Circle::setRadius(int r)
{
	radius = r;
}

//function to get user input center coordinates and radius
void Circle::setCoords()
{
    string input;
   	//check if the input is valid
    bool valid = false;

    //Get x-coordinate of center with input validation
    do 
    {
        cout << "Please enter x-ordinate of center: ";
        getline(cin, input);
        //trimming input
		input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);
        try 
        {
            center.x = stoi(input);
            valid = true;
        } 
        catch (...) 
        {
            cout << "Invalid input. Please enter a valid integer for center x coordinate.\n";
        }
    } 
    while (!valid);

    valid = false;

    //Get y-coordinate of center with input validation
    do 
    {
        cout << "Please enter y-ordinate of center: ";
        getline(cin, input);
        //trimming of input
		input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);
        try 
        {
            center.y = stoi(input);
            valid = true;
        } 
        catch (...) 
        {
            cout << "Invalid input. Please enter a valid integer for center y coordinate.\n";
        }
    } 
    while (!valid);

    valid = false;

    // Get radius with input validation and radius must be positive and non-zero
    do 
    {
        cout << "Please enter radius (units): ";
        getline(cin, input);
        //trimming of inputs
		input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);
        try 
        {
            radius = stoi(input);
            if (radius < 0) 
            {
                throw invalid_argument("Radius must be non-negative.\n");
            }
            else if (radius == 0)
            {
            	throw invalid_argument("Circle with radius 0 is a point.\n");
            }
            valid = true;
        } 
        catch (const invalid_argument& e)
        {
        	cout << e.what();
        }
        catch (...) 
        {
            cout << "Invalid radius. Please enter a positive integer greater than 0.\n";
        }
    } while (!valid);
    
    //set radius
    setRadius(radius);
    //calculate and store bounding box values for circle
    minX = center.x - radius;
    maxX = center.x + radius;
    minY = center.y - radius;
    maxY = center.y + radius;
    
}

//to get shape id
void Circle::setShapeNum(int num)
{
	shapeNum = num;
}

//returns decription of circle
string Circle::toString()
{
	string output;
	output += "\nShape [" + to_string(shapeNum) + "]\n";
	// base class info to get name and specialtype
	output += ShapeTwoD::toString();
	
	
	output += "\nArea : " + to_string(static_cast<int>(this->area)) + " units square\n";
	output += "Center : (" + to_string(center.x) + ", " + to_string(center.y) + ")\n";
    output += "Radius : " + to_string(static_cast<int>(this->radius)) + "\n\n";
	
	//list all points on perimeter inside bounding box
    output += "Points on perimeter : ";

    bool foundPerimeter = false;
    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            if (isPointOnShape(x, y))
            {
                output += "(" + to_string(x) + ", " + to_string(y) + "), ";
                foundPerimeter = true;
            }
        }
    }

    if (foundPerimeter)
    // Remove trailing comma and space
        output.erase(output.size() - 2); 
    else
        output += "None!";
	
	//list all points inside the circle excluding center point
    output += "\n\nPoints within shape (excluding Center): ";

    bool foundInside = false;
    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            if (isPointInShape(x, y))
            {
                if(!(x==center.x && y == center.y))
                {
                	output += "(" + to_string(x) + ", " + to_string(y) + "), ";
                	foundInside = true;
                }
            }
        }
    }
    if (foundInside)
    // Remove trailing comma and space
        output.erase(output.size() - 2);
    else
        output += "None!";

    return output;
}

