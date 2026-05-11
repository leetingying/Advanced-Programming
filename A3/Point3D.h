#ifndef POINT3D_H
#define POINT3D_H

#include "Point2D.h"

class Point3D:public Point2D
{
	protected:
		int z;
		
		void setDistFrOrigin();
		
	public:
		//Default constructor to initialize a point
		Point3D();
		
		//Overloaded constructor to initialize specific x, y, z values
		//calls function to compute distFrOrigin
		Point3D(int, int, int);
		
		//Destructor
		~Point3D() = default;
		
		//return z value
		int getZ() const;
		
		//set the z value of a point with a new value and
		//calls function to calculate distance to ensure distFrOrigin is always up to date
		void setZ(int);
		
		//Overloading operator to check if 2 Point3D objects are equal
		//Used with template function equals
		bool operator==(const Point3D& other) const;
		
		//Overloading operator to format data output
		 friend ostream& operator<<(ostream& oss, const Point3D& point);
};

#endif
