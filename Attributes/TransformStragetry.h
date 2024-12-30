#ifndef _TRANSFORM_STRAGETRY_H_
#define _TRANSFORM_STRAGETRY_H_

#include <iostream>
#include <cmath>
#include <Windows.h>
#include <gdiplus.h>
#include <objidl.h>
#include <string>
using namespace std;

#define M_PI 3.14159265358979323846
class TransformStragetry
{
protected:
public:
    virtual void transform(Gdiplus::Matrix &matrix) = 0;

    virtual TransformStragetry *clone() = 0;
    virtual void print() = 0;
    virtual string toString() = 0;
};

class Translate : public TransformStragetry
{
private:
    double dx, dy;

public:
    Translate(string str);
    void transform(Gdiplus::Matrix &matrix) override;
    TransformStragetry *clone() override;
    void print() override;
    string toString() override;
};

class Scale : public TransformStragetry
{
private:
    double sx, sy;

public:
    Scale(string str);
    void transform(Gdiplus::Matrix &matrix) override;
    TransformStragetry *clone() override;
    void print() override;
    string toString() override;
};

class Rotate : public TransformStragetry
{
private:
    double angle;

public:
    Rotate(string str);
    void transform(Gdiplus::Matrix &matrix) override;
    TransformStragetry *clone() override;
    void print() override;
    string toString() override;
};

#endif