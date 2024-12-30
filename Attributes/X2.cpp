#include "X2.h"

// Constructor
X2::X2()
{
    value = 0.0f; // Default value
}

// Constructor with value
X2::X2(std::string valueStr)
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

// Getter for x2 value
float X2::getValue()
{
    return value;
}

// Clone method
Attribute* X2::clone()
{
    return new X2(*this);
}

Attribute* X2::clone(std::string value)
{
    return new X2(value);
}

// This function will be called if the attribute already exists
void X2::mergeData(Attribute* attribute)
{
    // Don't need to do anything because x2 is a single attribute
}

string X2::toString()
{
    return "X2: " + to_string(value);
}

// Destructor
X2::~X2() {}