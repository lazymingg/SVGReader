#ifndef _LINE_SEGMENT_H_
#define _LINE_SEGMENT_H_

#include "Segment.h"

class LineSegment : public Segment
{
public:
    MyPoint::Point setSegment(const char &curCommand, const std::string& data, int& index, MyPoint::Point start);
    ~LineSegment() { value.Reset(); }
};

class HorizontalLineSegment : public Segment
{
public:
    MyPoint::Point setSegment(const char &curCommand, const std::string& data, int& index, MyPoint::Point start);
    ~HorizontalLineSegment() { value.Reset(); }
};

class VerticalLineSegment : public Segment
{
public:
    MyPoint::Point setSegment(const char &curCommand, const std::string& data, int& index, MyPoint::Point start);
    ~VerticalLineSegment() { value.Reset(); }
};

#endif