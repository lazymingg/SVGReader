#include "TransformStragetry.h"

Translate::Translate(string str)
{
    size_t openBracket = str.find("(");
    size_t closeBracket = str.find(")");
    size_t comma = str.find(",");
    if (comma == string::npos)
    {
        dx = stod(str.substr(openBracket + 1, closeBracket - openBracket - 1));
        dy = 0;
    }
    else
    {
        dx = stod(str.substr(openBracket + 1, comma - openBracket - 1));
        dy = stod(str.substr(comma + 1, closeBracket - comma - 1));
    }
}

void Translate::transform(Gdiplus::Matrix &matrix)
{
    matrix.Translate(dx, dy);
}

TransformStragetry *Translate::clone()
{
    return new Translate(*this);
}

void Translate::print()
{
    std::cout << "Translate: " << dx << " " << dy << std::endl;
}

Scale::Scale(string str)
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

void Scale::transform(Gdiplus::Matrix &matrix)
{
    matrix.Scale(sx, sy);
}

TransformStragetry *Scale::clone()
{
    return new Scale(*this);
}

void Scale::print()
{
    std::cout << "Scale: " << sx << " " << sy << std::endl;
}

Rotate::Rotate(string str)
{
    size_t openBracket = str.find("(");
    size_t closeBracket = str.find(")");
    angle = stod(str.substr(openBracket + 1, closeBracket - openBracket - 1));
}

void Rotate::transform(Gdiplus::Matrix &matrix)
{
    matrix.Rotate(angle);
}

TransformStragetry *Rotate::clone()
{
    return new Rotate(*this);
}

void Rotate::print()
{
    std::cout << "Rotate: " << angle << std::endl;
}