#include "FillOcopacity.h"
#include <regex>

// Constructor
FillOpacity::FillOpacity() : value(1.0f) {}

// Constructor with value
FillOpacity::FillOpacity(const std::string &getValue)
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

// Getter for fill opacity
float FillOpacity::getFillOpacity()
{
    return value;
}

// Clone method
Attribute* FillOpacity::clone()
{
    return new FillOpacity(*this);
}

// Destructor
FillOpacity::~FillOpacity() {}
