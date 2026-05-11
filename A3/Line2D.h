#ifndef LINE2D_H
#define LINE2D_H
#include "Point2D.h"

class Line2D
{
	private:
		Point2D pt1;
		Point2D pt2;
		
	protected:
		double length;
		
		//function to compute the length based on the 2 points of the line
		void setLength();
		
	public:
		//Default constructor to initialize the line with 2 (0, 0) Point2D obj
		Line2D();
		//Overloaded constructor to initialize a line using 2 given Point2D
		Line2D(Point2D, Point2D);
		
		//Virtual destructor as Line2D is a base class
		virtual ~Line2D() = default;
		
		//const reference of Point2D object to return first point of a line
		const Point2D& getPt1() const;
		
		//const reference of Point2D object to return second point of the line
		const Point2D& getPt2() const;
		
		//function which an accessor method to retrieve length of the line
		double getScalarValue() const;
		
		//function to take in Point2D object and assign the value to pt1 and call function to update length
		void setPt1(Point2D);
		
		//function to take in Point2D object and assign the value to pt2 and call function to update length
		void setPt2(Point2D);
		
		//Overloaded operator to check if both points of 2 lines are equal
		//Used with template function equals
		bool operator==(const Line2D& other) const;
		
		//Overloaded operator to format data output
		friend ostream& operator<<(ostream& oss, const Line2D& line2d);
};

#endif
