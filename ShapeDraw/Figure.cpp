#include "../ShapeHeader/Figure.h"

Figure::Figure(xml_node<>* shapeNode, Gdiplus::Graphics &graphics) : attributes(shapeNode), shapeNode(shapeNode), graphics(graphics) {}

SVGAttributes &Figure::getAttributes()
{
    return attributes;
}
