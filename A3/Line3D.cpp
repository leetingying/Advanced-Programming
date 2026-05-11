#include "Line3D.h"

//Default constructor to initialize 2 points of Point3D as (0, 0, 0)
Line3D::Line3D()
{
	pt1 = Point3D(0, 0, 0);
	pt2 = Point3D(0, 0, 0);
}

//Overloaded operator to take in 2 points of Point3D, store the objects as pt1 and pt2
//calls function to compute the length
Line3D::Line3D(Point3D pt1, Point3D pt2):Line2D(Point2D(pt1.getX(), pt1.getY()), Point2D(pt2.getX(), pt2.getY()))
{
	this->pt1=pt1;
	this->pt2=pt2;
	
	setLength();
}

//function to compute the length between 2 points
void Line3D::setLength()
{
	int dx = pt1.getX() - pt2.getX();
	int dy = pt1.getY() - pt2.getY();
	int dz = pt1.getZ() - pt2.getZ();
	
	length = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz,2));
}

//const reference to return pt 1 coordinates, used for sorting and display
const Point3D& Line3D::getPt1() const
{
	return pt1;
}

//const reference to return pt2 coordinates, used for sorting and display
const Point3D& Line3D::getPt2() const
{
	return pt2;
}

//function to take in Point3D object and assign the value to pt1 and calls function to ensure length is up to date
void Line3D::setPt1(Point3D pt1)
{
	this->pt1 = pt1;
	setLength();
}

//function to take in Point3D object and assign the value to pt2 and calls function to ensure length is up to date
void Line3D::setPt2(Point3D pt2)
{
	this->pt2 = pt2;
	setLength();
}

//Overloaded operator to compare if 2 Line3D objs are equal by comparing their pt1 and pt2
//Used with template function equals 
bool Line3D::operator==(const Line3D& other) const
{
	return pt1 == other.pt1 && pt2 == other.pt2;
}

//Overloaded operator to format data output
ostream& operator<<(ostream& oss, const Line3D& line3d)
{
	oss << right << setfill(' ') << "["
		<< setw(4) << line3d.getPt1().getX() << ", "
		<< setw(4) << line3d.getPt1().getY() << ", "
		<< setw(4) << line3d.getPt1().getZ() << "]"
		<< setw(4) << "["
		<< setw(4) << line3d.getPt2().getX() << ", "
		<< setw(4) << line3d.getPt2().getY() << ", "
		<< setw(4) << line3d.getPt2().getZ() << "]   "
		<< fixed << setprecision(3) << left << line3d.getScalarValue()
		<< right
		<< endl;
		
	return oss;
}

