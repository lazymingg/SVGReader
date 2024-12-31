#include "StopColor.h"

StopColor::StopColor()
{
    color = Gdiplus::Color::Black;
}

StopColor::StopColor(std::string value)
{
    color = getColor(value);
}

Gdiplus::Color StopColor::getStopColor()
{
    return color;
}

Attribute *StopColor::clone()
{
    return new StopColor(*this);
}

Attribute *StopColor::clone(std::string value)
{
    return new StopColor(value);
}

void StopColor::mergeData(Attribute *attribute)
{
    //nothing
}

string StopColor::toString()
{
    return "Stop color: " + color.GetA() + ',' + color.GetR() + ',' + color.GetG() + ',' + color.GetB() + ')';
}

StopColor::~StopColor()
{
}
