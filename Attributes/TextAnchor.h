#ifndef TEXTANCHOR_H
#define TEXTANCHOR_H

#include "Attribute.h"
#include <string>

// TextAnchor class for handling text-anchor attributes
class TextAnchor : public Attribute
{
private:
    std::string anchor;

public:
    TextAnchor();
    TextAnchor(std::string value);
    std::string getTextAnchor();
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    ~TextAnchor();
};

#endif