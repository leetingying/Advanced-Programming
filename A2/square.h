#ifndef SQUARE_H
#define SQUARE_H

#include "shapetwod.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Square: public ShapeTwoD 
{
	private:
		int minX;
		int minY;
		int maxX;
		int maxY;
		double area = 0.0;
		vector<Coord> coordS;
		int shapeNum;
		
	public:
		Square(string name, bool containsWarpSpace);
		double getArea() override;
		double computeArea() override;
		bool isPointInShape(int x, int y) override;
		bool isPointOnShape(int x, int y) override;
		void setCoords() override;
		void setShapeNum(int) override;
		string toString() override;

};

#endif
