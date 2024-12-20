#include "../ShapeHeader/Line.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Line::Line(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{

    string getX1 = rootNode->first_attribute("x1")->value();
    string getY1 = rootNode->first_attribute("y1")->value();
    string getX2 = rootNode->first_attribute("x2")->value();
    string getY2 = rootNode->first_attribute("y2")->value();

    this->start.setX(stof(getX1));
    this->start.setY(stof(getY1));
    this->end.setX(stof(getX2));
    this->end.setY(stof(getY2));
}

void MyFigure::Line::printInfomation()
{
    start.print();
    end.print();
    // attributes.printAttributes();
}

void MyFigure::Line::draw()
{
    // Draw the line

    // Get fill color and adjust opacity
    Color strokeColor = static_cast<Stroke *>(attributes.getAttributes("stroke"))->getStroke();
    // ajust opacity
    int opacity = static_cast<StrokeOpacity *>(attributes.getAttributes("stroke-opacity"))->getStrokeOpacity() * strokeColor.GetA();
    strokeColor = Color(opacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen pen(strokeColor, static_cast<StrokeWidth *>(attributes.getAttributes("stroke-width"))->getStrokeWidth());
    graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
    
    Gdiplus::Matrix a;
    
    static_cast<Transform *>(attributes.getAttributes("transform"))->transform(a);

    Gdiplus::Matrix originalMatrix;

    graphics.GetTransform(&originalMatrix);
    graphics.SetTransform(&a);
    graphics.DrawLine(&pen, start.getX(), start.getY(), end.getX(), end.getY());
    
    graphics.SetTransform(&originalMatrix);
}