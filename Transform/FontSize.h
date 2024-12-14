#ifndef FONTSIZE_H
#define FONTSIZE_H

#include "Attribute.h"
#include <string>
#include <regex>

// FontSize class for handling font size attributes
class FontSize : public Attribute
{
private:
    float size;

public:
    FontSize();
    FontSize(std::string value);
    float getFontSize();
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    ~FontSize();
};

#endif