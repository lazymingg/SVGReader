#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "TransformStragetry.h"

using namespace std;

class Transform
{
private:
    TransformStragetry *stragetry;

public:
    Transform();
    void setTransform(string str);
    void transform(MyMatrix::Matrix &matrix);
    ~Transform()
    {
        delete stragetry;
    }
};

#endif