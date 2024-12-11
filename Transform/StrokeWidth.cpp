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

// Destructor
StrokeWidth::~StrokeWidth() {}
