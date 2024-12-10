#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "TransformStragetry.h"
#include "SVGAttributes.h"
// // Forward declaration
// class SVGAttributes;

// class Attribute;

class Transform : public Attribute
{
private:
    std::vector<TransformStragetry *> stragetry;

public:
    Transform();
    Transform(std::string str);
    Transform(const Transform &transform);
    void transform(Gdiplus::Matrix &matrix);
    Transform &operator=(const Transform &transform);
    void addStragetry(Transform transform);
    Attribute *clone() override;
    ~Transform();
};

#endif
