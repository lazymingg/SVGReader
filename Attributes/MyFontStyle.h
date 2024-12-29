#ifndef MYFONTSTYLE_H
#define MYFONTSTYLE_H

#include "Attribute.h"
#include <string>
#include <regex>
#include <stdexcept>
#include <gdiplus.h>

// MyFontStyle class for handling font style attributes
class MyFontStyle : public Attribute
{
private:
    Gdiplus::FontStyle fontStyle;

public:
    MyFontStyle();
    MyFontStyle(std::string value);
    Gdiplus::FontStyle getFontStyle() const;
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    ~MyFontStyle();
};

#endif