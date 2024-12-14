#include "MyFontStyle.h"
#include "Attribute.h"
#include <sstream>

// Constructor
MyFontStyle::MyFontStyle() : fontStyle(Gdiplus::FontStyleRegular) {} // Default to regular

// Constructor with value
MyFontStyle::MyFontStyle(std::string value)
{
    if (value == "italic")
    {
        fontStyle = Gdiplus::FontStyleItalic;
    }
    else if (value == "bold")
    {
        fontStyle = Gdiplus::FontStyleBold;
    }
    else if (value == "underline")
    {
        fontStyle = Gdiplus::FontStyleUnderline;
    }
    else if (value == "strikeout")
    {
        fontStyle = Gdiplus::FontStyleStrikeout;
    }
    else if (value == "normal")
    {
        fontStyle = Gdiplus::FontStyleRegular;
    }
    else
    {
        throw std::invalid_argument("Invalid font style value");
    }
}

// Getter for font style
Gdiplus::FontStyle MyFontStyle::getFontStyle() const
{
    return fontStyle;
}

// Clone method
Attribute* MyFontStyle::clone()
{
    return new MyFontStyle(*this);
}

Attribute* MyFontStyle::clone(string value)
{
    return new MyFontStyle(value);
}

// This function will be called if the attribute already exists
void MyFontStyle::mergeData(Attribute *attribute)
{
    // Don't need to do anything because font style is a single attribute
}

// Destructor
MyFontStyle::~MyFontStyle() {}