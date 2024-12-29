
#include "Dx.h"

// Constructor
Dx::Dx()
{
    dxValues = {0.0f};
}

// Constructor with value
Dx::Dx(string &value)
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
            dxValues.push_back(percentageValue / 100.0f); // Convert percentage to a fraction
        }
        else
        {
            float lengthValue = std::stof(token);
            dxValues.push_back(lengthValue);
        }
    }
}

// Getter for dx values
std::vector<float> Dx::getDxValues(size_t glyphCount) const
{
    std::vector<float> result;

    if (dxValues.size() == 1)
    {
        // Single value applies to all glyphs
        result.assign(glyphCount, dxValues[0]);
    }
    else
    {
        // Multiple values apply to corresponding glyphs
        result = dxValues;

        // If there are fewer dx values than glyphs, fill the rest with 0
        if (dxValues.size() < glyphCount)
        {
            result.resize(glyphCount, 0.0f);
        }
        // If there are more dx values than glyphs, ignore the extra values
        else if (dxValues.size() > glyphCount)
        {
            result.resize(glyphCount);
        }
    }

    return result;
}

// Clone method
Attribute* Dx::clone()
{
    return new Dx(*this);
}

Attribute* Dx::clone(string value)
{
    return new Dx(value);
}

// This function will be called if the attribute already exists
void Dx::mergeData(Attribute* attribute)
{
    // Don't need to do anything because dx is a single attribute
}

// Destructor
Dx::~Dx() {}