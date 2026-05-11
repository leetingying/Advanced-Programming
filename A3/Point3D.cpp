#include "Point3D.h"

//Default constructor 
//initializes base class x and y with (0, 0) and z as 0
//calls function to compute distFrOrigin
Point3D::Point3D():Point2D(0, 0), z(0)
{
	setDistFrOrigin();
}

//Overloaded constructor
//calls base class to initialize x and y values, then initializes z 
//calls function to compute distFrOrigin
Point3D::Point3D(int x, int y, int z) : Point2D(x, y)
{
	this->z = z;
	setDistFrOrigin();
}

//function to compute the distance from origin (0, 0)
void Point3D::setDistFrOrigin()
{
	distFrOrigin = sqrt(pow(x,2) + pow(y, 2) + pow(z, 2));
}

//function to return z, used for sorting and display
int Point3D::getZ() const
{
	return z;
}

//function to set z value then calls function to ensure distFrOrigin is always up to date
void Point3D::setZ(int z)
{
	this->z = z;
	setDistFrOrigin();
}

//Overloaded operator to check if 2 Point3D obj are equal
//Used with template function equals
bool Point3D::operator==(const Point3D& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

//Overloaded operator to format data output
ostream& operator<<(ostream& oss, const Point3D& point)
{
	oss << right << setfill(' ') << "["
		<< setw(4) << point.getX() << ", "
		<< setw(4) << point.getY() << ", "
		<< setw(4) << point.getZ() << "]   "
		<< fixed << setprecision(3) << left << point.getScalarValue() 
		<< right
		<< endl;
		
	return oss;
}


