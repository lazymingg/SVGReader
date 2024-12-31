#include "../ShapeHeader/Rectangle.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Rectangle::Rectangle(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
	// Đặt các điểm từ thuộc tính "points"
	vector<float> xValues = static_cast<vector<float>>(static_cast<X *>(attributes.getAttributes("x"))->getXValues(1));
	vector<float> yValues = static_cast<vector<float>>(static_cast<Y *>(attributes.getAttributes("y"))->getYValues(1));

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