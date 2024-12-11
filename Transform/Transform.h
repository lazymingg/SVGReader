#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>
#include <Windows.h>
#include <gdiplus.h>
#include "TransformStragetry.h"
#include "Attribute.h"

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
    Attribute* clone() override;
    void mergeData(Attribute* attribute) override;
    ~Transform();
};

#endif // TRANSFORM_H
