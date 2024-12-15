#ifndef _QUADRATIC_BEZIER_SEGMENT_H_
#define _QUADRATIC_BEZIER_SEGMENT_H_

#include "Segment.h"

class QuadraticBezierSegment : public Segment
{
public:
    MyPoint::Point setSegment(const char &curCommand, const std::string& data, int& index, MyPoint::Point start, MyPoint::Point &point1, MyPoint::Point &point2);
    ~QuadraticBezierSegment() { segment.Reset(); }
};

class SmoothQuadraticBezierSegment : public Segment
{
public:
    MyPoint::Point setSegment(const char &curCommand, const char &prevCommand, const std::string& data, int& index, MyPoint::Point start, MyPoint::Point &point1, MyPoint::Point &point2);
    ~SmoothQuadraticBezierSegment() { segment.Reset(); }
};

class QuadraticBezierSegment_t : public Segment
{
public:
    MyPoint::Point setSegment(const char &prevCommand, const std::string& data, int& index, MyPoint::Point start, MyPoint::Point &point1, MyPoint::Point &point2);
    ~QuadraticBezierSegment_t() { segment.Reset(); }
};

#endif