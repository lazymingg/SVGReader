#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "TransformStragetry.h"
#include "SVGAttributes.h"
using namespace std;

class Transform : public Attribute
{
    private:
        vector<TransformStragetry *>stragetry;        
    public:
        Transform();
        Transform(string str);
        //copy constructor
        Transform(const Transform &transform);
        void transform(Gdiplus::Matrix &matrix);
        Transform &operator=(const Transform &transform);
        //void setTransform(string str);
        void addStragetry(Transform transform);
        Attribute* clone() override;
        ~Transform();
};

#endif