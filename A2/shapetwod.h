#ifndef SHAPETWOD_H
#define SHAPETWOD_H
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Coord{
    int x;
    int y;
};

class ShapeTwoD 
{
    protected:
        string name;
        bool containsWarpSpace;
    public:
        ShapeTwoD(string, bool);
        string getName();
        bool getContainsWarpSpace();
        void setName(string);
        void setContainsWarpSpace(bool);

        virtual string toString();

        virtual double computeArea(){
            return 1.0;
        };

        virtual bool isPointInShape(int, int){
            return false;
        };

        virtual bool isPointOnShape(int, int){
            return false;
        };
		
        virtual void setRadius(int){};
        virtual double getArea(){
        	return 1.0;
        };
        virtual void setCoords(){};
        virtual void setShapeNum(int){};
        virtual ~ShapeTwoD() = default;

};

#endif // SHAPETWOD_H
