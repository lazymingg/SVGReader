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

    this->start.setX(stoi(getX1));
    this->start.setY(stoi(getY1));
    this->end.setX(stoi(getX2));
    this->end.setY(stoi(getY2));
}

void MyFigure::Line::printInfomation()
{
    cout << "Text" << endl;
    start.print();
    end.print();
    attributes.printAttributes();
}

void MyFigure::Line::draw()
{
    // Draw the line

    // Get fill color and adjust opacity
    Color strokeColor = attributes.getStrokeColor();
    // ajust opacity
    int opacity = attributes.getStrokeOpacity() * 255;
    strokeColor = Color(opacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen pen(strokeColor, attributes.getStrokeWidth());
    // print color
    graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

    graphics.DrawLine(&pen, start.getX(), start.getY(), end.getX(), end.getY());
}

void MyFigure::Line::applyTransform()
{
    cout << "Apply transform for Line" << endl;
}