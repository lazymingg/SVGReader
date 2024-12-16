#include "../../ShapeHeader/Path/Segment.h"

float Segment::toAbsoluteX(const char &curCommand, const std::string &data, int &index, MyPoint::Point start)
{
    if (isCapitalizedAlpha(curCommand))
        return extractNumber(data, index);
    else
        return start.getX() + extractNumber(data, index);
}

float Segment::toAbsoluteY(const char &curCommand, const std::string &data, int &index, MyPoint::Point start)
{
    if (isCapitalizedAlpha(curCommand))
        return extractNumber(data, index);
    else
        return start.getY() + extractNumber(data, index);
}

MyPoint::Point Segment::toAbsolute(const char &curCommand, const std::string &data, int &index, MyPoint::Point start)
{
    if (isCapitalizedAlpha(curCommand))
        return {extractNumber(data, index), extractNumber(data, index)};
    else
        return {start.getX() + extractNumber(data, index), start.getY() + extractNumber(data, index)};
}