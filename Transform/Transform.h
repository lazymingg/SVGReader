#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "TransformStragetry.h"

using namespace std;

class Transform : public TransformStragetry
{
    private:
        vector <TransformStragetry*> stragetry;        
    public:
        Transform();
        Transform(string str);
        MyMatrix::Matrix doTransform(MyMatrix::Matrix matrix) override;
        void setTransform(string str);
        ~Transform();
};

#endif