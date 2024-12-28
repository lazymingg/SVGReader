#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#include "../Figure.h"
#include "../Point.h"
#include <gdiplus/gdipluspath.h>
#include <string>
#include <cmath>
#include <vector>

#define PI 3.14159265358979323846

class Segment
{
protected:
    Gdiplus::GraphicsPath value;
public:
    float toAbsoluteX(const char &curCommand, const std::string &data, int &index, MyPoint::Point start);
    float toAbsoluteY(const char &curCommand, const std::string &data, int &index, MyPoint::Point start);
    MyPoint::Point toAbsolute(const char &curCommand, const std::string &data, int &index, MyPoint::Point start);

    Gdiplus::GraphicsPath& getSegment() { return value; }
    virtual ~Segment() { value.Reset(); }
};

#endif