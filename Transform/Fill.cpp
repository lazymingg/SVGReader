#include "Fill.h"
#include "Attribute.h"

// Helper function to convert HEX to Gdiplus::Color
Gdiplus::Color hexToColor(const std::string &hex);

Gdiplus::Color getColor(const std::string &value);

// Constructor
Fill::Fill() {}

// Constructor with value
Fill::Fill(std::string value)
{
    color = getColor(value);
}

// Getter for Fill color
Gdiplus::Color Fill::getFill()
{
    return color;
}

// Clone method
Attribute* Fill::clone()
{
    return new Fill(*this);
}

// Destructor
Fill::~Fill() {}
