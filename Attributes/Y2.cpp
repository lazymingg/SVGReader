#include "Y2.h"

// Constructor
Y2::Y2()
{
    value = 0.0f; // Default value
}

// Constructor with value
Y2::Y2(std::string valueStr)
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

// Getter for y2 value
float Y2::getValue()
{
    return value;
}

// Clone method
Attribute* Y2::clone()
{
    return new Y2(*this);
}

Attribute* Y2::clone(std::string value)
{
    return new Y2(value);
}

// This function will be called if the attribute already exists
void Y2::mergeData(Attribute* attribute)
{
    // Don't need to do anything because y2 is a single attribute
}

// Destructor
Y2::~Y2() {}