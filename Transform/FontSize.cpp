#include "FontSize.h"
#include "Attribute.h"
#include <stdexcept>
#include <sstream>

// Helper function to parse font size value
float parseFontSize(std::string value)
{
    std::regex absoluteSizeRegex("^(xx-small|x-small|small|medium|large|x-large|xx-large)$");
    std::regex relativeSizeRegex("^(larger|smaller)$");
    std::regex lengthPercentageRegex("^([0-9]*\\.?[0-9]+)(em|ex|px|pt|pc|in|cm|mm|%)$");

    std::smatch match;
    if (std::regex_match(value, match, absoluteSizeRegex))
    {
        // Map absolute sizes to a float value (example values)
        if (value == "xx-small") return 8.0f;
        if (value == "x-small") return 10.0f;
        if (value == "small") return 12.0f;
        if (value == "medium") return 16.0f;
        if (value == "large") return 18.0f;
        if (value == "x-large") return 24.0f;
        if (value == "xx-large") return 32.0f;
    }
    else if (std::regex_match(value, match, relativeSizeRegex))
    {
        // Map relative sizes to a float value (example values)
        if (value == "larger") return 1.2f; // 120% of the parent element's font size
        if (value == "smaller") return 0.8f; // 80% of the parent element's font size
    }
    else if (std::regex_match(value, match, lengthPercentageRegex))
    {
        return std::stof(match.str(1));
    }
    else
    {
        throw std::invalid_argument("Invalid font size value");
    }

    return 16.0f; // Default to medium if no match
}

// Constructor
FontSize::FontSize() : size(16.0f) {} // Default to medium

// Constructor with value
FontSize::FontSize(std::string value)
{
    size = parseFontSize(value);
}

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