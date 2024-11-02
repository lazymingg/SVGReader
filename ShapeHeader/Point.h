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
        int x;
        int y;
    public:
        Point();
        Point(int x, int y);
        ~Point();
        void setX(int x);
        void setY(int y);
        int getY();
        int getX();
        void print();
    };
}
#endif