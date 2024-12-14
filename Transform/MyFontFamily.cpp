#include "MyFontFamily.h"
#include "Attribute.h"
#include <stdexcept>
#include <sstream>

// Constructor
MyFontFamily::MyFontFamily() : fontFamily(new Gdiplus::FontFamily(L"Times New Roman")) {} // Default to Times New Roman

// Constructor with value
MyFontFamily::MyFontFamily(std::string value)
{
    std::regex familyNameRegex(R"(^[a-zA-Z0-9\s]+$)");
    std::regex genericFamilyRegex(R"(^(serif|sans-serif|system-ui|cursive|fantasy|math|monospace|ui-serif|ui-sans-serif|ui-monospace|ui-rounded|generic\(kai\)|generic\(fangsong\)|generic\(nastaliq\))$)");

    if (std::regex_match(value, familyNameRegex) || std::regex_match(value, genericFamilyRegex))
    {
        std::wstring wValue(value.begin(), value.end());
        fontFamily = new Gdiplus::FontFamily(wValue.c_str());
    }
    else
        fontFamily = new Gdiplus::FontFamily(L"Times New Roman");
}

// Getter for font family
Gdiplus::FontFamily *MyFontFamily::getFontFamily()
{
    return fontFamily;
}

// Clone method
Attribute *MyFontFamily::clone()
{
    return new MyFontFamily(*this);
}

Attribute *MyFontFamily::clone(string value)
{
    return new MyFontFamily(value);
}

// This function will be called if the attribute already exists
void MyFontFamily::mergeData(Attribute *attribute)
{
    // Don't need to do anything because font family is a single attribute
}

// Destructor
MyFontFamily::~MyFontFamily()
{
    delete fontFamily;
}