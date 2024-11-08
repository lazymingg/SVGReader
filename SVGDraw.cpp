#include "SVGDraw.h"
#include <iostream>

SVGDraw::SVGDraw(Graphics &graphics) : graphics(graphics) {}

SVGDraw::~SVGDraw()
{
    for (Figure *figure : figures)
    {
        delete figure;
    }
    figures.clear();
}

void SVGDraw::loadSVGFile(const std::string &filename)
{
    // bool isHead = false;
    SVGParser parser(filename);
    xml_node<> *rootNode = parser.getRootNode();

    for (xml_node<> *node = rootNode->first_node(); node; node = node->next_sibling())
    {
        std::string shape = node->name();

        if (shape == "text")
        {
            figures.push_back(new MyFigure::Text(node, graphics));
        }
        else if (shape == "rect")
        {
            figures.push_back(new MyFigure::Rectangle(node, graphics));
        }
        else if (shape == "line")
        {
            figures.push_back(new MyFigure::Line(node, graphics));
        }
        else if (shape == "polygon")
        {
            figures.push_back(new MyFigure::Polygon(node, graphics));
        }
        else if (shape == "polyline")
        {
            figures.push_back(new MyFigure::Polyline(node, graphics));
        }
        else if (shape == "ellipse")
        {
            figures.push_back(new MyFigure::Ellipse(node, graphics));
        }
        else if (shape == "circle")
        {
            figures.push_back(new MyFigure::Circle(node, graphics));
        }
    }
}

void SVGDraw::draw()
{
    for (Figure *figure : figures)
    {
        figure->draw();
    }
}
