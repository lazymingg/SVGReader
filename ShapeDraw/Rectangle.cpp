#include "../ShapeHeader/Rectangle.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Rectangle::Rectangle(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
	// Đặt các điểm từ thuộc tính "points"
	string getX = rootNode->first_attribute("x")->value();
	string getY = rootNode->first_attribute("y")->value();
	string getWidth = rootNode->first_attribute("width")->value();
	string getHeight = rootNode->first_attribute("height")->value();

	this->point.setX(stof(getX));
	this->point.setY(stof(getY));

	this->height = stof(getHeight);
	this->width = stof(getWidth);
}

void MyFigure::Rectangle::printInfomation()
{
	cout << "Rectangle" << endl;
	point.print();
	cout << width << " " << height << '\n';
	attributes.printAttributes();
}

void MyFigure::Rectangle::draw()
{
    // Get fill color and adjust opacity if necessary
    Color fillColor = attributes.getFillColor();
    int fillOpacity = static_cast<int>(attributes.getFillOpacity() * 255);
    fillColor = Color(fillOpacity * fillColor.GetA(), fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush brush(fillColor);

    // Get stroke color and adjust opacity if necessary
    Color strokeColor = attributes.getStrokeColor();
    int strokeOpacity = static_cast<int>(attributes.getStrokeOpacity() * 255);
    strokeColor = Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen pen(strokeColor, attributes.getStrokeWidth());

    // Set anti-aliasing for smoother rendering
    graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

    // Apply transformation if defined
    Gdiplus::Matrix transformMatrix;
    attributes.getTransform().transform(transformMatrix);

    // Save the original transformation and set the new one
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.SetTransform(&transformMatrix);

    // Draw the rectangle with the pen and brush
    graphics.DrawRectangle(&pen, point.getX(), point.getY(), width, height);
    graphics.FillRectangle(&brush, point.getX(), point.getY(), width, height);

    // Restore the original transformation
    graphics.SetTransform(&originalMatrix);
}

void MyFigure::Rectangle::applyTransform()
{
}
