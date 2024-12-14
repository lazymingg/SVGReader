#include "Text.h"

// Constructor
Text::Text() : text("") {}

// Constructor with text value
Text::Text(std::string text)
{
    this->text = text;
}

// Getter for text
std::string Text::getText()
{
    return text;
}

// Clone method
Attribute* Text::clone()
{
    return new Text(*this);
}

Attribute *Text::clone(string value)
{
    return new Text(value);
}

void Text::mergeData(Attribute *attribute)
{
    // donothings
}

// Destructor
Text::~Text() {}
