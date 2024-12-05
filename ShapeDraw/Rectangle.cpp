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

	this->point.setX(stoi(getX));
	this->point.setY(stoi(getY));

	this->height = stoi(getHeight);
	this->width = stoi(getWidth);
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
	
	// Draw the Rectangle
	// Fill rectangle first
	// if (attributes.getFill() != "none")
	// {
	Color fillColor = attributes.getFillColor();
	// ajust opacity
	int opacity = attributes.getFillOpacity() * 255;
	fillColor = Color(opacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
	SolidBrush brush(fillColor);


	// draw stroke
	// if (attributes.getStroke() != "none")
	// {
	Color strokeColor = attributes.getStrokeColor();
	// ajust opacity
	opacity = attributes.getStrokeOpacity() * 255;
	strokeColor = Color(opacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
	Pen pen(strokeColor, attributes.getStrokeWidth());
	// print color
	graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
	Gdiplus::Matrix a;
	attributes.getTransform().transform(a);
	
	Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.SetTransform(&a);

	graphics.DrawRectangle(&pen, point.getX(), point.getY(), width, height);
	graphics.FillRectangle(&brush, point.getX(), point.getY(), width, height);

    graphics.SetTransform(&originalMatrix);

}

void MyFigure::Rectangle::applyTransform()
{
}
