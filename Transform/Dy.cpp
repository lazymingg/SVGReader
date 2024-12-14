#include "Dy.h"

// Constructor
Dy::Dy()
{
    dyValues = {0.0f};
}

// Constructor with value
Dy::Dy(std::string &value)
{
    std::vector<std::string> tokens;
    std::string getToken = "";
    for (size_t i = 0; i <= value.length(); i++)
    {
        if (value[i] == ',' || i == value.length())
        {
            tokens.push_back(getToken);
            getToken = "";
        }
        else
        {
            getToken += value[i];
        }
    }

    std::regex percentageRegex(R"((\d+(\.\d+)?)%)");

    for (const auto& token : tokens)
    {
        std::smatch match;
        if (std::regex_match(token, match, percentageRegex))
        {
            float percentageValue = std::stof(match[1].str());
            dyValues.push_back(percentageValue / 100.0f); // Convert percentage to a fraction
        }
        else
        {
            float lengthValue = std::stof(token);
            dyValues.push_back(lengthValue);
        }
    }
}

// Getter for dy values
std::vector<float> Dy::getDyValues(size_t glyphCount) const
{
    std::vector<float> result;

    if (dyValues.size() == 1)
    {
        // Single value applies to all glyphs
        result.assign(glyphCount, dyValues[0]);
    }
    else
    {
        // Multiple values apply to corresponding glyphs
        result = dyValues;

        // If there are fewer dy values than glyphs, fill the rest with 0
        if (dyValues.size() < glyphCount)
        {
            result.resize(glyphCount, 0.0f);
        }
        // If there are more dy values than glyphs, ignore the extra values
        else if (dyValues.size() > glyphCount)
        {
            result.resize(glyphCount);
        }
    }

    return result;
}

// Clone method
Attribute* Dy::clone()
{
    return new Dy(*this);
}

Attribute* Dy::clone(std::string value)
{
    return new Dy(value);
}

// This function will be called if the attribute already exists
void Dy::mergeData(Attribute* attribute)
{
    // Don't need to do anything because dy is a single attribute
}

// Destructor
Dy::~Dy() {}