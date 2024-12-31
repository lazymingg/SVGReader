#include "FontWeight.h"
#include "Attribute.h"
#include <stdexcept>
#include <sstream>

// Constructor with value
FontWeight::FontWeight(std::string value)
{
    std::regex keywordRegex("^(normal|bold|bolder|lighter)$");
    std::regex numberRegex("^([1-9]00)$");

    std::smatch match;
    if (std::regex_match(value, match, keywordRegex))
    {
        weight = value;
    }
    else if (std::regex_match(value, match, numberRegex))
    {
        weight = value;
    }
    else
    {
        weight = "normal"; // Default to normal if no match
    }
}

// Default constructor
FontWeight::FontWeight() : weight("normal") {}

// Getter for font weight
std::string FontWeight::getFontWeight()
{
    return weight;
}

// Clone method
Attribute* FontWeight::clone()
{
    return new FontWeight(*this);
}

Attribute* FontWeight::clone(std::string value)
{
    return new FontWeight(value);
}

// This function will be called if the attribute already exists
void FontWeight::mergeData(Attribute* attribute)
{
    // Don't need to do anything because font weight is a single attribute
}

std::string FontWeight::toString()
{
    //to String
    return weight; 
}

// Destructor
FontWeight::~FontWeight() {}