#ifndef _STOP_H_
#define _STOP_H_
#include "../../../../Attributes/SVGAttributes.h"
#include "../../../../extendLib/rapid_xml/rapidxml.hpp"
class Stop
{
private:
    rapidxml::xml_node<> *stopNode;
    SVGAttributes attributes;
public:
    Stop(rapidxml::xml_node<> *stopNode);
    // float GetOffSet();
    // Gdiplus::Color GetStopColor();
    SVGAttributes getAttributes();
    // std::string toString();
    ~Stop();
};

#endif