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
    // Lấy giá trị `viewBox` scale từ `graphics`
    Gdiplus::Matrix currentMatrix;
    graphics.GetTransform(&currentMatrix);
    // Draw the line

    // Get fill color and adjust opacity
    Pen* pen = penRender.getSolidPen(attributes);
    Pen* penLinear = penRender.getPenLinear(static_cast<Fill *>(attributes.getAttributes("fill"))->getId(), attributes);
    graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
    
    Gdiplus::Matrix a;
    static_cast<Transform *>(attributes.getAttributes("transform"))->transform(a);
    graphics.MultiplyTransform(&a);
    // Gdiplus::Matrix originalMatrix;
    // graphics.GetTransform(&originalMatrix);
    // graphics.SetTransform(&a);
    graphics.DrawLine(pen, start.getX(), start.getY(), end.getX(), end.getY());
    if (penLinear != nullptr)
        graphics.DrawLine(penLinear, start.getX(), start.getY(), end.getX(), end.getY());
    
    graphics.SetTransform(&currentMatrix);
    delete pen;
    if (penLinear != nullptr)
        delete penLinear;
}