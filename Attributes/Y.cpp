#include "Y.h"

// Constructor
Y::Y()
{
    yValues.push_back(0.0f); // Default value
}

// Constructor with value
Y::Y(string value)
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
            yValues.push_back(percentageValue / 100.0f); // Convert percentage to a fraction
        }
        else
        {
            yValues.push_back(std::stof(matchStr)); // Convert length or number directly
        }
        searchStart = match.suffix().first;
    }

    if (yValues.empty())
    {
        yValues.push_back(0.0f); // Default value if no valid input
    }
}

// Getter for y values
std::vector<float> Y::getYValues(size_t length) const
{
    std::vector<float> result = yValues;
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
Attribute* Y::clone()
{
    return new Y(*this);
}

Attribute* Y::clone(string value)
{
    return new Y(value);
}

// This function will be called if the attribute already exists
void Y::mergeData(Attribute* attribute)
{
    // Don't need to do anything because y is a single attribute
}

string Y::toString()
{
    int len = yValues.size();
    string s = "Y values: ";
    if (len == 0)
        return s + "empty";
        
    for (int i = 0; i < len; ++i)
    {
        s += yValues[i];
        if (i != len - 1)
            s += ", ";
    }
    return s;
}

// Destructor
Y::~Y() {}