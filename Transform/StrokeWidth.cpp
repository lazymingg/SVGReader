#include "StrokeWidth.h"
#include <string>

// Constructor
StrokeWidth::StrokeWidth() : width(1.0f) {}

// Constructor with width
StrokeWidth::StrokeWidth(std::string width)
{
    this->width = std::stof(width);
}

// Getter for Stroke Width
float StrokeWidth::getStrokeWidth()
{
    return width;
}

// Clone method
Attribute* StrokeWidth::clone()
{
    return new StrokeWidth(*this);
}

void StrokeWidth::mergeData(Attribute *attribute)
{
    // do nothing
}

Attribute *StrokeWidth::clone(string value)
{
    return new StrokeWidth(value);
}

// Destructor
StrokeWidth::~StrokeWidth() {}
