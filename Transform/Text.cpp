#include "Text.h"

// Constructor
Text::Text() : text("") {}

// Constructor with text value
Text::Text(std::string text) : text(text) {}

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

void Text::mergeData(Attribute *attribute)
{
    // donothings
}

// Destructor
Text::~Text() {}
