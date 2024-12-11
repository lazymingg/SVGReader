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
void MyFigure::Polygon::draw() {
    // Fill color
    Color fillColor = attributes.getFillColor();
    int fillOpacity = attributes.getFillOpacity() * 255;
    fillColor = Color(fillOpacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush brush(fillColor);

    // Stroke color
    Color strokeColor = attributes.getStrokeColor();
    int strokeOpacity = attributes.getStrokeOpacity() * 255;
    strokeColor = Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen pen(strokeColor, attributes.getStrokeWidth());

    // Prepare points
    std::vector<Point> pointArray(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        pointArray[i] = Point(points[i].getX(), points[i].getY());
    }

    // Apply transformation
    Gdiplus::Matrix transformMatrix;
    attributes.getTransform().transform(transformMatrix);

    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.SetTransform(&transformMatrix);

    // Draw filled polygon
    graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
    graphics.FillPolygon(&brush, pointArray.data(), pointArray.size());

    // Draw polygon outline
    graphics.DrawPolygon(&pen, pointArray.data(), pointArray.size());

    // Restore original matrix
    graphics.SetTransform(&originalMatrix);
}


void MyFigure::Polygon::applyTransform()
{
}
