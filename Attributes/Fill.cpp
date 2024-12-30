#include "Fill.h"
#include "Attribute.h"

// Constructor
Fill::Fill()
{
    color = Gdiplus::Color();
}

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

Attribute *Fill::clone(string value)
{
    return new Fill(value);
}

//this funtion will be call if the attribute is allready exist
void Fill::mergeData(Attribute *attribute)
{
    //don't need to do anything because fill is a single attribute
}

string Fill::toString()
{
    return "Fill color: (" + color.GetA() + ',' + color.GetR() + ',' + color.GetG() + ',' + color.GetB() + ')';
}

// Destructor
Fill::~Fill() {}
