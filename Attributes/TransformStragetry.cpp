#include "TransformStragetry.h"

Translate::Translate(string str)
{
<<<<<<< HEAD
    size_t openBracket = str.find("(");
    size_t closeBracket = str.find(")");
    size_t comma = str.find(",");

    //find " " if there is no comma
    if (comma == string::npos) comma = str.find(" ");
    
    if (comma == string::npos)
    {
        dx = stod(str.substr(openBracket + 1, closeBracket - openBracket - 1));
=======
    int len = str.length();
    int i = str.find("(") + 1;
    dx = extractNumber(str, i);
    if (i == len - 1)
>>>>>>> 4534dd95f8ba05792504bc87df0fbb7afea6e574
        dy = 0;
    else
        dy = extractNumber(str, i);

    cout << ("Translate: " + to_string(dx) +  ", " + to_string(dy)) << endl;

    // size_t openBracket = str.find("(");
    // size_t closeBracket = str.find(")");
    // size_t comma = str.find(",");
    // if (comma == string::npos)
    // {
    //     dx = stod(str.substr(openBracket + 1, closeBracket - openBracket - 1));
    //     dy = 0;
    // }
    // else
    // {
    //     dx = stod(str.substr(openBracket + 1, comma - openBracket - 1));
    //     dy = stod(str.substr(comma + 1, closeBracket - comma - 1));
    // }
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

string Translate::toString()
{
    return "Translate: " + to_string(dx) +  ", " + to_string(dy);
}

Scale::Scale(string str)
{
    int len = str.length();
    int i = str.find("(") + 1;
    sx = extractNumber(str, i);
    if (i == len - 1)
        sy = sx;
    else
        sy = extractNumber(str, i);

    cout << ("Scale: " + to_string(sx) + ", " + to_string(sy)) << endl;
    // size_t openBracket = str.find("(");
    // size_t closeBracket = str.find(")");
    // size_t comma = str.find(",");
    // if (comma == string::npos)
    //     sx = sy = stod(str.substr(openBracket + 1, closeBracket - openBracket - 1));
    // else
    // {
    //     sx = stod(str.substr(openBracket + 1, comma - openBracket - 1));
    //     sy = stod(str.substr(comma + 1, closeBracket - comma - 1));
    // }
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

string Scale::toString()
{
    return "Scale: " + to_string(sx) + ", " + to_string(sy);
}

Rotate::Rotate(string str)
{
    int len = str.length();
    int i = str.find("(") + 1;
    angle = extractNumber(str, i);
    if (i == len - 1)
        point = {0, 0};
    else
        point = MyPoint::Point(extractNumber(str, i), extractNumber(str, i));

    cout << ("Rotate: " + to_string(angle) + ", (" + to_string(point.getX()) + ',' + to_string(point.getY()) + ")") << endl;
    // size_t openBracket = str.find("(");
    // size_t closeBracket = str.find(")");
    // angle = stod(str.substr(openBracket + 1, closeBracket - openBracket - 1));
}

void Rotate::transform(Gdiplus::Matrix &matrix)
{
    matrix.RotateAt(angle, {point.getX(), point.getY()});
}

TransformStragetry *Rotate::clone()
{
    return new Rotate(*this);
}

void Rotate::print()
{
    std::cout << "Rotate: " << angle << std::endl;
}

string Rotate::toString()
{
    return "Rotate: " + to_string(angle) + ", (" + to_string(point.getX()) + ',' + to_string(point.getY()) + ")";
}
