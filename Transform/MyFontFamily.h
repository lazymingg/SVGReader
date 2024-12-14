#ifndef MYFONTFAMILY_H
#define MYFONTFAMILY_H

#include "Attribute.h"
#include <string>
#include <Gdiplus.h>

// MyFontFamily class for handling font family attributes
class MyFontFamily : public Attribute
{
private:
    Gdiplus::FontFamily* fontFamily;

public:
    MyFontFamily();
    MyFontFamily(std::string value);
    Gdiplus::FontFamily* getFontFamily();
    Attribute* clone() override;
    void mergeData(Attribute* attribute) override;
    ~MyFontFamily();
};

#endif