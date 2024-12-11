#include "FontSize.h"
#include "Attribute.h"
#include <stdexcept>
#include <sstream>

// Helper function to parse font size value

FontSize::FontSize(std::string value)
{
    std::regex absoluteSizeRegex("^(xx-small|x-small|small|medium|large|x-large|xx-large)$");
    std::regex relativeSizeRegex("^(larger|smaller)$");
    std::regex lengthPercentageRegex("^([0-9]*\\.?[0-9]+)(em|ex|px|pt|pc|in|cm|mm|%)$");
    std::regex plainNumberRegex("^([0-9]*\\.?[0-9]+)$");

    std::smatch match;
    if (std::regex_match(value, match, absoluteSizeRegex))
    {
        // Map absolute sizes to a float value (example values)
        if (value == "xx-small") size = 8.0f;
        else if (value == "x-small") size = 10.0f;
        else if (value == "small") size = 12.0f;
        else if (value == "medium") size = 16.0f;
        else if (value == "large") size = 18.0f;
        else if (value == "x-large") size = 24.0f;
        else if (value == "xx-large") size = 32.0f;
    }
    else if (std::regex_match(value, match, relativeSizeRegex))
    {
        // Map relative sizes to a float value (example values)
        if (value == "larger") size = 1.2f; // 120% of the parent element's font size
        if (value == "smaller") size = 0.8f; // 80% of the parent element's font size
    }
    else if (std::regex_match(value, match, lengthPercentageRegex))
    {
        size = std::stof(match.str(1));
    }
    else if (std::regex_match(value, match, plainNumberRegex))
    {
        size = std::stof(match.str(1));
    }
    else
    {
        size = 16.0f; // Default to medium if no match
    }
}

// Constructor
FontSize::FontSize() : size(16.0f) {} // Default to medium


// Getter for font size
float FontSize::getFontSize() 
{
    return size;
}

// Clone method
Attribute* FontSize::clone()
{
    return new FontSize(*this);
}

// This function will be called if the attribute already exists
void FontSize::mergeData(Attribute *attribute)
{
    // Don't need to do anything because font size is a single attribute
}

// Destructor
FontSize::~FontSize() {}