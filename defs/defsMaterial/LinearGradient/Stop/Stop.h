#ifndef _STOP_H_
#define _STOP_H_
#include "../../../../Attributes/SVGAttributes.h"
#include "../../../../extendLib/rapid_xml/rapidxml.hpp"
class Stop
{
private:
    rapidxml::xml_node<> *stopNode;
public:
    SVGAttributes attributes;
    Stop(rapidxml::xml_node<> *stopNode);
    // float GetOffSet();
    // Gdiplus::Color GetStopColor();
    SVGAttributes getAttributes();
    void printOffSet();
    ~Stop();
};

#endif