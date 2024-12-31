#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
using namespace std;

namespace MyPoint
{
    class Point
    {
    private:
        float x;
        float y;

    public:
        Point();
        Point(float x, float y);
        ~Point();
        void setX(float x);
        void setY(float y);
        float getX() const;
        float getY() const;
        void print() const;
    };
}

#endif