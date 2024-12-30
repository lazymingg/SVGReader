#include "X1.h"

// Constructor
X1::X1()
{
    value = 0.0f; // Default value
}

// Constructor with value
X1::X1(std::string valueStr)
{
    std::regex percentageRegex(R"((\d+(\.\d+)?)%)");
    std::smatch match;

    if (std::regex_match(valueStr, match, percentageRegex))
    {
        float percentageValue = std::stof(match[1].str());
        value = percentageValue / 100.0f; // Convert percentage to a fraction
    }
    else
    {
        value = std::stof(valueStr); // Convert length or number directly
    }
}

// Getter for x1 value
float X1::getValue()
{
    return value;
}

// Clone method
Attribute* X1::clone()
{
    return new X1(*this);
}

Attribute* X1::clone(std::string value)
{
    return new X1(value);
}

// This function will be called if the attribute already exists
void X1::mergeData(Attribute* attribute)
{
    // Don't need to do anything because x1 is a single attribute
}

string X1::toString()
{
    return "X1: " + to_string(value);
}

// Destructor
X1::~X1() {}