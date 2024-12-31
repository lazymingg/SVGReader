#include "../ShapeHeader/Rectangle.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Rectangle::Rectangle(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
	// Đặt các điểm từ thuộc tính "points"
	string getX, getY;
	if(rootNode->first_attribute("x"))
	{
		getX = rootNode->first_attribute("x")->value();
	}
	else 
	{
		getX = "0";
	}
	
	if(rootNode->first_attribute("y"))
	{
		getY = rootNode->first_attribute("y")->value();
	}
	else
	{
		getY = "0";
	}
	
	string getWidth = rootNode->first_attribute("width")->value();
	string getHeight = rootNode->first_attribute("height")->value();

	double unit1 = formatUnit(getX);
	double unit2 = formatUnit(getY);
	double unit3 = formatUnit(getWidth);
	double unit4 = formatUnit(getHeight);

	this->point.setX(stof(getX) * unit1);
	this->point.setY(stof(getY) * unit2);

	this->width = stof(getWidth) * unit3;
	this->height = stof(getHeight) * unit4;
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

	// Create brushes and pen by penRender
	Brush *brush = penRender.getSolidBrush(attributes);
	Pen *pen = penRender.getSolidPen(attributes);

	bool isPenLinear = false;
	LinearGradientManager *temp = penRender.getPenLinear(static_cast<Fill *>(attributes.getAttributes("fill"))->getId(), attributes);
	Gdiplus::Pen *penLinear = nullptr;
	if (temp != nullptr)
	{
		penLinear = temp->getPen();
	}
	// print color
	graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
	Gdiplus::Matrix a;
	static_cast<Transform *>(attributes.getAttributes("transform"))->transform(a);
	graphics.MultiplyTransform(&a);

	graphics.DrawRectangle(pen, point.getX(), point.getY(), width, height);
	graphics.FillRectangle(brush, point.getX(), point.getY(), width, height);

	// Use penLinear
	if (penLinear != nullptr)
		graphics.DrawRectangle(penLinear, point.getX(), point.getY(), width, height);
	if (penLinear != nullptr)
	{
		// Transform coordinates if gradientUnits is objectBoundingBox
		if (!temp->getIsUserSpaceOnUse())
		{
			// Retrieve the bounding box of the rectangle
			Gdiplus::RectF bbox(point.getX(), point.getY(), width, height);
			temp->transformCoordinates(bbox);
		}

		Gdiplus::LinearGradientBrush *linearBrush = temp->getBrush();
		graphics.FillRectangle(linearBrush, point.getX(), point.getY(), width, height);
	}

	graphics.SetTransform(&currentMatrix);
	delete pen;
	delete brush;
	if (penLinear != nullptr)
		delete penLinear;
	if (temp != nullptr)
		delete temp;
}