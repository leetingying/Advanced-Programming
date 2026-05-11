#include "functions.h"
#include <iostream>
using std::cerr;
using std::endl;
using std::vector;
using std::sort;
using std::string;

//Sort function for Point2D x-ordinate (ASC/DESC)
bool P2DSortXAsc(const Point2D& a, const Point2D& b)
{
	return a.getX() < b.getX();
}

bool P2DSortXDesc(const Point2D& a, const Point2D& b)
{
	return a.getX() > b.getX();
}

//Sort function for Point2D y-ordinate (ASC/DESC)
bool P2DSortYAsc(const Point2D& a, const Point2D& b)
{
	return a.getY() < b.getY();
}

bool P2DSortYDesc(const Point2D& a, const Point2D& b)
{
	return a.getY() > b.getY();
}

//Sort function for Point2D distFrOrigin (ASC/DESC)
bool P2DSortDistAsc(const Point2D& a, const Point2D& b)
{
	return a.getScalarValue() < b.getScalarValue();
}

bool P2DSortDistDesc(const Point2D& a, const Point2D& b)
{
	return a.getScalarValue() > b.getScalarValue();
}

//takes in Point2D vector to sort based on criteria and order, returns the sorted vector
vector<Point2D> sortP2D(const vector<Point2D>& v , const string& criteria, const string& order)
{
	vector<Point2D> sortv = v;
	
	if(criteria == "x-ordinate")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), P2DSortXAsc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), P2DSortXDesc);
		}
	}
	else if(criteria == "y-ordinate")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), P2DSortYAsc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), P2DSortYDesc);
		}
	}
	else if (criteria == "Dist. Fr Origin")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), P2DSortDistAsc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), P2DSortDistDesc);
		}
	}
	else
	{
		cerr << "Invalid sorting criteria or order for P2D." << endl;
	}
	
	return sortv;
}

//Sort function for Point3D x-ordinate (ASC/DESC)
bool P3DSortXAsc(const Point3D& a, const Point3D& b)
{
	return a.getX() < b.getX();
}

bool P3DSortXDesc(const Point3D& a, const Point3D& b)
{
	return a.getX() > b.getX();
}

//Sort function for Point3D y-ordinate (ASC/DESC)
bool P3DSortYAsc(const Point3D& a, const Point3D& b)
{
	return a.getY() < b.getY();
}

bool P3DSortYDesc(const Point3D& a, const Point3D& b)
{
	return a.getY() > b.getY();
}

//Sort function for Point3D z-ordinate (ASC/DESC)
bool P3DSortZAsc(const Point3D& a, const Point3D& b)
{
	return a.getZ() < b.getZ();
}

bool P3DSortZDesc(const Point3D& a, const Point3D& b)
{
	return a.getZ() > b.getZ();
}

//Sort function for Point3D distFrOrigin (ASC/DESC)
bool P3DSortDistAsc(const Point3D& a, const Point3D& b)
{
	return a.getScalarValue() < b.getScalarValue();
}

bool P3DSortDistDesc(const Point3D& a, const Point3D& b)
{
	return a.getScalarValue() > b.getScalarValue();
}

//takes in Point3D vector to sort based on criteria and order, return the sorted vector
vector<Point3D> sortP3D(const vector<Point3D>& v, const string& criteria, const string& order)
{
	vector<Point3D> sortv = v;
	
	if(criteria == "x-ordinate")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), P3DSortXAsc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), P3DSortXDesc);
		}
	}
	else if(criteria == "y-ordinate")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), P3DSortYAsc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), P3DSortYDesc);
		}
	}
	else if(criteria == "z-ordinate")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), P3DSortZAsc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), P3DSortZDesc);
		}
	}
	else if (criteria == "Dist. Fr Origin")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), P3DSortDistAsc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), P3DSortDistDesc);
		}
	}
	else
	{
		cerr << "Invalid sorting criteria or order for P3D."<< endl;
	}
	
	return sortv;
}

//Sort function for Line2D Pt. 1's x and y values (ASC/DESC)
//sort by X values first, if x values are the same thwen sort by y values
bool L2DSortPt1Asc(const Line2D& a, const Line2D& b)
{
	if(a.getPt1().getX() != b.getPt1().getX())
	{
		return a.getPt1().getX() < b.getPt1().getX();
	}
	return a.getPt1().getY() < b.getPt1().getY();
}

bool L2DSortPt1Desc(const Line2D& a, const Line2D& b)
{
	if(a.getPt1().getX() != b.getPt1().getX())
	{
		return a.getPt1().getX() > b.getPt1().getX();
	}
	return a.getPt1().getY() > b.getPt1().getY();
}

//Sort function for Line2D Pt. 2's x and y values (ASC/DESC)
//sort by X values first, if x values are the same thwen sort by y values
bool L2DSortPt2Asc(const Line2D& a, const Line2D& b)
{
	if(a.getPt2().getX() != b.getPt2().getX())
	{
		return a.getPt2().getX() < b.getPt2().getX();
	}
	return a.getPt2().getY() < b.getPt2().getY();
}

bool L2DSortPt2Desc(const Line2D& a, const Line2D& b)
{
	if(a.getPt2().getX() != b.getPt2().getX())
	{
		return a.getPt2().getX() > b.getPt2().getX();
	}
	return a.getPt2().getY() > b.getPt2().getY();
}

//Sort function for Line2D Length values (ASC/DESC)
bool L2DSortLengthAsc(const Line2D& a, const Line2D& b)
{
	return a.getScalarValue() < b.getScalarValue();
}

bool L2DSortLengthDesc(const Line2D& a, const Line2D& b)
{
	return a.getScalarValue() > b.getScalarValue();
}

//takes in Line2D vector to sort based on criteria and order, then return the sorted vector
vector<Line2D> sortL2D(const vector<Line2D>& v, const string& criteria, const string& order)
{
	vector<Line2D> sortv = v;
	
	if(criteria== "Pt. 1")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), L2DSortPt1Asc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), L2DSortPt1Desc);
		}
	}
	else if(criteria== "Pt. 2")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), L2DSortPt2Asc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), L2DSortPt2Desc);
		}
	}
	else if(criteria== "Length")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), L2DSortLengthAsc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), L2DSortLengthDesc);
		}
	}
	else
	{
		cerr << "Invalid sorting criteria or order for L2D."<< endl;
	}
	
	return sortv;
}

//Sort function for Line3D Pt. 1's x and y values (ASC/DESC)
//sort by X values first, if x values are the same thwen sort by y values
bool L3DSortPt1Asc(const Line3D& a, const Line3D& b)
{
	if(a.getPt1().getX() != b.getPt1().getX())
	{
		return a.getPt1().getX() < b.getPt1().getX();
	}
	return a.getPt1().getY() < b.getPt1().getY();
}

bool L3DSortPt1Desc(const Line3D& a, const Line3D& b)
{
	if(a.getPt1().getX() != b.getPt1().getX())
	{
		return a.getPt1().getX() > b.getPt1().getX();
	}
	return a.getPt1().getY() > b.getPt1().getY();
}

//Sort function for Line3D Pt. 1's x and y values (ASC/DESC)
//sort by X values first, if x values are the same thwen sort by y values
bool L3DSortPt2Asc(const Line3D& a, const Line3D& b)
{
	if(a.getPt2().getX() != b.getPt2().getX())
	{
		return a.getPt2().getX() < b.getPt2().getX();
	}
	return a.getPt2().getY() < b.getPt2().getY();
}

bool L3DSortPt2Desc(const Line3D& a, const Line3D& b)
{
	if(a.getPt2().getX() != b.getPt2().getX())
	{
		return a.getPt2().getX() > b.getPt2().getX();
	}
	return a.getPt2().getY() > b.getPt2().getY();
}

//Sort function for Line3D Length values (ASC/DESC)
bool L3DSortLengthAsc(const Line3D& a, const Line3D& b)
{
	return a.getScalarValue() < b.getScalarValue();
}

bool L3DSortLengthDesc(const Line3D& a, const Line3D& b)
{
	return a.getScalarValue() > b.getScalarValue();
}

//takes in Line3D vector to sort based on criteria and order then return the sorted vector
vector<Line3D> sortL3D(const vector<Line3D>& v, const string& criteria, const string& order)
{
	vector<Line3D> sortv = v;
	
	if(criteria== "Pt. 1")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), L3DSortPt1Asc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), L3DSortPt1Desc);
		}
	}
	else if(criteria== "Pt. 2")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), L3DSortPt2Asc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), L3DSortPt2Desc);
		}
	}
	else if(criteria== "Length")
	{
		if (order == "ASC")
		{
			sort(sortv.begin(), sortv.end(), L3DSortLengthAsc);
		}
		else if (order == "DSC")
		{
			sort(sortv.begin(), sortv.end(), L3DSortLengthDesc);
		}
	}
	else
	{
		cerr << "Invalid sorting criteria or order for L3D." << endl;
	}
	
	return sortv;
}
