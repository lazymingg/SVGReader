#include "Stroke.h"
#include "Fill.h"

// Constructor
Stroke::Stroke()
{
    color = Gdiplus::Color(0, 0, 0, 0);
}

// Constructor with value
Stroke::Stroke(std::string value)
{
    color = getColor(value);
}

// Getter for Stroke color
Gdiplus::Color Stroke::getStroke()
{
    return color;
}

// Clone method
Attribute* Stroke::clone()
{
    return new Stroke(*this);
}

Attribute *Stroke::clone(string value)
{
    return new Stroke(value);
}

void Stroke::mergeData(Attribute *attribute)
{
    // do nothing
}

string Stroke::toString()
{
    return "Stroke color: " + color.GetA() + ',' + color.GetR() + ',' + color.GetG() + ',' + color.GetB() + ')';
}

// Destructor
Stroke::~Stroke() {}
