#ifndef LINE3D_H
#define LINE3D_H

#include "Point3D.h"
#include "Line2D.h"

class Line3D: public Line2D
{
	private:
		Point3D pt1;
		Point3D pt2;
		
	protected:
		//function to compute the length of a 3D line
		void setLength();
	
	public:
		//Default constructor to intialize 2 Point3D objs to (0, 0, 0)
		Line3D();
		
		//Overloaded constructor to initialize a line based on 2 Point3D objs
		Line3D(Point3D, Point3D);
		
		//Destructor 
		~Line3D() = default;
		
		//const reference of Point3D object to return pt1 coordinates
		const Point3D& getPt1() const;
		//const reference of Point3D object to return pt2 coordinates
		const Point3D& getPt2() const;
		
		//function to take in Point3D object and assign the value to pt1 and calls function to update the length
		void setPt1(Point3D);
		//function  to take in Point3D object and assign the value to pt2 and calls function to update the length
		void setPt2(Point3D);
		
		//Overloaded operator to compare if 2 Line3D objects are equal by comparing their pt1 and pt2
		//Used with template function equals
		bool operator==(const Line3D& other) const;
		
		//Overloaded operator to format data output
		friend ostream& operator<<(ostream& oss, const Line3D& line3d);
};


#endif
