#include "../ShapeHeader/Rectangle.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Rectangle::Rectangle(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
	// Đặt các điểm từ thuộc tính "points"
	vector<float> xValues = static_cast<vector<float>>(static_cast<X*>(attributes.getAttributes("x"))->getXValues(1));
    vector<float> yValues = static_cast<vector<float>>(static_cast<Y*>(attributes.getAttributes("y"))->getYValues(1));
	
	this->point.setX(xValues[0]);
	this->point.setY(yValues[0]);
	
	string getWidth = rootNode->first_attribute("width")->value();
	string getHeight = rootNode->first_attribute("height")->value();

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
	// Lấy giá trị `viewBox` scale từ `graphics`
    Gdiplus::Matrix currentMatrix;
    graphics.GetTransform(&currentMatrix);
	Color fillColor = static_cast<Fill *>(attributes.getAttributes("fill"))->getFill();
	// ajust opacity
	int opacity = static_cast<FillOpacity *>(attributes.getAttributes("fill-opacity"))->getFillOpacity() * fillColor.GetA();
	fillColor = Color(opacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
	SolidBrush *brush= new SolidBrush(fillColor);

	// draw stroke
	// if (attributes.getStroke() != "none")
	// {
	Color strokeColor = static_cast<Stroke *>(attributes.getAttributes("stroke"))->getStroke();
	// ajust opacity
	opacity = static_cast<StrokeOpacity *>(attributes.getAttributes("stroke-opacity"))->getStrokeOpacity() * strokeColor.GetA();
	strokeColor = Color(opacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
	Pen *pen = new Pen(strokeColor, static_cast<StrokeWidth *>(attributes.getAttributes("stroke-width"))->getStrokeWidth());
	// print color
	graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
	Gdiplus::Matrix a;
	static_cast<Transform *>(attributes.getAttributes("transform"))->transform(a);
	graphics.MultiplyTransform(&a);

	// Gdiplus::Matrix originalMatrix;
	// graphics.GetTransform(&originalMatrix);
	// graphics.SetTransform(&a);

	// Draw the rectangle with the pen and brush
	graphics.DrawRectangle(pen, point.getX(), point.getY(), width, height);
	graphics.FillRectangle(brush, point.getX(), point.getY(), width, height);

	graphics.SetTransform(&currentMatrix);
	delete pen;
	delete brush;
}