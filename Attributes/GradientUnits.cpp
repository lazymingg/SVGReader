#include "GradientUnits.h"

GradientUnits::GradientUnits()
{
    this->units = "objectBoundingBox";
}

GradientUnits::GradientUnits(std::string value)
{
    if (value == "userSpaceOnUse" || value == "objectBoundingBox")
    {
        this->units = value;
    }
    else
    {
        this->units = "objectBoundingBox";
    }
}

std::string GradientUnits::getUnits()
{
    return this->units;
}

Attribute* GradientUnits::clone()
{
    return new GradientUnits(*this);
}

Attribute* GradientUnits::clone(std::string value)
{
    return new GradientUnits(value);
}

void GradientUnits::mergeData(Attribute* attribute)
{
    // Nothing to do
}

std::string GradientUnits::toString()
{
    return "GradientUnits: " + units;
}

GradientUnits::~GradientUnits()
{
}