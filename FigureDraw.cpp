#include "FigureDraw.h"
#include <iostream>

FigureDraw::FigureDraw(Graphics &graphics) : graphics(graphics) {}

FigureDraw::~FigureDraw()
{
    for (Figure *figure : figures)
    {
        delete figure;
    }
    figures.clear();
}

void FigureDraw::loadSVGFile(const std::string &filename)
{
    // bool isHead = false;
    SVGParser parser(filename);
    parser.print();
    xml_node<> *rootNode = parser.getRootNode();

    for (xml_node<> *node = rootNode->first_node(); node; node = node->next_sibling())
    {
        std::string element = node->name();

        if (element == "text")
        {
            figures.push_back(new MyFigure::Text(node, graphics));
        }
        else if (element == "rect")
        {
            figures.push_back(new MyFigure::Rectangle(node, graphics));
        }
        else if (element == "line")
        {
            figures.push_back(new MyFigure::Line(node, graphics));
        }
        else if (element == "polygon")
        {
            figures.push_back(new MyFigure::Polygon(node, graphics));
        }
        else if (element == "polyline")
        {
            figures.push_back(new MyFigure::Polyline(node, graphics));
        }
        else if (element == "ellipse")
        {
            figures.push_back(new MyFigure::Ellipse(node, graphics));
        }
        else if (element == "circle")
        {
            figures.push_back(new MyFigure::Circle(node, graphics));
        }
        else if (element == "path")
        {
            figures.push_back(new MyFigure::Path(node, graphics));
        }
        else if (element == "g")
        {
            figures.push_back(new MyFigure::Group(node, graphics));
        }
        else if (element == "defs")
        {
            Defs::getInstance()->setDefsNode(node);
        }
    }
}

void FigureDraw::draw()
{
    for (Figure *figure : figures)
    {
        std::cout << "draw figure" << endl;
        figure->draw();
    }
}
