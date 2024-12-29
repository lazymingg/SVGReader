#include "X.h"

// Constructor
X::X()
{
    xValues.push_back(0.0f); // Default value
}

// Constructor with value
X::X(string value)
{
    std::regex valueRegex(R"((\d+(\.\d+)?%?))");
    std::smatch match;

    std::string::const_iterator searchStart(value.cbegin());
    while (std::regex_search(searchStart, value.cend(), match, valueRegex))
    {
        std::string matchStr = match[0].str();
        if (matchStr.back() == '%')
        {
            float percentageValue = std::stof(matchStr.substr(0, matchStr.size() - 1));
            xValues.push_back(percentageValue / 100.0f); // Convert percentage to a fraction
        }
        else
        {
            xValues.push_back(std::stof(matchStr)); // Convert length or number directly
        }
        searchStart = match.suffix().first;
    }

    if (xValues.empty())
    {
        xValues.push_back(0.0f); // Default value if no valid input
    }
}

// Getter for x values
std::vector<float> X::getXValues(size_t length) const
{
    std::vector<float> result = xValues;
    if (result.size() == 1)
    {
        result.resize(length, result[0]); // Apply single value to all glyphs
    }
    else if (result.size() < length)
    {
        result.resize(length, result.back()); // Extend with the last value
    }
    return result;
}

// Clone method
Attribute* X::clone()
{
    return new X(*this);
}

Attribute* X::clone(string value)
{
    return new X(value);
}

// This function will be called if the attribute already exists
void X::mergeData(Attribute* attribute)
{
    // Don't need to do anything because x is a single attribute
}

// Destructor
X::~X() {}