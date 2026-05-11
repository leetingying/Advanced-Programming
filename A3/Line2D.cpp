#include "Line2D.h"

//Default constructor to intialize pt1 and pt2 to (0, 0)
Line2D::Line2D()
{
	pt1 = Point2D(0, 0);
	pt2 = Point2D(0, 0);
}

//Overloaded constructor to assign pt1 and pt2 values and update the length
Line2D::Line2D(Point2D pt1, Point2D pt2)
{
	setPt1(pt1);
	setPt2(pt2);
}

//const reference of Point2D object to return pt1 coordinates
const Point2D& Line2D::getPt1() const
{
	return pt1;
}

//const reference of Point2D object to return pt2 coordinates
const Point2D& Line2D::getPt2() const
{
	return pt2;
}

//function to compute length based on pt1 and pt2 of a line
void Line2D::setLength()
{	
	int dx = getPt1().getX() - getPt2().getX();
	int dy = getPt1().getY() - getPt2().getY();
	length = sqrt(pow(dx, 2) + pow(dy, 2));
}

//function which is an accessor method to return length of the line 
double Line2D::getScalarValue() const
{
	return length;
}
		
//function to take in Point2D object and assign the value to pt1 and calls function to ensure length is up to date
void Line2D::setPt1(Point2D pt1)
{
	this->pt1 = pt1;
	setLength();
}

//function to take in Point2D object and assign the value to pt2 and calls function to ensure length is up to date
void Line2D::setPt2(Point2D pt2)
{
	this->pt2 = pt2;
	setLength();
}

//Overloaded operator to compare 2 Line2D objs if thwy are equal
//Used with template function equals		
bool Line2D::operator==(const Line2D& other) const
{
	return pt1 == other.pt1 && pt2 == other.pt2;
}

//Overloaded operator to format data output
ostream& operator<<(ostream& oss, const Line2D& line2d)
{
	oss << right << setfill(' ') << "[" 
	<< setw(4) << line2d.getPt1().getX() << ", "
	<< setw(4) << line2d.getPt1().getY() << "]"
	<< setw(4)  << "["
	<< setw(4) << line2d.getPt2().getX() << ", "
	<< setw(4) << line2d.getPt2().getY() << "]   "
	<< fixed << setprecision(3) << left << line2d.getScalarValue() 
	<< right
	<< endl;
	
	return oss;
}
