#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
using namespace std;
// define my point class

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
        float getY();
        float getX();
        void print();
    };
}
#endif