#include "StopColor.h"

StopColor::StopColor()
{
}

StopColor::StopColor(std::string value)
{
    color = getColor(value);
}

Gdiplus::Color StopColor::getStopColor()
{
    return Gdiplus::Color();
}

Attribute *StopColor::clone()
{
    return nullptr;
}

Attribute *StopColor::clone(std::string value)
{
    return nullptr;
}

void StopColor::mergeData(Attribute *attribute)
{
}

StopColor::~StopColor()
{
}
