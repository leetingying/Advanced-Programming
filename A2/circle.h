#ifndef CIRCLE_H
#define CIRCLE_H

#include "shapetwod.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

class Circle:public ShapeTwoD
{
	private:
		int minX;
		int minY;
		int maxX;
		int maxY;
		const double Pi = 3.14159265358979323846;
		int radius;
		double area = 0.0;
		Coord center;
		int shapeNum;
    
	public:
		Circle(string name, bool containsWarpSpace);
		double getArea() override;
		double computeArea() override;
		bool isPointInShape(int x, int y) override;
		bool isPointOnShape(int x, int y) override;
		void setRadius(int) override;
		void setCoords() override;
		void setShapeNum(int) override;
		string toString() override;

};

#endif
