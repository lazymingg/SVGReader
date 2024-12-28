#include "Stop.h"

Stop::Stop(rapidxml::xml_node<> *stopNode) : stopNode(stopNode), attributes(stopNode)
{
}

float Stop::GetOffSet()
{
    return static_cast<OffSet *>(attributes.getAttributes("offset"))->getOffSet();
}

Gdiplus::Color Stop::GetStopColor()
{
    return static_cast<StopColor *>(attributes.getAttributes("stop-color"))->getStopColor();
}

Stop::~Stop()
{
}

