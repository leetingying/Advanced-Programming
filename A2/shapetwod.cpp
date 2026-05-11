#include "shapetwod.h"

using namespace std;

ShapeTwoD::ShapeTwoD(string name, bool containsWarpSpace) 
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
}

// getname function for shapes
string ShapeTwoD::getName() 
{
    return name;
}

// get the special type for shapes
bool ShapeTwoD::getContainsWarpSpace() 
{
    return containsWarpSpace;
}

//set function for shape name
void ShapeTwoD::setName(string name) 
{
    this->name = name;
}

// set function for special type
void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace) 
{
    this->containsWarpSpace = containsWarpSpace;
}

string ShapeTwoD::toString() 
{
    string specialtype;
    //check bool to see what is the special type of the shape
    if(containsWarpSpace == true)
    {
        specialtype = "WS";
    }
    else
    {
        specialtype = "NS";
    }
    string output = "Name	: " + name + "\nSpecial Type : " + specialtype;
    return output;
}

