#include "../ShapeHeader/Point.h"

MyPoint::Point::Point()
{
    x = 0;
    y = 0;
}
MyPoint::Point::Point(float x, float y)
{
    this->x = x;
    this->y = y;
}
MyPoint::Point::~Point()
{
    //nothing to do here
}
void MyPoint::Point::setX(float x)
{
    this->x = x;
}
void MyPoint::Point::setY(float y)
{
    this->y = y;
}
float MyPoint::Point::getX()
{
    return x;
}
float MyPoint::Point::getY()
{
    return y;
}
void MyPoint::Point::print()
{
    cout << "Point: (" << x << ", " << y << ")" << endl;
}
