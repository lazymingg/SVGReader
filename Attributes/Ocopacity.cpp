#include "Ocopacity.h"
#include <regex>

// Constructor
Ocopacity::Ocopacity() : value(1.0f) {}

// Constructor with value
Ocopacity::Ocopacity(std::string value)
{
    std::regex numberRegex(R"(opacity\s*=\s*\"([0-9]*\.?[0-9]+)\")");
    std::regex percentageRegex(R"(opacity\s*=\s*\"([0-9]+)%\")");
    std::smatch match;

    if (std::regex_search(value, match, numberRegex))
    {
        this->value = std::stof(match[1].str());
    }
    else if (std::regex_search(value, match, percentageRegex))
    {
        this->value = std::stof(match[1].str()) / 100.0f;
    }
}

// Getter for opacity
float Ocopacity::getOcopacity()
{
    return value;
}

// Clone method
Attribute* Ocopacity::clone()
{
    return new Ocopacity(*this);
}

Attribute *Ocopacity::clone(string value)
{
    return new Ocopacity(value);
}

void Ocopacity::mergeData(Attribute *attribute)
{
    Ocopacity *ocopacity = dynamic_cast<Ocopacity *>(attribute);
    //multiple fill-opacity
    if (ocopacity)
    {
        value *= ocopacity->value;
    }
}

string Ocopacity::toString()
{
    return "Opacity: " + to_string(value);
}

// Destructor
Ocopacity::~Ocopacity() {}
