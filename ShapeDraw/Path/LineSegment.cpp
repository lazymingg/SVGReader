#include "../../ShapeHeader/Path/LineSegment.h"

MyPoint::Point LineSegment::setSegment(const char &curCommand, const std::string &data, int &index, MyPoint::Point start)
{
    MyPoint::Point end = toAbsolute(curCommand, data, index, start);
    segment.AddLine(start.getX(), start.getY(), end.getX(), end.getY());
    return end;
}

MyPoint::Point HorizontalLineSegment::setSegment(const char &curCommand, const std::string &data, int &index, MyPoint::Point start)
{
    float x = toAbsoluteX(curCommand, data, index, start);
    segment.AddLine(start.getX(), start.getY(), x, start.getY());
    return {x, start.getY()};
}

MyPoint::Point VerticalLineSegment::setSegment(const char &curCommand, const std::string &data, int &index, MyPoint::Point start)
{
    float y = toAbsoluteY(curCommand, data, index, start);
    segment.AddLine(start.getX(), start.getY(), start.getX(), y);
    return {start.getX(), y};
}