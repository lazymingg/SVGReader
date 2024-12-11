#include "StrokeOcopacity.h"
#include <regex>

// Constructor
StrokeOpacity::StrokeOpacity() : value(1.0f) {}

// Constructor with value
StrokeOpacity::StrokeOpacity(std::string getValue)
{
    std::regex percentageRegex(R"(^([0-9]+)%$)");
    std::regex decimalRegex(R"(^([0-9]*\.?[0-9]+)$)");
    std::smatch match;

    if (std::regex_match(getValue, match, percentageRegex))
    {
        value = std::stof(match[1].str()) / 100.0f;
    }
    else if (std::regex_match(getValue, match, decimalRegex))
    {
        value = std::stof(match[1].str());
    }
}

// Getter for stroke opacity
float StrokeOpacity::getStrokeOpacity()
{
    return value;
}

// Clone method
Attribute* StrokeOpacity::clone()
{
    return new StrokeOpacity(*this);
}

// Destructor
StrokeOpacity::~StrokeOpacity() {}
