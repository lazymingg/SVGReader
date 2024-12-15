#ifndef _LINE_SEGMENT_H_
#define _LINE_SEGMENT_H_

#include "Segment.h"

class LineSegment : public Segment
{
public:
    MyPoint::Point setSegment(const char &curCommand, const std::string& data, int& index, MyPoint::Point start);
    ~LineSegment() { segment.Reset(); }
};

class HorizontalLineSegment : public Segment
{
public:
    MyPoint::Point setSegment(const char &curCommand, const std::string& data, int& index, MyPoint::Point start);
    ~HorizontalLineSegment() { segment.Reset(); }
};

class VerticalLineSegment : public Segment
{
public:
    MyPoint::Point setSegment(const char &curCommand, const std::string& data, int& index, MyPoint::Point start);
    ~VerticalLineSegment() { segment.Reset(); }
};

#endif