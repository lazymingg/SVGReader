#include "TextAnchor.h"

// Default constructor
TextAnchor::TextAnchor() : anchor("start") {}

// Constructor with value
TextAnchor::TextAnchor(std::string value) : anchor(value) {}

// Get the text-anchor value
std::string TextAnchor::getTextAnchor() {
    return anchor;
}

// Clone the TextAnchor object
Attribute* TextAnchor::clone() {
    return new TextAnchor(*this);
}

// Merge data from another attribute
void TextAnchor::mergeData(Attribute* attribute) {
    TextAnchor* textAnchor = dynamic_cast<TextAnchor*>(attribute);
    if (textAnchor) {
        this->anchor = textAnchor->anchor;
    }
}

// Destructor
TextAnchor::~TextAnchor() {}