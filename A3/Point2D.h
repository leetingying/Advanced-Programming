#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>
#include <iostream>
#include <iomanip>

using std::ostream;
using std::sqrt;
using std::pow;
using std::right;
using std::left;
using std::setfill;
using std::setw;
using std::fixed;
using std::setprecision;
using std::cout;
using std::endl;

class Point2D
{
	protected:
		int x;
		int y;
		
		double distFrOrigin;
		
		//function to compute distance of a point to the origin
		void setDistFrOrigin();
	
	public:
		//Default Constructor to initialize variables
		Point2D();
		
		//Overloaded constructor to create a point with given coordinates
		Point2D(int, int);
		
		//virtual destructor as this is a base class
		virtual ~Point2D() = default;
		
		//return x value
		int getX() const;
		//return y value
		int getY() const;
		//function that is an accessor method which returns the value of distFrOrigin
		double getScalarValue() const;
		
		//set the x value of the point with a new value and
		//calls function to compute distance to ensure distFrOrigin is always up to date
		void setX(int);
		
		//set the x value of the point with a new value and
		//calls function to compute distance to ensure distFrOrigin is always up to date
		void setY(int);
		
		//Overloading operator to compare 2 Point2D objects
		//Used with the template function equals
		 bool operator==(const Point2D& other) const;
		 
		 //Overloading operator to format data output
		 friend ostream& operator<<(ostream& oss, const Point2D& point);
};

#endif
