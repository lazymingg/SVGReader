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
// 	cout << "Rectangle" << endl;
// 	point.print();
// 	cout << width << " " << height << '\n';
// 	attributes.printAttributes();
}

void MyFigure::Rectangle::draw()
{


	Color fillColor = static_cast<Fill *>(attributes.getAttributes("fill"))->getFill();
	// ajust opacity
	int opacity = static_cast<FillOpacity *>(attributes.getAttributes("fill-opacity"))->getFillOpacity() * 255;
	if (fillColor.GetA() == 0 && fillColor.GetR() == 0 && fillColor.GetG() == 0 && fillColor.GetB() == 0)
	{
		opacity = 0;
	}
	fillColor = Color(opacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
	SolidBrush brush(fillColor);

	// draw stroke
	// if (attributes.getStroke() != "none")
	// {
	Color strokeColor = static_cast<Stroke *>(attributes.getAttributes("stroke"))->getStroke();
	// ajust opacity
	opacity = static_cast<StrokeOpacity *>(attributes.getAttributes("stroke-opacity"))->getStrokeOpacity() * 255;
	strokeColor = Color(opacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
	Pen pen(strokeColor, static_cast<StrokeWidth *>(attributes.getAttributes("stroke-width"))->getStrokeWidth());
	// print color
	graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
	Gdiplus::Matrix a;
	static_cast<Transform *>(attributes.getAttributes("transform"))->transform(a);

	Gdiplus::Matrix originalMatrix;
	graphics.GetTransform(&originalMatrix);
	graphics.SetTransform(&a);

	// Draw the rectangle with the pen and brush
	graphics.DrawRectangle(&pen, point.getX(), point.getY(), width, height);
	graphics.FillRectangle(&brush, point.getX(), point.getY(), width, height);

	graphics.SetTransform(&originalMatrix);
}