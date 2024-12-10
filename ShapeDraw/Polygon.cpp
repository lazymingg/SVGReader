#include "../ShapeHeader/Polygon.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Polygon::Polygon(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
	// Đặt các điểm từ thuộc tính "points"
	string points = rootNode->first_attribute("points")->value();
	stringstream ss(points);
	string point;
	while (getline(ss, point, ' '))
	{
		stringstream ssPoint(point);
		string x, y;
		getline(ssPoint, x, ',');
		getline(ssPoint, y, ',');
		this->points.push_back(MyPoint::Point(stof(x), stof(y)));
	}
}

void MyFigure::Polygon::printInfomation()
{
	cout << "polygon" << endl;
	attributes.printAttributes();
	for (int i = 0; i < points.size(); i++)
	{
		points[i].print();
	}
}
void MyFigure::Polygon::draw()
{
	// draw polygon here
	// draw fill polygon first

	Color fillColor = attributes.getFillColor();
	// ajust opacity
	int opacity = attributes.getFillOpacity() * 255;
	fillColor = Color(opacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
	SolidBrush brush(fillColor);
	// print color

	Point *pointArray = new Point[points.size()];
	for (int i = 0; i < points.size(); i++)
	{
		pointArray[i].X = points[i].getX();
		pointArray[i].Y = points[i].getY();
	}
	graphics.FillPolygon(&brush, pointArray, (int)points.size());
	delete[] pointArray;

	// draw stroke
	Color strokeColor = attributes.getStrokeColor();
	// ajust opacity
	opacity = attributes.getStrokeOpacity() * 255;
	strokeColor = Color(opacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
	Pen pen(strokeColor, attributes.getStrokeWidth());
	// print color
	// print stroke color
	cout << "Stroke color: " << strokeColor.GetR() << " " << strokeColor.GetG() << " " << strokeColor.GetB() << endl;
	// print stroke width
	cout << "Stroke width: " << attributes.getStrokeWidth() << endl;
	// print stroke opacity
	cout << "Stroke opacity: " << attributes.getStrokeOpacity() << endl;
	
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
	Gdiplus::Matrix a;
	attributes.getTransform().transform(a);

	Gdiplus::Matrix originalMatrix;
	graphics.GetTransform(&originalMatrix);
	graphics.SetTransform(&a);

	graphics.FillPolygon(&brush, (Point *)&points[0], points.size());
	graphics.DrawPolygon(&pen, (Point *)&points[0], points.size());
	graphics.SetTransform(&originalMatrix);
}

void MyFigure::Polygon::applyTransform()
{
}
