#include "Point2D.h"

//Default Constructor to initialize a point at (0, 0) and distFrOrigin is 0.0
Point2D::Point2D()
{
	x = 0;
	y = 0;
	distFrOrigin = 0.0;
}

//Constructor to initialize a point with given x and y values
//and calls function to compute the distFrOrigin
Point2D::Point2D(int x, int y)
{
	this->x = x;
	this->y = y;
	setDistFrOrigin();
}

//function to compute distFrOrigin
void Point2D::setDistFrOrigin()
{
	distFrOrigin = sqrt(pow(x, 2) + pow(y, 2));
}

//function to return x, used for sorting and display
int Point2D::getX() const
{
	return x;
}

//function to return y, used for sorting and display
int Point2D::getY() const
{
	return y;
}

//function to return distFrOrigin, used for sorting and display
double Point2D::getScalarValue() const
{
	return distFrOrigin;
}

//function to set x and calculate distance after to ensure distFrOrigin is always up to date
void Point2D::setX(int x)
{
	this->x = x;
	setDistFrOrigin();
}

//function to set y and calculate distance after to ensure distFrOrigin is always up to date
void Point2D::setY(int y)
{
	this->y = y;
	setDistFrOrigin();
}

//overload operator to compare if 2 Point2D objects are equal
//works with the template function equals 
bool Point2D::operator==(const Point2D& other) const
{
	return x == other.x && y == other.y;
}

//overload output to format data output 
ostream& operator<<(ostream& oss, const Point2D& point)
{
	oss << right << setfill(' ') << "[" 
		<< setw(4) << point.getX() << ", " 
		<< setw(4) << point.getY() << "]   " 
		<< fixed << setprecision(3) << left << point.getScalarValue() 
		<< right
		<< endl;
	
	return oss;
}

