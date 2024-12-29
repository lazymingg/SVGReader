#include "Y1.h"

// Constructor
Y1::Y1()
{
    value = 0.0f; // Default value
}

// Constructor with value
Y1::Y1(std::string valueStr)
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

// Getter for y1 value
float Y1::getValue()
{
    return value;
}

// Clone method
Attribute* Y1::clone()
{
    return new Y1(*this);
}

Attribute* Y1::clone(std::string value)
{
    return new Y1(value);
}

// This function will be called if the attribute already exists
void Y1::mergeData(Attribute* attribute)
{
    // Don't need to do anything because y1 is a single attribute
}

// Destructor
Y1::~Y1() {}