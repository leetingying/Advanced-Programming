#ifndef FUNCTIONS_H
#define FUNCTIONS_h

#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"
#include <algorithm>
#include <vector>
#include <string>


//sorting functions for Point2D
bool P2DSortXAsc(const Point2D&, const Point2D&);
bool P2DSortXDesc(const Point2D&, const Point2D&);
bool P2DSortYAsc(const Point2D&, const Point2D&);
bool P2DSortYDesc(const Point2D&, const Point2D&);
bool P2DSortDistAsc(const Point2D&, const Point2D&);
bool P2DSortDistDesc(const Point2D&, const Point2D&);
std::vector<Point2D> sortP2D(const std::vector<Point2D>&, const std::string&, const std::string&);

//sorting functions for Point3D
bool P3DSortXAsc(const Point3D&, const Point3D&);
bool P3DSortXDesc(const Point3D&, const Point3D&);
bool P3DSortYAsc(const Point3D&, const Point3D&);
bool P3DSortYDesc(const Point3D&, const Point3D&);
bool P3DSortZAsc(const Point3D&, const Point3D&);
bool P3DSortZDesc(const Point3D&, const Point3D&);
bool P3DSortDistAsc(const Point3D&, const Point3D&);
bool P3DSortDistDesc(const Point3D&, const Point3D&);
std::vector<Point3D> sortP3D(const std::vector<Point3D>&, const std::string&, const std::string&);

//sorting functions for Line2D
bool L2DSortPt1Asc(const Line2D&, const Line2D&);
bool L2DSortPt1Desc(const Line2D&, const Line2D&);
bool L2DSortPt2Asc(const Line2D&, const Line2D&);
bool L2DSortPt2Desc(const Line2D&, const Line2D&);
bool L2DSortLengthAsc(const Line2D&, const Line2D&);
bool L2DSortLengthDesc(const Line2D&, const Line2D&);
std::vector<Line2D> sortL2D(const std::vector<Line2D>&, const std::string&, const std::string&);

//sorting functions for Line3D
bool L3DSortPt1Asc(const Line3D&, const Line3D&);
bool L3DSortPt1Desc(const Line3D&, const Line3D&);
bool L3DSortPt2Asc(const Line3D&, const Line3D&);
bool L3DSortPt2Desc(const Line3D&, const Line3D&);
bool L3DSortLengthAsc(const Line3D&, const Line3D&);
bool L3DSortLengthDesc(const Line3D&, const Line3D&);
std::vector<Line3D> sortL3D(const std::vector<Line3D>&, const std::string&, const std::string&);

#endif
