#include "../ShapeHeader/Point.h"

MyPoint::Point::Point()
{
    x = 0;
    y = 0;
}
MyPoint::Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}
MyPoint::Point::~Point()
{
    //nothing to do here
}
void MyPoint::Point::setX(int x)
{
    this->x = x;
}
void MyPoint::Point::setY(int y)
{
    this->y = y;
}
int MyPoint::Point::getX()
{
    return x;
}
int MyPoint::Point::getY()
{
    return y;
}
void MyPoint::Point::print()
{
    cout << "Point: (" << x << ", " << y << ")" << endl;
}
