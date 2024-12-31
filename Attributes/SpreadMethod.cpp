#include "SpreadMethod.h"

SpreadMethod::SpreadMethod()
{
    this->method = "pad";
}

SpreadMethod::SpreadMethod(std::string value)
{
    if (value == "pad" || value == "reflect" || value == "repeat")
    {
        this->method = value;
    }
    else
    {
        this->method = "pad";
    }
}

std::string SpreadMethod::getMethod()
{
    return this->method;
}

Attribute* SpreadMethod::clone()
{
    return new SpreadMethod(*this);
}

Attribute* SpreadMethod::clone(std::string value)
{
    return new SpreadMethod(value);
}

void SpreadMethod::mergeData(Attribute* attribute)
{
    // Nothing to do
}

std::string SpreadMethod::toString()
{
    return "SpreadMethod: " + method;
}

SpreadMethod::~SpreadMethod()
{
}