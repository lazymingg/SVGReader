#ifndef FONTWEIGHT_H
#define FONTWEIGHT_H

#include "Attribute.h"
#include <string>
#include <regex>

// FontWeight class for handling font weight attributes
class FontWeight : public Attribute
{
private:
    std::string weight;

public:
    FontWeight();
    FontWeight(std::string value);
    std::string getFontWeight();
    Attribute* clone() override;
    Attribute* clone(std::string value) override;
    void mergeData(Attribute* attribute) override;
    ~FontWeight();
};

#endif