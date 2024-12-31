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
}

void MyPoint::Point::setX(float x)
{
    this->x = x;
}

void MyPoint::Point::setY(float y)
{
    this->y = y;
}

float MyPoint::Point::getX() const
{
    return x;
}

float MyPoint::Point::getY() const
{
    return y;
}

void MyPoint::Point::print() const
{
    cout << "(" << x << ", " << y << ")" << endl;
}