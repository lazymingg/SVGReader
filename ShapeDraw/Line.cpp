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

    double unit1 = formatUnit(getX1);
    double unit2 = formatUnit(getY1);
    double unit3 = formatUnit(getX2);
    double unit4 = formatUnit(getY2);

    this->start.setX(stof(getX1) * unit1);
    this->start.setY(stof(getY1) * unit2);
    this->end.setX(stof(getX2) * unit3);
    this->end.setY(stof(getY2) * unit4);
}

void MyFigure::Line::printInfomation()
{
    start.print();
    end.print();
    // attributes.printAttributes();
}

void MyFigure::Line::draw()
{
    // Lấy giá trị `viewBox` scale từ `graphics`
    Gdiplus::Matrix currentMatrix;
    graphics.GetTransform(&currentMatrix);
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
    graphics.MultiplyTransform(&a);
    // Gdiplus::Matrix originalMatrix;
    // graphics.GetTransform(&originalMatrix);
    // graphics.SetTransform(&a);
    graphics.DrawLine(&pen, start.getX(), start.getY(), end.getX(), end.getY());
    
    graphics.SetTransform(&currentMatrix);
}