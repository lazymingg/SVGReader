#ifndef _SEGMENT_GENERATOR_H_
#define _SEGMENT_GENERATOR_H_

#include "LineSegment.h"
#include "CubicBezierSegment.h"
#include "QuadraticBezierSegment.h"
#include "EllipticalArcCurveSegment.h"

class SegmentGenerator
{
public:
    Segment* generateSegment(const char &prevCommand, const char &curCommand, const std::string &data, int &index,
                            MyPoint::Point &start, MyPoint::Point &point1,  MyPoint::Point &point2,  MyPoint::Point &point3);
};



#endif