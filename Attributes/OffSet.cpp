#include "OffSet.h"

OffSet::OffSet()
{
}

OffSet::OffSet(std::string value)
{
    //percentage ::= number "%"
    std::regex lengthPercentageRegex("^([0-9]*\\.?[0-9]+)%$");
    //number ::= integer
            // | [+-]? [0-9]* "." [0-9]+
    std::regex plainNumberRegex("^([0-9]*\\.?[0-9]+)$");

    std::smatch match;
    if (std::regex_match(value, match, lengthPercentageRegex))
    {
        offSet = std::stof(match.str(1));
        offSet /= 100.0f;
    }
    else if (std::regex_match(value, match, plainNumberRegex))
    {
        offSet = std::stof(match.str(1));
    }
    else
    {
        offSet = 0.0f;
    }
}

float OffSet::getOffSet()
{
    return offSet;
}

Attribute *OffSet::clone()
{
    return new OffSet(*this);
}

Attribute *OffSet::clone(std::string value)
{
    return new OffSet(value);
}

void OffSet::mergeData(Attribute *attribute)
{
    //nothing to do
}

OffSet::~OffSet()
{
}
