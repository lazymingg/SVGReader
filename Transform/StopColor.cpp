#include "StopColor.h"

StopColor::StopColor()
{
}

StopColor::StopColor(std::string value)
{
    color = getColor(value);
}
