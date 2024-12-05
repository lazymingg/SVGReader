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
};

class Scale : public TransformStragetry
{
private:
    double sx, sy;

public:
    Scale(string str)
    {
        size_t openBracket = str.find("(");
        size_t closeBracket = str.find(")");
        size_t comma = str.find(",");
        if (comma == string::npos)
            sx = sy = stod(str.substr(openBracket + 1, closeBracket - openBracket - 1));
        else
        {
            sx = stod(str.substr(openBracket + 1, comma - openBracket - 1));
            sy = stod(str.substr(comma + 1, closeBracket - comma - 1));
        }
    }
    void transform(Gdiplus::Matrix &matrix) override
    {
        matrix.Scale(sx, sy);
    }

    TransformStragetry *clone() override
    {
        return new Scale(*this);
    }

    void print() override
    {
        std::cout << "Scale: " << sx << " " << sy << std::endl;
    }
};

class Rotate : public TransformStragetry
{
private:
    double angle;

public:
    Rotate(string str)
    {
        size_t openBracket = str.find("(");
        size_t closeBracket = str.find(")");
        angle = stod(str.substr(openBracket + 1, closeBracket - openBracket - 1));
    }
    void transform(Gdiplus::Matrix &matrix) override
    {
        matrix.Rotate(angle);
    }

    TransformStragetry *clone() override
    {
        return new Rotate(*this);
    }

    void print() override
    {
        std::cout << "Rotate: " << angle << std::endl;
    }
};

#endif