#include "../../ShapeHeader/Path/QuadraticBezierSegment.h"

MyPoint::Point QuadraticBezierSegment::setSegment(const char &curCommand, const std::string &data, int &index, MyPoint::Point start, MyPoint::Point &point1, MyPoint::Point &point2)
{
    point1 = toAbsolute(curCommand, data, index, start);
    point2 = toAbsolute(curCommand, data, index, start);

    MyPoint::Point control1 =
    {
        start.getX() + 2.0f / 3 * (point1.getX() - start.getX()),
        start.getY() + 2.0f / 3 * (point1.getY() - start.getY()),
    };
    
    MyPoint::Point control2 =
    {                        
        point2.getX() + 2.0f / 3 * (point1.getX() - point2.getX()),
        point2.getY() + 2.0f / 3 * (point1.getY() - point2.getY()),
    };

    segment.AddBezier
    (
        start.getX(), start.getY(),
        control1.getX(), control1.getY(),
        control2.getX(), control2.getY(),    
        point2.getX(), point2.getY()
    );

    return point2;
}

MyPoint::Point SmoothQuadraticBezierSegment::setSegment(const char &curCommand, const char &prevCommand, const std::string &data, int &index, MyPoint::Point start, MyPoint::Point &point1, MyPoint::Point &point2)
{
    if (prevCommand == 'Q' || prevCommand == 'q' || 
        prevCommand == 'T' || prevCommand == 't')
        point1 =
        {
            2 * start.getX() - point1.getX(),
            2 * start.getY() - point1.getY()
        };
    else
        point1 = start;

    point2 = toAbsolute(curCommand, data, index, start); 

    MyPoint::Point control1 =
    {
        start.getX() + 2.0f / 3 * (point1.getX() - start.getX()),
        start.getY() + 2.0f / 3 * (point1.getY() - start.getY()),
    };
    
    MyPoint::Point control2 =
    {                        
        point2.getX() + 2.0f / 3 * (point1.getX() - point2.getX()),
        point2.getY() + 2.0f / 3 * (point1.getY() - point2.getY()),
    };

    segment.AddBezier
    (
        start.getX(), start.getY(),
        control1.getX(), control1.getY(),
        control2.getX(), control2.getY(),    
        point2.getX(), point2.getY()
    );

    return point2;
}