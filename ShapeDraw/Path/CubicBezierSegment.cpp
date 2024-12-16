#include "../../ShapeHeader/Path/CubicBezierSegment.h"

MyPoint::Point CubicBezierSegment::setSegment(const char &curCommand, const std::string &data, int &index, MyPoint::Point start, MyPoint::Point& point1, MyPoint::Point& point2, MyPoint::Point& point3)
{
    point1 = toAbsolute(curCommand, data, index, start);
    point2 = toAbsolute(curCommand, data, index, start);
    point3 = toAbsolute(curCommand, data, index, start);

    value.AddBezier
    (
        start.getX(), start.getY(), 
        point1.getX(), point1.getY(),
        point2.getX(), point2.getY(),
        point3.getX(), point3.getY()
    );

    return point3;
}

MyPoint::Point SmoothCubicBezierSegment::setSegment(const char &curCommand, const char &prevCommand, const std::string &data, int &index, MyPoint::Point start, MyPoint::Point &point1, MyPoint::Point &point2, MyPoint::Point &point3)
{
    if (prevCommand == 'C' || prevCommand == 'c' ||
        prevCommand == 'S' || prevCommand == 's')
        point1 = {2 * point3.getX() - point2.getX(), 2 * point3.getY() - point2.getY()};
    else
        point1 = start;

    point2 = toAbsolute(curCommand, data, index, start);
    point3 = toAbsolute(curCommand, data, index, start);

    value.AddBezier
    (
        start.getX(), start.getY(),
        point1.getX(), point1.getY(),
        point2.getX(), point2.getY(),
        point3.getX(), point3.getY()
    );

    return point3;
}