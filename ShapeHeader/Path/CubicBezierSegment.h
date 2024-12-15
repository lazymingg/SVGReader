#ifndef _CUBIC_BEZIER_SEGMENT_H_
#define _CUBIC_BEZIER_SEGMENT_H_

#include "Segment.h"

class CubicBezierSegment : public Segment
{
public:
    MyPoint::Point setSegment(const char &curCommand, const std::string& data, int& index, MyPoint::Point start, MyPoint::Point& point1, MyPoint::Point& point2, MyPoint::Point& point3);
    ~CubicBezierSegment() { segment.Reset(); }
};

class SmoothCubicBezierSegment : public Segment
{
public:
    MyPoint::Point setSegment(const char &curCommand, const char &prevCommand, const std::string& data, int& index, MyPoint::Point start, MyPoint::Point& point1, MyPoint::Point& point2, MyPoint::Point& point3);
    ~SmoothCubicBezierSegment() { segment.Reset(); }
};

#endif