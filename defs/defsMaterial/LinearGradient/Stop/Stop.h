#ifndef _STOP_H_
#define _STOP_H_
#include "../../../Transform/SVGAttributes.h"
#include "../../../extendLib/rapid_xml/rapidxml.hpp"
class Stop
{
private:
    rapidxml::xml_node<> *stopNode;
    SVGAttributes attributes;
public:
    Stop(rapidxml::xml_node<> *stopNode);
    float GetOffSet();
    Gdiplus::Color GetStopColor();
    ~Stop();
};

#endif