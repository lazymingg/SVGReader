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

Attribute *StrokeOpacity::clone(string value)
{
    return new StrokeOpacity(value);
}

void StrokeOpacity::mergeData(Attribute *attribute)
{
    StrokeOpacity *strokeOpacity = dynamic_cast<StrokeOpacity *>(attribute);
    //multiple stroke-opacity
    if (strokeOpacity)
    {
        value *= strokeOpacity->value;
    }
}

string StrokeOpacity::toString()
{
    return "Stroke Opacity: " + to_string(value);
}

// Destructor
StrokeOpacity::~StrokeOpacity() {}
